#include <iostream>
#include <string>
#include <fstream>
#include "file_validation.h"
#include "flag_validation.h"

const std::string VERSION = "1.0.0";
const std::string AUTHOR = "Your Name";

const std::string PATH;
const std::string FLAGS[];
const int NUM_FLAGS = 0;

int main(int argc, char* argv[]) {

    if (!check_valid_flags(argc, argv, FLAGS, NUM_FLAGS)) {
            return 1;
        }

    
}