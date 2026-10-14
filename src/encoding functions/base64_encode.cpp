#include <cstdint>
#include <string>
#include "base64_encode.h"

std::string base64_encode(const std::string& value) {
    static constexpr char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string encoded;
    std::uint32_t buffer = 0;
    unsigned bits = 0;

    for (unsigned char byte : value) {
        buffer = (buffer << 8) | byte;
        bits += 8;

        while (bits >= 6) {
            bits -= 6;
            encoded += alphabet[(buffer >> bits) & 0x3F];
        }
    }

    if (bits > 0) {
        encoded += alphabet[(buffer << (6 - bits)) & 0x3F];
    }

    while (encoded.size() % 4 != 0) {
        encoded += '=';
    }

    return encoded;
}