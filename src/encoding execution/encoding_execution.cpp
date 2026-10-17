#include <string>
#include <stdexcept>
#include "encoding_functions.h"

std::string encode(const std::string& flag, const std::string& value) {

    if (flag == "-ascii") {
        return ascii_encode(value);
    }

    if (flag == "-base32") {
        return base32_encode(value);
    }

    if (flag == "-base64") {
        return base64_encode(value);
    }

    if (flag == "-base64url") {
        return base64url_encode(value);
    }

    if (flag == "-hex") {
        return hex_encode(value);
    }

    if (flag == "-url") {
        return url_encode(value);
    }

    if (flag == "-utf8") {
        return utf8_encode(value);
    }

    if (flag == "-utf16le") {
        return utf16le_encode(value);
    }

    if (flag == "-utf16be") {
        return utf16be_encode(value);
    }

    if (flag == "-utf32le") {
        return utf32le_encode(value);
    }
    
    if (flag == "-utf32be") {
        return utf32be_encode(value);
    }

    throw std::invalid_argument("Unknown encoding flag: " + flag);
}