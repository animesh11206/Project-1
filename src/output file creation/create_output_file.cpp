#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "create_output_file.h"

bool create_output_file(std::string operation[], const std::string& wordlist_file) {
    std::filesystem::path current_dir = std::filesystem::current_path();
    std::filesystem::path created_dir = current_dir / "Wordcoder";
    bool condition1 = false;
    bool condition2 = false;

    std::error_code err;

    if (std::filesystem::is_directory(created_dir)) {
        //Path already exists so we will use that
        condition1 = true;
    }

    if (!std::filesystem::is_directory(created_dir)){
        if (std::filesystem::create_directory(created_dir, err)) {
            //Path  created successfully
            condition2 = true;
        } else {
            std::cerr << "Error: Cannot create the output path." << err.message() << std::endl;
            return false;
        }
    }

    if (!(condition1 || condition2)) {
        std::cerr << "Error: The output directory could not be created" << std::endl;
        return false;
    }

    if ((condition1 || condition2)) {
        std::string out_file = std::filesystem::path(wordlist_file).filename().string();

        for (int i = 0; i < num_operation_flags_used; i++) {
            out_file = operation[i] + "_" + out_file;
        }

        std::filesystem::path output_path = created_dir / out_file;
        std::string stem = std::filesystem::path(out_file).stem().string();
        std::string extension = std::filesystem::path(out_file).extension().string();

        if (std::filesystem::exists(output_path)) {
            for (int i = 0; std::filesystem::exists(output_path); i++) {
                out_file = stem + "(" + std::to_string(i) + ")" + extension;
                output_path = created_dir / out_file;
            }
        }

        std::ofstream file(output_path);

        if (!file) {
            std::cerr << "Error: Could not open the output file." << std::endl;
            return false;
        }

        output_file = output_path.string();
        return true;

    } else {
        std::cerr << "Error: The output file cannot be created." << std::endl;
        return false;
    }
}