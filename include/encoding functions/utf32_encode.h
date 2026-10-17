#ifndef UTF32_ENCODE_H
#define UTF32_ENCODE_H

#include <string>

std::u32string utf32_encode(const std::string& value);

// Return space-separated hexadecimal bytes, without a BOM.
std::string utf32le_encode(const std::string& value);
std::string utf32be_encode(const std::string& value);

#endif
