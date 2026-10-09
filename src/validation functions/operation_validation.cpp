#include <iostream>
#include <string>
#include "operation_validation.h"

bool num_operations(int argc, char* argv[], const std::string valid_operations[], const int num_valid_ops) {
    int count = 0;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        bool valid = false;

        for (int j = 0; j < num_valid_ops; ++j) {
            if (arg == valid_operations[j]) {
                count++;
                valid = true;
                break;
            }
        }

        if (!valid) {
            continue; // Skip invalid operations, but continue checking the rest of the arguments
        }
    }

    if (count == 0) {
        std::cerr << "Error: No valid operations provided." << std::endl;
        return false;
    }

    if (count > 3) {
        std::cerr << "Error: More than 3 operations provided. Please provide 3 or less operations." << std::endl;
        return false;
    }

    count = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        bool valid = false;

        for (int j = 0; j < num_valid_ops; ++j) {
            if (arg == valid_operations[j]) {
                count++;
                valid = true;
                OPERATIONS_FLAGS_USED[count-1] = arg;
                break;
            }
        }

        if (!valid) {
            continue; // Skip invalid operations, but continue checking the rest of the arguments
        }
    }

    return true;
}
