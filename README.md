# Wordcoder

A C++ command-line tool for encoding wordlists, one line at a time.

Wordcoder supports 11 encoding options and lets you chain up to three transformations in a single run. Use it to inspect character representations, prepare encoded text, or experiment with encoding pipelines.

**Version:** 1.0.0 · **Author:** Animesh Bhatia · **Status:** Early development

## Features

- Base32, Base64, URL-safe Base64, hexadecimal, and URL percent-encoding.
- Decimal ASCII values and Unicode representations in UTF-8, UTF-16, and UTF-32.
- Ordered encoding chains with one to three operations per run.
- Line-by-line processing without loading the entire wordlist into memory.
- Input validation and automatic output filenames that avoid existing paths.
- Temporary output staging to keep encoding exceptions from committing partial results.

Encoding changes how data is represented. It does not encrypt data or provide confidentiality.

## Download

Download the compiled binaries from the [GitHub Releases page](https://github.com/animesh11206/Project-1/releases). No compiler is needed to run the packaged tool.

| Platform | Release asset |
| --- | --- |
| Windows x86_64 | `wordcoder-v1.0.0-windows-x86_64.zip` |
| Linux x86_64 | `wordcoder-v1.0.0-linux-x86_64.tar.gz` |

### Windows

Extract the ZIP, keep the bundled DLLs alongside `wordcoder.exe`, and open PowerShell in the extracted folder:

```powershell
.\wordcoder.exe --help
.\wordcoder.exe -w words.txt -base64
```

### Linux

Extract the archive and run the tool from a terminal:

```bash
tar -xzf wordcoder-v1.0.0-linux-x86_64.tar.gz
cd wordcoder-v1.0.0-linux-x86_64
./wordcoder --help
./wordcoder -w words.txt -base64
```

For the encoding examples, place your own nonempty `words.txt` in the extracted folder. Linux requires compatible system libraries; use the source build instructions below if the binary is incompatible with your distribution.

## Build from source

You need a C++17 compiler and standard library with `std::filesystem` support. The project uses the C++ standard library and has no third-party library dependencies.

```sh
git clone https://github.com/animesh11206/Project-1.git
cd Project-1
```

### Windows — PowerShell and MinGW-w64

Make sure `g++` is available in your terminal, then run from the repository root:

```powershell
$sources = Get-ChildItem -Path src -Recurse -Filter *.cpp |
    Select-Object -ExpandProperty FullName

g++ -std=c++17 -O2 -Wall -Wextra -I include -I "include/encoding functions" $sources -o wordcoder.exe

.\wordcoder.exe --help
```

### Linux — Bash and GCC

The following command collects source paths safely, including directories containing spaces:

```bash
mapfile -d '' sources < <(find src -type f -name '*.cpp' -print0)
g++ -std=c++17 -O2 -Wall -Wextra -I include -I "include/encoding functions" "${sources[@]}" -o wordcoder

./wordcoder --help
```

The Windows build has been checked with MinGW-w64. The Linux command is provided for building from source; Linux behavior has not yet been verified in this project.

## Usage

```text
wordcoder -w <wordlist.txt> <encoding...> [-o <output.txt>]
wordcoder -h
wordcoder --help
wordcoder --version
```

Use `./wordcoder` on Linux or `.\wordcoder.exe` in Windows PowerShell in place of `wordcoder` below.

| Option | Description |
| --- | --- |
| `-h`, `--help` | Display usage and exit. Must be used alone. |
| `--version` | Display the version and exit. Must be used alone. |
| `-w`, `--wordlist <file>` | Required input file: readable, nonempty, and ending in `.txt`. |
| `-o`, `--output <file>` | Optional output file: must already exist, be writable and empty, and end in `.txt`. |

Normal runs require one to three encoding flags. Flags and the `.txt` extension are case-sensitive. Quote paths containing spaces.

### Encode a wordlist

Given a `words.txt` file containing:

```text
hello
world
```

Run:

```sh
wordcoder -w words.txt -base64
```

The generated output contains:

```text
aGVsbG8=
d29ybGQ=
```

### Chain encodings

```sh
wordcoder -w words.txt -base64 -url
```

Each line is Base64-encoded first, then the resulting text is URL-encoded:

```text
hello → aGVsbG8= → aGVsbG8%3D
```

Each operation receives the previous operation's output. The tool writes one final result per input line; it does not create a separate result for each encoding.

### Choose an output file

Create an empty output file first, then pass it with `-o`:

```powershell
# Windows PowerShell: use a filename that does not already exist.
New-Item -ItemType File -Path encoded.txt
.\wordcoder.exe --wordlist words.txt -hex --output encoded.txt
```

```bash
# Linux: use a filename that does not already exist.
touch encoded.txt
./wordcoder --wordlist words.txt -hex --output encoded.txt
```

A nonempty output file is rejected. A missing output file is also rejected; omit `-o` to let Wordcoder create one automatically.

### Paths containing spaces

```sh
wordcoder -w "my wordlists/words.txt" -base32
```

## Supported encodings

The examples below show the output for the single character `A`.

| Flag | Output format | Example |
| --- | --- | --- |
| `-ascii` | Space-separated decimal ASCII values; rejects non-ASCII input | `65` |
| `-base32` | Base32 using `A–Z` and `2–7`, with `=` padding | `IE======` |
| `-base64` | Standard Base64 with `=` padding | `QQ==` |
| `-base64url` | Base64 using `-` and `_` instead of `+` and `/`; retains `=` padding | `QQ==` |
| `-hex` | Lowercase hexadecimal bytes without separators | `41` |
| `-url` | Percent-encoded bytes; unreserved characters remain unchanged | `A` |
| `-utf8` | Validates UTF-8 and returns the original bytes | `A` |
| `-utf16be` | UTF-16 big-endian bytes displayed as hexadecimal text | `00 41` |
| `-utf16le` | UTF-16 little-endian bytes displayed as hexadecimal text | `41 00` |
| `-utf32be` | UTF-32 big-endian bytes displayed as hexadecimal text | `00 00 00 41` |
| `-utf32le` | UTF-32 little-endian bytes displayed as hexadecimal text | `41 00 00 00` |

Unicode operations interpret input as UTF-8. UTF-16 and UTF-32 options produce space-separated, uppercase hexadecimal text, rather than binary UTF-16 or UTF-32 files. Chaining another operation encodes that text representation.

## Input and output behavior

- Each input line is processed independently, including blank lines.
- A final line without a newline is still processed. Every output result receives a newline.
- Use UTF-8 input without a byte-order mark to avoid treating the mark as part of the first word. UTF-16/32 input files are not decoded automatically.
- Without `-o`, output is created under `Wordcoder/` in the current working directory.
- Output names include the selected flags and input filename. Flags are prepended in turn, so the filename lists them in reverse order; processing still follows command-line order.
- If a generated output path already exists, a numeric suffix such as `(0)` is added.
- Exit code `0` indicates success. Handled validation and processing errors return `1`.

## Project structure

```text
include/                    Public declarations and shared state declarations
  encoding functions/       Individual encoding declarations
src/
  main.cpp                  CLI flow, file processing, and error handling
  display_help.cpp          Help output
  encoding execution/       Encoding dispatch
  encoding functions/       Encoding implementations
  validation functions/     Flag, operation, and file validation
  output file creation/     Automatic output paths and filenames
```

## Contributing

Issues and pull requests are welcome. For a bug report, include your operating system, compiler version, exact command, a minimal input example, and the expected and actual results. Avoid including private wordlists or sensitive data.

Useful next improvements include exclusive temporary-file creation, atomic output replacement, automated encoding and failure-case tests, and a CMake build with CI checks.

## License

No license file is currently included. This repository does not yet specify permissions for reuse, modification, or redistribution.
