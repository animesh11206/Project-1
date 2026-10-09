#ifndef FILE_VALIDATION_H
#define FILE_VALIDATION_H

#include <string>
#include <fstream>

extern bool OUTPUT_FILE_VALID;
extern std::string input_file;
extern std::string output_file;

bool is_valid_file(int argc, char* argv[], const std::string& file_path, const std::string& flag);

#endif