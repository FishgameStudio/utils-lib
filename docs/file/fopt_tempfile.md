# Documentation for Temporary File Operations
Function usage: Provides a safe, automatic temporary file management class. Creates, reads, and auto‑cleans up temporary files.


# Documentation of Class `TempFile`
Function usage: Represents a temporary file that is **automatically deleted** when the object is destroyed.
Supports custom paths or auto‑generated unique temp files.

## Private Member
`std::string name`
Stores the full path of the temporary file.


# Documentation of Constructor `TempFile`
Function usage: Creates a new temporary file.
If no filename is provided, auto‑generates a unique name in the system temp directory.

Implementation:
```cpp
TempFile(std::string file = "");
```

**Logic**:
1. If filename is empty:
   - Generate unique name using timestamp + random number.
   - Place it in the system temp directory.
2. If the file does not exist, create it.
3. Throw `FileOpenFailException` if creation fails.


# Documentation of Method `getContent`
Function usage: Read the full text content of the temporary file.
Implementation:
```cpp
FSTRING getContent() const;
```
**Return**: File content as `const std::string&`.
**Uses**: `file::readFile`


# Documentation of Method `getBinary`
Function usage: Read raw binary data from the temporary file.
Implementation:
```cpp
FBINARY getBinary() const;
```
**Return**: Binary data as `const std::vector<uint8_t>&`.
**Uses**: `file::readBinary`


# Documentation of Method `getName`
Function usage: Get the full path of the temporary file.
Implementation:
```cpp
std::string getName() const;
```
**Return**: Full path string.


# Documentation of Method `remove`
Function usage: Manually delete the temporary file.
Implementation:
```cpp
void remove();
```
**Exception**: Throws `FileException` if deletion fails.


# Documentation of Destructor `~TempFile`
Function usage: **Automatically deletes the temporary file** when the object goes out of scope.
Implementation:
```cpp
~TempFile();
```
**Behavior**:
- Silently ignores errors during cleanup.
- Guarantees no leftover temporary files.