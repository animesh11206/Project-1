#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "file_validation.h"

bool is_valid_file(int argc, char* argv[], const std::string& file_path) {
    bool condition_1 = false;
    bool condition_2 = false;

    for (int i = 1; argv[i] != nullptr; ++i) {
        std::string arg = argv[i];

        if (arg == "-w" || arg == "--wordlist" || arg == "-o" || arg == "--output") {
            
            if (i + 1 >= argc) {
                std::cerr << "Error: Missing argument for flag '" << arg << "'." << std::endl;
                return false;
            }           
            std::string next_arg = argv[i + 1];

            std::string extension = std::filesystem::path(next_arg).extension().string();

            if (i + 1 < argc) {
                
                if (next_arg == file_path) {
                    condition_1 = true;
                }

                if (extension == ".txt") {
                    condition_2 = true;
                }
                else if (extension != ".txt") {
                    std::cerr << "Error: Invalid file extension for '" << next_arg << "'. Only .txt files are allowed." << std::endl;
                    return false;
                }

                ++i; // Skip the next argument since it's already processed
            }
        }
    }
    if (condition_1 && condition_2) {
        return true;
    } 
    else {
        return false;
    }
}
