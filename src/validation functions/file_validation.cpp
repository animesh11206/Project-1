#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "file_validation.h"
#include "input_file_validation.h"
#include "output_file_validation.h"
#include "create_output_file.h"

bool is_valid_file(int argc, char* argv[], const std::string& file_path, const std::string& flag) {

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        bool condition_1 = false;
        bool condition_2 = false;

        if (i + 1 >= argc) {
                std::cerr << "Error: Missing argument for flag '" << arg << "'." << std::endl;
                break; // Exit the loop if there's no next argument
            }  

        std::string next_arg = argv[i + 1];

        if (arg == "-w" || arg == "--wordlist" || arg == "-o" || arg == "--output") {
            
            std::string extension = std::filesystem::path(next_arg).extension().string();

            if (i + 1 < argc) {
                
                if (next_arg == file_path && arg == flag) {
                    condition_1 = true;
                }

                if (extension == ".txt" && arg == flag) {
                    condition_2 = true;
                }
                else if (extension != ".txt") {
                    std::cerr << "Error: Invalid file extension for '" << next_arg << "'. Only .txt files are allowed." << std::endl;
                    return false;
                }

                if (condition_1 && condition_2) {
                    
                    if (arg == "-w" || arg == "--wordlist") {
                        if (!is_valid_input_file(next_arg)) {
                            return false;
                        }
                        return true; // Valid input file
                    }

                    if (arg == "-o" || arg == "--output"){
                        
                        if (!is_valid_output_file(next_arg)) {
                            OUTPUT_FILE_VALID = false;
                            return false;
                            
                        } 
                        OUTPUT_FILE_VALID = true;
                        return true; // Valid output file                   
                    }
                }

                ++i; // Skip the next argument since it's already processed
            }
        }
        
    }
    return false; // No valid file found
}
