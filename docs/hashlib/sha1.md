# Documentation for SHA‑1 Hash Module
Function usage: Implements the standard **SHA‑1 cryptographic hash algorithm**, converts any input string into a fixed 40‑character hexadecimal hash string.


# Documentation of function `rotl`
Function usage: Performs **cyclic left shift** for 32‑bit integers (core operation in SHA‑1).
Implementation:
```cpp
constexpr uint32_t rotl(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}
```
**Logic**:
Shift left by `n` bits, move the overflowed high bits to the low bits.
**Why needed**: SHA‑1 standard requires cyclic left shift for mixing bits.


# Documentation of internal function `__sha1`
Function usage: Low‑level SHA‑1 core function, processes binary data and outputs a 20‑byte raw hash.
Implementation:
```cpp
static std::array<uint8_t, 20> __sha1(const std::vector<uint8_t>& input)
```
**Steps**:
1. Initialize five standard hash values `h0 ~ h4`.
2. **Pad the input** to a multiple of 512 bits (SHA‑1 rule).
3. Append the original length (big‑endian).
4. Split into 64‑byte blocks and process each block.
5. Expand each block to 80 words using XOR and cyclic shift.
6. Perform 80 rounds of mixing with 4 stages of logic functions.
7. Update the hash values.
8. Convert final hash to a 20‑byte big‑endian array.
**Return**: Raw 20‑byte SHA‑1 hash.


# Documentation of function `sha1`
Function usage: Public interface for SHA‑1 hash. Input string → output 40‑character hex string.
Implementation:
```cpp
std::string sha1(const std::string& input) {
    const std::vector<uint8_t> bytes(input.begin(), input.end());
    const auto hash = __sha1(bytes);

    std::string hex;
    hex.reserve(40);

    constexpr char digits[] = "0123456789abcdef";
    for (uint8_t b : hash) {
        hex += digits[(b >> 4) & 0x0F];
        hex += digits[b & 0x0F];
    }

    return hex;
}
```
**Logic**:
1. Convert input string to binary bytes.
2. Call core `__sha1` to get raw hash.
3. Convert each byte to two hex characters (0–9, a–f).
4. Return final 40‑character hash string.
**Example**:
`"hello"` → `"aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d"`