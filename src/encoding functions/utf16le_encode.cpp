#include <string>
#include "utf16_encode.h"

std::string utf16le_encode(const std::string& value) {
    static constexpr char digits[] = "0123456789ABCDEF";
    std::string result;

    for (char16_t unit : utf16_encode(value)) {
        for (unsigned i = 0; i < 2; ++i) {
            unsigned shift = i * 8;
            unsigned byte = (unit >> shift) & 0xFF;

            if (!result.empty()) {
                result += ' ';
            }
            result += digits[byte >> 4];
            result += digits[byte & 0x0F];
        }
    }

    return result;
}
