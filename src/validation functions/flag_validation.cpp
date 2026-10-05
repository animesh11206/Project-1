#include <iostream>
#include <string>
#include <fstream>
#include "flag_validation.h"
#include "file_validation.h"


bool check_valid_flags(int argc, char* argv[], const std::string valid_flags[], const int num_flags) {  

    int count = 0;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];       
        bool valid = false;

        if (is_valid_file(argc,argv, arg)) {
            count++;
            continue;
        }

        for (int j = 0; j < num_flags; ++j) {
            
            if (arg == valid_flags[j]) {
                count++;
                valid = true;
                break;
            }
        }

        if (!valid) {
                std::cerr << "Error: Invalid flag '" << arg << "'." << std::endl;
                return false;
            }
    }

    
    if (count == argc - 1) {
        return true;
    } 
    else {
        return false;
    }
}


/* This function checks if the provided flag is valid by comparing it against a list of valid flags. 
If the flag is not found in the list, it prints an error message and returns false. 
If the flag is valid, it returns true.
*/


        

    
