# Documentation for Base64 Module
Function usage: Implements standard **Base64 encoding & decoding** for strings and binary data.


# Documentation of constant `base64_chars`
Function usage: Standard Base64 alphabet (64 characters).
Definition:
```cpp
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
```
**Logic**: Maps 6‑bit values to printable characters as per Base64 standard.


# Documentation of function `is_base64`
Function usage: Checks if a character is a valid Base64 symbol.
Implementation:
```cpp
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}
```
**Return**: `true` if valid, `false` otherwise.


# Documentation of function `base64_encode` (byte pointer)
Function usage: Encodes raw binary bytes into a Base64 string.
Implementation:
```cpp
string base64_encode(const uint8_t* bytes_to_encode, size_t len)
```
**Logic**:
- Groups **3 input bytes** into **4 output characters** (6 bits each).
- Pads with `=` to make length a multiple of 4.
**Return**: Standard Base64 encoded string.


# Documentation of function `base64_encode` (string overload)
Function usage: Encodes a plain string directly to Base64.
Implementation:
```cpp
string base64_encode(const string& s)
```
**Example**:
`"Hello, Base64!"` → `"SGVsbG8sIEJhc2U2NCE="`


# Documentation of function `base64_decode`
Function usage: Decodes a Base64 string back into raw binary bytes.
Implementation:
```cpp
vector<uint8_t> base64_decode(const string& encoded)
```
**Logic**:
- Converts **4 Base64 chars** back to **3 original bytes**.
- Stops at padding `=`.
- Skips invalid characters.
**Return**: Binary byte vector.


# Documentation of function `decode_to_string`
Function usage: Decodes Base64 and converts result directly to a readable string.
Implementation:
```cpp
string decode_to_string(const string& encoded)
```
**Example**:
`"SGVsbG8sIEJhc2U2NCE="` → `"Hello, Base64!"`
