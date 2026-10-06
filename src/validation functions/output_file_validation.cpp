#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "output_file_validation.h"

bool is_valid_output_file(const std::string& file_path) {

    if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {    
        std::fstream file(file_path, std::ios::in | std::ios::out);
        if (!file) {
            std::cerr << "Error: Unable to open output file '" << file_path << "' for writing." << std::endl;
            return false;
        }
    
        if (file.peek() != std::ifstream::traits_type::eof()) {
            std::cerr << "Error: Output file '" << file_path << "' is not empty. Please choose a different output file or delete the existing one." << std::endl;
            return false;
        }

        if (file.fail()) {
            std::cerr << "Error: Output file '" << file_path << "' is not in a valid format." << std::endl;
            return false;
        }

        file.close();
        return true; // File exists, is writable, and is empty
    }
    return false; // File does not exist, so it's not valid
}