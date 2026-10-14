#include <string>

std::string ascii_encode(const std::string& value) {
    std::string result;

    for (unsigned char c : value) {
        if (!result.empty()) {
            result += ' ';
        }

        result += std::to_string(c);
    }

    return result;
}