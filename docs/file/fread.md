# Documentation of function `readFile`
Function usage: Read a text file and return its content as a `std::string`.

Function implementation:
```cpp
std::string readFile(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);        
    std::ifstream ifs;
    try {
        ifs.open(name);
    } catch(...) {
        F_THROW_OPENFAIL(name);
    }
    std::string s;
    try {
        ifs >> s;
    } catch(...) {
        F_THROW_READFAIL(name);
    }
    return s;
}
```
**`std::ifstream`**: Input file stream for reading text files.
**`ifs.open(name)`**: Opens the specified file in text mode.
**`ifs >> s`**: Reads file content into a string.
**Exceptions thrown**:
- `FileNotFoundException`: if file does not exist.
- `FileOpenFailException`: if file cannot be opened.
- `FileReadFailException`: if file reading fails.



# Documentation of function `readBinary`
Function usage: Read a file in binary mode and return raw binary data as a `std::vector<uint8_t>`.

Function implementation:
```cpp
FBINARY readBinary(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);        
    std::ifstream ifs;
    try {
        ifs.open(name, std::ios::binary);
    } catch(...) {
        F_THROW_OPENFAIL(name);
    }
    try {
        return std::vector<uint8_t>(
            std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>()
        );
    } catch(...) {
        F_THROW_READFAIL(name);
    }
}
```
**`std::ios::binary`**: Opens file in binary mode to avoid data corruption.
**`std::istreambuf_iterator<char>`**: Reads raw bytes directly from the stream buffer.
**`FBINARY`**: Alias of `const std::vector<uint8_t>&` for binary data.
**Exceptions thrown**:
- `FileNotFoundException`: if file does not exist.
- `FileOpenFailException`: if file cannot be opened.
- `FileReadFailException`: if binary reading fails.