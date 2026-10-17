#include <iostream>
#include <string>
#include <fstream>
#include "file_validation.h"
#include "flag_validation.h"
#include "operation_validation.h"
#include "create_output_file.h"

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

    
}