#include <cstdint>
#include <stdexcept>
#include <string>
#include "utf32_encode.h"

std::u32string utf32_encode(const std::string& value) {
    std::u32string result;
    std::size_t i = 0;

    while (i < value.size()) {
        unsigned char byte = value[i++];
        std::uint32_t code;
        std::uint32_t minimum = 0;
        unsigned remaining = 0;

        if (byte < 0x80) {
            code = byte;
        } else if (byte >= 0xC2 && byte <= 0xDF) {
            code = byte % 32;
            remaining = 1;
            minimum = 0x80;
        } else if (byte >= 0xE0 && byte <= 0xEF) {
            code = byte % 16;
            remaining = 2;
            minimum = 0x800;
        } else if (byte >= 0xF0 && byte <= 0xF4) {
            code = byte % 8;
            remaining = 3;
            minimum = 0x10000;
        } else {
            throw std::invalid_argument("Invalid UTF-8");
        }

        for (unsigned j = 0; j < remaining; ++j) {
            if (i == value.size()) {
                throw std::invalid_argument("Incomplete UTF-8");
            }

            byte = value[i++];

            if (byte < 0x80 || byte > 0xBF) {
                throw std::invalid_argument("Invalid UTF-8");
            }

            code = code * 64 + byte % 64;
        }

        if (code < minimum || code > 0x10FFFF ||
            (code >= 0xD800 && code <= 0xDFFF)) {
            throw std::invalid_argument("Invalid Unicode character");
        }

        result += static_cast<char32_t>(code);
    }

    return result;
}
