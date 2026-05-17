# Documentation for MD5 Hash Module
Function usage: Implements the standard **MD5 cryptographic hash algorithm**, converts any input data into a fixed 32‑character hexadecimal hash string.


# Documentation of Class `MD5`
Function usage: Full MD5 hash calculator class. Provides update, finalize, and string output interfaces.
Member variables:
- `state[4]`: MD5 core 128‑bit state (ABCD)
- `buffer[64]`: 64‑byte block buffer
- `count[2]`: 64‑bit input length counter
- `digest[16]`: Final 16‑byte MD5 result


# Documentation of function `F`
Function usage: MD5 round 1 logical function.
Implementation:
```cpp
uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | (~x & z);
}
```


# Documentation of function `G`
Function usage: MD5 round 2 logical function.
Implementation:
```cpp
uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
    return (x & z) | (y & ~z);
}
```


# Documentation of function `H`
Function usage: MD5 round 3 logical function (XOR).
Implementation:
```cpp
uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}
```


# Documentation of function `I`
Function usage: MD5 round 4 logical function.
Implementation:
```cpp
uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
    return y ^ (x | ~z);
}
```


# Documentation of function `ROTATE_LEFT`
Function usage: 32‑bit cyclic left shift (core MD5 bit mixing).
Implementation:
```cpp
uint32_t ROTATE_LEFT(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
}
```


# Documentation of Macro `FF`
Function usage: MD5 round 1 operation macro.
```cpp
#define FF(a,b,c,d,x,s,ac)
```


# Documentation of Macro `GG`
Function usage: MD5 round 2 operation macro.


# Documentation of Macro `HH`
Function usage: MD5 round 3 operation macro.


# Documentation of Macro `II`
Function usage: MD5 round 4 operation macro.


# Documentation of Constructor `MD5()`
Function usage: Initialize MD5 state with standard initial vector.
Implementation:
```cpp
MD5::MD5() {
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
    count[0] = count[1] = 0;
    memset(buffer, 0, 64);
}
```


# Documentation of function `transform`
Function usage: MD5 core compression function. Processes 64‑byte block.
Implementation:
```cpp
void MD5::transform(const unsigned char block[64]);
```
Steps:
1. Decode block to 16 × 32‑bit words
2. 4 rounds × 16 steps of FF/GG/HH/II
3. Update ABCD state


# Documentation of function `encode`
Function usage: Convert `uint32_t` array to little‑endian `unsigned char` array.
```cpp
void encode(const uint32_t* input, unsigned char* output, int len);
```


# Documentation of function `decode`
Function usage: Convert little‑endian `unsigned char` to `uint32_t` array.
```cpp
void decode(const unsigned char* input, uint32_t* output, int len);
```


# Documentation of function `update`
Function usage: Feed input data into MD5 incrementally.
```cpp
void update(const unsigned char* input, uint32_t inputLen);
```


# Documentation of function `finalize`
Function usage: Finish MD5 calculation: padding + append length + generate digest.
```cpp
void finalize();
```


# Documentation of function `toString`
Function usage: Output 16‑byte digest as 32‑character lowercase hex string.
```cpp
std::string toString();
```
Example:
`"hello"` → `"5d41402abc4b2a76b9719d911017c592"`