#ifndef OPERATION_VALIDATION_H
#define OPERATION_VALIDATION_H

#include <string>

extern std::string operation_flags_used[3];
extern int num_operation_flags_used;

bool num_operations(int argc, char* argv[], const std::string valid_operations[], const int num_ops);

#endif