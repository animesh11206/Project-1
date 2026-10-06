#include <iostream>
#include <string>
#include <fstream>
#include "input_file_validation.h"


bool is_valid_input_file(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open input file '" << file_path << "'." << std::endl;
        return false;
    }

    if (file.peek() != std::ifstream::traits_type::eof()) {
        if (file.good()) {
            file.close();
            return true;
        } else {
            std::cerr << "Error: Input file '" << file_path << "' is not in a valid format." << std::endl;
            file.close();
            return false;
        }
    } else {
        std::cerr << "Error: Input file '" << file_path << "' is empty." << std::endl;
        file.close();
        return false;
    }
}