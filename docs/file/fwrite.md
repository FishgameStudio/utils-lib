# Documentation of function `writeFile`
Function usage: Write text content to a file. Overwrites the original content.

Function implementation:
```cpp
void writeFile(FNAME name, FSTRING s) {
    if(!exists(name)) F_THROW_NOTFOUND(name);
    std::ofstream ofs;
    try {
        ofs.open(name, std::ios::out);
    } catch(...) {
        F_THROW_OPENFAIL(name);
    }
    try {
        ofs << s;
    } catch(...) {
        F_THROW_WRITEFAIL(name);
    }
}
```
**`std::ofstream`**: Output file stream for writing files.
**`std::ios::out`**: Open file in overwrite text mode.
**`ofs << s`**: Write string content to file.
**Exceptions**: `FileNotFoundException`, `FileOpenFailException`, `FileWriteFailException`.

---

# Documentation of function `appendFile`
Function usage: Append text content to the end of a file. Does not overwrite original content.

Function implementation:
```cpp
void appendFile(FNAME name, FSTRING s) {
    if(!exists(name)) F_THROW_NOTFOUND(name);
    std::ofstream ofs;
    try {
        ofs.open(name, std::ios::app);
    } catch(...) {
        F_THROW_OPENFAIL(name);
    }
    try {
        ofs << s;
    } catch(...) {
        F_THROW_WRITEFAIL(name);
    }
}
```
**`std::ios::app`**: Open file in append mode.
**`ofs << s`**: Append string to file.
**Exceptions**: `FileNotFoundException`, `FileOpenFailException`, `FileWriteFailException`.

---

# Documentation of function `writeBinary`
Function usage: Write raw binary data to a file.

Function implementation:
```cpp
void writeBinary(FNAME name, FBINARY bin) {
    if(!exists(name)) F_THROW_NOTFOUND(name);
    std::ofstream ofs;
    try {
        ofs.open(name, std::ios::binary);
    } catch(...) {
        F_THROW_OPENFAIL(name);
    }
    try {
        ofs.write((const char*)bin.data(), bin.size());
    } catch(...) {
        F_THROW_WRITEFAIL(name);
    }
}
```
**`std::ios::binary`**: Open file in binary mode.
**`bin.data()`**: Get the pointer of the binary buffer.
**`bin.size()`**: Get the length of binary data.
**`ofs.write(...)`**: Write binary bytes to file.
**Exceptions**: `FileNotFoundException`, `FileOpenFailException`, `FileWriteFailException`.