#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <filesystem>
#include "file_validation.h"
#include "flag_validation.h"
#include "operation_validation.h"
#include "create_output_file.h"
#include "encoding_execution.h"
#include "display_help.h"

const std::string VERSION = "1.0.0";
const std::string AUTHOR = "Animesh Bhatia";

const std::string FLAGS[18] = {"-h", "--help", "--version", "-w", "--wordlist", "-o", "--output",
                               "-ascii", "-base32", "-base64", "-base64url", "-hex", "-url", "-utf8",
                               "-utf16be", "-utf16le", "-utf32be", "-utf32le" };

const std::string OPERATIONS_FLAGS[11] = {"-ascii", "-base32", "-base64", "-base64url", "-hex", "-url", "-utf8",
                                          "-utf16be", "-utf16le", "-utf32be", "-utf32le"};

const int NUM_FLAGS = 18;
const int NUM_OPERATIONS_FLAGS = 11;

bool output_file_valid = false;
std::string operation_flags_used[3];
std::string input_file;
std::string output_file;
int num_operation_flags_used;

int main(int argc, char* argv[]) {

    if (argc == 2) {
        std::string arg = argv[1];

        if (arg == "-h" || arg == "--help") {
            display_help(argv[0]);
            return 0;
        }

        if (arg == "--version") {
            std::cout << VERSION << '\n';
            return 0;
        }
    }

    bool has_wordlist = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help" || arg == "--version") {
            std::cerr << "Error: " << arg << " must be used alone.\n";
            return 1;
        }

        if (arg == "-w" || arg == "--wordlist") {
            has_wordlist = true;
        }

        // Skip file paths so they aren't interpreted as flags.
        if (arg == "-w" || arg == "--wordlist" ||
            arg == "-o" || arg == "--output") {
            ++i;
        }
    }

    if (!has_wordlist) {
        std::cerr << "Error: -w or --wordlist is required.\n";
        return 1;
    }

    if (!check_valid_flags(argc, argv, FLAGS, NUM_FLAGS)) {
        return 1;
    }

    if (!num_operations(argc, argv, OPERATIONS_FLAGS, NUM_OPERATIONS_FLAGS)) {
        return 1;
    }

    if (!output_file_valid) {
        if (!create_output_file(operation_flags_used, input_file)) {
            return 1;
        }
    }

    const std::filesystem::path temp_file = output_file + ".tmp";

    try {
        std::ifstream file(input_file);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open input file.");
        }

        file.exceptions(std::ios::badbit);

        std::ofstream output;
        output.exceptions(std::ios::failbit | std::ios::badbit);
        output.open(temp_file);

        std::string word;
        while (std::getline(file, word)) {
            for (int i = 0; i < num_operation_flags_used; ++i) {
                word = encode(operation_flags_used[i], word);
            }

            output << word << '\n';
        }

        output.close();

        std::filesystem::copy_file(
            temp_file,
            output_file,
            std::filesystem::copy_options::overwrite_existing
        );

        std::filesystem::remove(temp_file);
    }
    catch (const std::exception& error) {
        std::error_code cleanup_error;
        std::filesystem::remove(temp_file, cleanup_error);

        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}