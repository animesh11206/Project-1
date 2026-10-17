#include <iostream>
#include <string>
#include "display_help.h"

void display_help(const char* program_name) {
    std::cout
        << "Wordcoder " << VERSION << " - Wordlist encoding tool\n"
        << "By " << AUTHOR << "\n\n"

        << "USAGE\n"
        << "  " << program_name << " -w <file.txt> <encoding...> [-o <file.txt>]\n"
        << "  " << program_name << " -h | --help\n"
        << "  " << program_name << " --version\n\n"

        << "DESCRIPTION\n"
        << "  Encode a wordlist using one to three encoding options.\n"
        << "  A wordlist and at least one encoding are required for normal use.\n\n"

        << "OPTIONS\n"
        << "  -h, --help              Display this help message and exit.\n"
        << "      --version           Display the version and exit.\n"
        << "  -w, --wordlist <file>   Read words from a nonempty .txt file.\n"
        << "  -o, --output <file>     Write to an existing, empty .txt file.\n"
        << "                          If omitted, create a file in ./Wordcoder/.\n\n"

        << "ENCODINGS\n"
        << "  -ascii                  ASCII character encoding.\n"
        << "  -base32                 Base32 representation using A-Z and 2-7.\n"
        << "  -base64                 Standard Base64 representation.\n"
        << "  -base64url              URL-safe Base64 using '-' and '_'.\n"
        << "  -hex                    Hexadecimal representation of bytes.\n"
        << "  -url                    URL percent-encoding of characters.\n"
        << "  -utf8                   UTF-8 Unicode encoding.\n"
        << "  -utf16be                UTF-16 with big-endian byte order.\n"
        << "  -utf16le                UTF-16 with little-endian byte order.\n"
        << "  -utf32be                UTF-32 with big-endian byte order.\n"
        << "  -utf32le                UTF-32 with little-endian byte order.\n\n"

        << "EXAMPLES\n"
        << "  Show help:\n"
        << "    " << program_name << " --help\n\n"

        << "  Encode a wordlist with Base64:\n"
        << "    " << program_name << " -w words.txt -base64\n\n"

        << "  Specify an output file:\n"
        << "    " << program_name
        << " --wordlist words.txt -hex --output encoded.txt\n\n"

        << "  Specify multiple encodings:\n"
        << "    " << program_name << " -w words.txt -base64 -url\n\n"

        << "  Use a path containing spaces:\n"
        << "    " << program_name << " -w \"my wordlists/words.txt\" -base32\n\n"

        << "NOTES\n"
        << "  Help and version options must be used on their own.\n"
        << "  Provide between one and three encoding options per run.\n"
        << "  Quote file paths that contain spaces.\n"
        << "  Encoding transforms data; it does not encrypt it.\n";
}