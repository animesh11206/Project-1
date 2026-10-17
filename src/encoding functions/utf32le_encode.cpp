#include <string>
#include "utf32_encode.h"

std::string utf32le_encode(const std::string& value) {
    static constexpr char digits[] = "0123456789ABCDEF";
    std::string result;

    for (char32_t unit : utf32_encode(value)) {
        for (unsigned i = 0; i < 4; ++i) {
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
