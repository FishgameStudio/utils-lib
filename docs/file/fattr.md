# Documentation for fnuction `exists`

function usage: for judge wether the file exists.

function implementation:
```cpp
bool exists(FNAME name) {
    return std::filesystem::exists(name);
}
```
**`FNAME`**: an alias of `const std::string&`
**`std::filesystem::exists`**: a function for judge wether the file exists.

# Documentation of function `isRegular` 

function usage: judge wether the file is a regular file(no hidden, no high permission).

implementation:
```cpp
bool isRegular(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);
    return std::filesystem::is_regular_file(name);
}
```
**`F_THROW_NOTFOUND`**: A macro, throw exception `FileNotFoundException` when nonexist.
**`std::filesystem::is_regular_file`**: A function to judgde wether the file is regular.

# Documentation of function `relativePathOf`

Function usage: returns the relative path of a specified file.
**e.g.**: (Hypothesis the current working path is /usr/me)
/usr/me/doc/a.txt -> doc/a.txt
/usr/me/abc.md    -> abc.md

Implementation:
```cpp
std::string relativePathOf(FNAME name) {    
    if (!exists(name)) F_THROW_NOTFOUND(name);
    return std::filesystem::relative(name).string();
    }
```
**`std::filesystem::relative`** returns the relative path of a path. Note: the type of the return is `std::filesystem::path`
**`.string()`**: Convert `std::filesystem::path` to `std::string`.


# Documentation of function `absPathOf`
Function usage: Return the absolute path of the specified file.
**e.g.** : (Hypothesis the current working path is /usr/me)
abc.md     -> /usr/me/abc.md
doc/a.txt  -> /usr/me/doc/a.txt

Function implementation:
```cpp
std::string absPathOf(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);
    return std::filesystem::absolute(name).string();
}
```
**`std::filesystem::absolute`**: Returns the absolute path of a path.
**`.string()`**: Convert `std::filesystem::path` to `std::string`.

# Documentation of function `extensionOf`
Function usage: Return the file extension (suffix) of the specified file.
**e.g.** :
abc.txt -> .txt
archive.tar.gz -> .gz
document -> (empty string)

Function implementation:
```cpp
std::string extensionOf(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);
    return std::filesystem::path(name).extension().string();
}
```
**`std::filesystem::path::extension`**: Gets the extension part of a path.
**`.string()`**: Convert `std::filesystem::path` to `std::string`.

# Documentation of function `stemOf`
Function usage: Return the file stem (filename without extension) of the specified file.
**e.g.** :
abc.txt -> abc
archive.tar.gz -> archive.tar
document -> document

Function implementation:
```cpp
std::string stemOf(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);
    return std::filesystem::path(name).stem().string();
}
```
**`std::filesystem::path::stem`**: Gets the stem part of a path (filename without extension).
**`.string()`**: Convert `std::filesystem::path` to `std::string`.

# Documentation of function `size`
Function usage: Return the total size of the specified file in bytes.

Function implementation:
```cpp
size_t size(FNAME name) {
    size_t res=0;
    try {
        res = static_cast<uint64_t>(std::filesystem::file_size(name));
    } catch(...) {
        F_THROW_NOTFOUND(name);
    }
    return res;
}
```
**`std::filesystem::file_size`**: Gets the size of a file in bytes.
**`static_cast<uint64_t>`**: Ensure type compatibility for large file sizes.
**`try-catch`**: Capture errors and throw a unified file exception.

# Documentation of function `isHidden`
Function usage: Judge whether the specified file is hidden (cross-platform).
- Windows: Files with `FILE_ATTRIBUTE_HIDDEN` attribute
- Linux/macOS: Files starting with `.`

Function implementation:
```cpp
bool isHidden(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);
    #ifdef _WIN32
    DWORD attr = GetFileAttributesA(name.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) F_THROW_INVALIDATTR(name);
    return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
    #else
    const std::filesystem::path path(name);
    auto namestring = path.filename().string();
    return !namestring.empty() && name.front() == '.';
    #endif
}
```
**`GetFileAttributesA`**: Windows API to get file attributes.
**`FILE_ATTRIBUTE_HIDDEN`**: Windows hidden file flag.
**Linux/macOS rule**: Filename starts with `.` means hidden.

# Documentation of function `isReadOnly`
Function usage: Judge whether the specified file is read-only (cross-platform).

Function implementation:
```cpp
bool isReadOnly(FNAME name) {
    if (!exists(name)) F_THROW_NOTFOUND(name);
    #ifdef _WIN32
    DWORD attr = GetFileAttributesA(name.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        F_THROW_INVALIDATTR(name);
    }
    return (attr & FILE_ATTRIBUTE_READONLY) != 0;
    #else
    struct stat fileStat{};
    if (stat(name.c_str(), &fileStat) != 0) {
        F_THROW_NOTFOUND(name);
    }
    return (fileStat.st_mode & S_IWUSR) == 0;
    #endif
}
```
**`FILE_ATTRIBUTE_READONLY`**: Windows read-only flag.
**`S_IWUSR`**: Linux/macOS owner write permission bit.
**`stat`**: Linux/macOS system call to get file status.

# Documentation of function `modifyTime`
Function usage: Return the latest modification timestamp of the file (in seconds).

Function implementation:
```cpp
int64_t modifyTime(const std::filesystem::path& p) {
    auto tp = std::filesystem::last_write_time(p);
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        tp - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
    );
    return std::chrono::duration_cast<std::chrono::seconds>(sctp.time_since_epoch()).count();
}
```
**`std::filesystem::last_write_time`**: Get the last modification time of a file.
**`time_point_cast`**: Convert file clock to system clock (cross-platform compatible).
**`duration_cast<std::chrono::seconds>`**: Convert time to second-level timestamp.
**Return**: Unix timestamp (seconds since 1970-01-01).