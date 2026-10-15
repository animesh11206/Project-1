#include <string>
#include "utf8_encode.h"
#include "utf32_encode.h"

std::string utf8_encode(const std::string& value) {
    // Throws std::invalid_argument if the input is invalid UTF-8.
    (void)utf32_encode(value);

    return value;
}