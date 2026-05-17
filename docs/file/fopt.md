# Documentation of function `getWorkingDir`
Function usage: Get the current working directory path.
Implementation:
```cpp
DIRPATH getWorkingDir() {
    try {
        return std::filesystem::current_path().string();
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileException("Failed to get current working directory: " + std::string(e.what()));
    }
}
```
**Return**: Current working directory path as `DIRPATH`.
**Exception**: `FileException` if system call fails.

# Documentation of function `chdir`
Function usage: Change the current working directory.
Implementation:
```cpp
void chdir(DIRPATH path) {
    if (!exists(path)) F_THROW_NOTFOUND(path);
    try {
        std::filesystem::current_path(path);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**:
- `FileNotFoundException`: Path does not exist.
- `FileException`: Change directory fails.

# Documentation of function `copy`
Function usage: Copy a file from source to destination.
Implementation:
```cpp
void copy(FNAME src, FPATH dst) {
    if (!exists(src)) F_THROW_NOTFOUND(src);
    try {
        std::filesystem::copy(src, dst);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**:
- `FileNotFoundException`: Source file not found.
- `FileException`: Copy fails.

# Documentation of function `move`
Function usage: Move a file to another path.
Implementation:
```cpp
void move(FNAME src, FPATH dst) {
    if (!exists(src)) F_THROW_NOTFOUND(src);
    if (!exists(dst)) F_THROW_NOTFOUND(dst.string());
    try {
        std::filesystem::rename(src, dst);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**:
- `FileNotFoundException`: Source or destination not exist.
- `FileException`: Move fails.

# Documentation of function `rename`
Function usage: Rename a file or directory.
Implementation:
```cpp
void rename(FNAME src, FPATH new_name) {
    if (!exists(src)) F_THROW_NOTFOUND(src);
    if (src == new_name) return;
    try {
        std::filesystem::rename(src, new_name);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**:
- `FileNotFoundException`: Source not exist.
- `FileException`: Rename fails.

# Documentation of function `isValidFilename`
Function usage: Check if a filename is valid (cross-platform).
- Windows: Invalid chars: `\ / : * ? " < > |`
- Linux/macOS: Invalid char: `/`
Implementation:
```cpp
bool isValidFilename(FNAME name) {
    #ifndef _WIN32
        return name.find('/') == std::string::npos && name.find('\0') == std::string::npos;
    #else
        static const std::string invalidChars = "\\/:*?\"<>|";
        for (char c : name) {
            if (c == '\0') continue;
            if (std::find(invalidChars.begin(), invalidChars.end(), c) != invalidChars.end())
                return false;
        }
        return true;
    #endif
}
```
**Return**: `true` if valid, `false` otherwise.

# Documentation of function `makeDir`
Function usage: Create a directory (supports multi-level directories).
Implementation:
```cpp
void makeDir(DIRPATH path) {
    if (exists(path)) return;
    try {
        std::filesystem::create_directories(path);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**: `FileException` if creation fails.

# Documentation of function `removeFile`
Function usage: Delete a single file.
Implementation:
```cpp
void removeFile(FNAME path) {
    if (!exists(path)) F_THROW_NOTFOUND(path);
    try {
        std::filesystem::remove(path);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**:
- `FileNotFoundException`: File not exist.
- `FileException`: Deletion fails.

# Documentation of function `removeDir`
Function usage: Delete a directory and all its contents (recursive).
Implementation:
```cpp
void removeDir(DIRPATH path) {
    if (!exists(path)) F_THROW_NOTFOUND(path);
    try {
        std::filesystem::remove_all(path);
    } catch (...) {
        throw FileException("...");
    }
}
```
**Exception**:
- `FileNotFoundException`: Directory not exist.
- `FileException`: Deletion fails.