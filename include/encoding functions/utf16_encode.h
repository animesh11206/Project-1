#ifndef UTF16_ENCODE_H
#define UTF16_ENCODE_H

#include <string>

std::u16string utf16_encode(const std::string& value);

// Return space-separated hexadecimal bytes, without a BOM.
std::string utf16le_encode(const std::string& value);
std::string utf16be_encode(const std::string& value);

#endif
