#include <string>
#include "hex_encode.h"

std::string hex_encode(const std::string& value) {
    std::string digits = "0123456789abcdef";
    std::string result;

    for (unsigned char c : value) {
        result += digits[c / 16];
        result += digits[c % 16];
    }

    return result;
}