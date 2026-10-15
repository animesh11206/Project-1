#include <stdexcept>
#include <string>
#include "ascii_encode.h"

std::string ascii_encode(const std::string& value) {
    std::string result;

    for (unsigned char c : value) {
        if (c > 127) {
            throw std::invalid_argument(
                "Input contains a non-ASCII character"
            );
        }

        if (!result.empty()) {
            result += ' ';
        }

        result += std::to_string(static_cast<unsigned int>(c));
    }

    return result;
}