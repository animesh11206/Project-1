#ifndef FLAG_VALIDATION_H
#define FLAG_VALIDATION_H

#include <string>
bool check_valid_flags(int argc, char* argv[], const std::string valid_flags[], const int num_flags);

#endif