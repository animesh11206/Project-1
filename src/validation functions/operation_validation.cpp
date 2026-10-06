#include <iostream>
#include <string>
#include "operation_validation.h"

int num_operations(int argc, char* argv[], const std::string valid_operations[], const int num_ops) {
    int count = 0;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        bool valid = false;

        for (int j = 0; j < num_ops; ++j) {
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

    return count;
}
