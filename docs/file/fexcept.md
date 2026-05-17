# Documentation for Header File `fexcept.hpp`
Function usage: Defines all file-related custom exceptions and type aliases for the file module. All exceptions inherit from `std::runtime_error` and provide clear error messages.



# Documentation of Type Alias `FNAME`
Usage: Alias for `const std::string&`, used to represent file names / file paths.
**Definition**:
```cpp
using FNAME = const std::string&;
```

# Documentation of Type Alias `FSTRING`
Usage: Alias for `const std::string&`, used to represent general string parameters.
**Definition**:
```cpp
using FSTRING = const std::string&;
```

# Documentation of Type Alias `FBINARY`
Usage: Alias for `const std::vector<uint8_t>&`, used to represent binary data buffers.
**Definition**:
```cpp
using FBINARY = const std::vector<uint8_t>&;
```

# Documentation of Type Alias `FPATH`
Usage: Alias for `const std::filesystem::path&`, used to manage long file pathes.
**Definition**:
```cpp
using FPATH = const std::filesystem::path&;
```


# Documentation of Type Alias `DIRPATH`
Usage: Alias for `const std::string&`, used to return a long path.
**Definition**:
```cpp
DIRPATH = const std::string&;
```


# Documentation of Exception `FileNotFoundException`
Function usage: Thrown when a target file does not exist.
Implementation:
```cpp
class FileNotFoundException : std::runtime_error {
public:
    explicit FileNotFoundException(std::string msg) 
    : runtime_error("File not found: " + msg) {}
};
```
**Base class**: `std::runtime_error`
**Message format**: `File not found: [path]`



# Documentation of Exception `FileReadFailException`
Function usage: Thrown when reading a file fails (permission denied, corrupted, occupied, etc.).
Implementation:
```cpp
class FileReadFailException : std::runtime_error {
public:
    explicit FileReadFailException(std::string msg) 
    : runtime_error("Failed to read file: " + msg) {}
};
```
**Base class**: `std::runtime_error`
**Message format**: `Failed to read file: [path]`



# Documentation of Exception `FileWriteFailException`
Function usage: Thrown when writing to a file fails (read-only, disk full, permission denied).
Implementation:
```cpp
class FileWriteFailException : std::runtime_error {
public:
    explicit FileWriteFailException(std::string msg) 
    : runtime_error("Failed to write file: " + msg) {}
};
```
**Base class**: `std::runtime_error`
**Message format**: `Failed to write file: [path]`



# Documentation of Exception `FileOpenFailException`
Function usage: Thrown when opening a file fails (invalid path, occupied, permission issues).
Implementation:
```cpp
class FileOpenFailException : std::runtime_error {
public:
    explicit FileOpenFailException(std::string msg) 
    : runtime_error("Failed to open file: " + msg) {}
};
```
**Base class**: `std::runtime_error`
**Message format**: `Failed to open file: [path]`



# Documentation of Exception `FileInvalidAttributesException`
Function usage: Thrown when retrieving or processing file attributes fails (Windows/macOS/Linux).
Implementation:
```cpp
class FileInvalidAttributesException : std::runtime_error {
public:
    explicit FileInvalidAttributesException(std::string msg) 
    : runtime_error("Invalid attributes of file: " + msg) {}
};
```
**Base class**: `std::runtime_error`
**Message format**: `Invalid attributes of file: [path]`




# Documentation of Macro `F_THROW_NOTFOUND`
Usage: Shortcut to throw `FileNotFoundException`.
```cpp
#define F_THROW_NOTFOUND(msg) throw FileNotFoundException(msg)
```

# Documentation of Macro `F_THROW_READFAIL`
Usage: Shortcut to throw `FileReadFailException`.
```cpp
#define F_THROW_READFAIL(msg) throw FileReadFailException(msg)
```

# Documentation of Macro `F_THROW_WRITEFAIL`
Usage: Shortcut to throw `FileWriteFailException`.
```cpp
#define F_THROW_WRITEFAIL(msg) throw FileWriteFailException(msg)
```

# Documentation of Macro `F_THROW_OPENFAIL`
Usage: Shortcut to throw `FileOpenFailException`.
```cpp
#define F_THROW_OPENFAIL(msg) throw FileOpenFailException(msg)
```

# Documentation of Macro `F_THROW_INVALIDATTR`
Usage: Shortcut to throw `FileInvalidAttributesException`.
```cpp
#define F_THROW_INVALIDATTR(msg) throw FileInvalidAttributesException(msg)
```