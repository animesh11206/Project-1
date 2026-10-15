#ifndef CREATE_OUTPUT_FILE_H
#define CREATE_OUTPUT_FILE_H

#include <string>

extern int num_operation_flags_used;
extern std::string output_file;
extern bool output_file_valid;

bool create_output_file(std::string operation[], const std::string& wordlist_file);

#endif