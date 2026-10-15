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

    if (std::filesystem::is_directory(created_dir)) {
        //Path already exists so we will use that
        condition1 = true;
    }

    if (!std::filesystem::is_directory(created_dir)){
        if (std::filesystem::create_directory(created_dir)) {
            //Path  created successfully
            condition2 = true;
        }
    }

    if (!(condition1 || condition2)) {
        std::cerr << "Error: The output directory could not be created" << std::endl;
        return false;
    }

    if ((condition1 || condition2)) {
        std::string output_file = wordlist_file;

        for (int i = 0; i < num_operation_flags_used; i++) {
            output_file = operation[i] + "_" + output_file;
        }

        std::filesystem::path output_path = created_dir / output_file;
        std::ofstream file(output_path);

        if (!file) {
            std::cerr << "Error: Could not open the output file." << std::endl;
            return false;
        }

        output_file = output_path.string();
        return true;
    }
}