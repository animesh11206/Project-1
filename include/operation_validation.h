#ifndef OPERATION_VALIDATION_H
#define OPERATION_VALIDATION_H

#include <string>

extern std::string OPERATIONS_FLAGS_USED[3];

bool num_operations(int argc, char* argv[], const std::string valid_operations[], const int num_ops);

#endif