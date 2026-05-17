/* Base64 encode & decode functions. */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>


// Base64 standard charset
static const std::string BASE64_CHARS = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

// Check if char is valid base64
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

// Encode bytes to Base64 string
std::string base64_encode(const uint8_t* bytes_to_encode, size_t len) {
  std::string ret;
  int i = 0;
  uint32_t val = 0;
  int bits = 0;

  // Core: pack 3 bytes into 4 Base64 chars
  while (len--) {
    val = (val << 8) | *(bytes_to_encode++);
    bits += 8;

    // Extract 6 bits each time
    while (bits >= 6) {
      bits -= 6;
      ret += BASE64_CHARS[(val >> bits) & 0x3F];
    }
  }

  // Handle remaining bits and padding
  if (bits > 0) {
    val <<= (6 - bits);
    ret += BASE64_CHARS[val & 0x3F];
  }
  while (ret.size() % 4) ret += '=';

  return ret;
}

// Overload: encode string directly
std::string base64_encode(const std::string& s) {
  return base64_encode(reinterpret_cast<const uint8_t*>(s.data()), s.size());
}

// Decode Base64 string back to bytes
std::vector<uint8_t> base64_decode(const std::string& encoded) {
  std::vector<uint8_t> ret;
  int i = 0;
  uint32_t val = 0;
  int bits = 0;

  // Core: decode 4 chars back to 3 bytes
  for (char c : encoded) {
    if (c == '=') break;
    if (!is_base64(c)) continue;

    val = (val << 6) | *std::find(BASE64_CHARS.begin(), BASE64_CHARS.end(), c);
    bits += 6;

    if (bits >= 8) {
      bits -= 8;
      ret.push_back((val >> bits) & 0xFF);
    }
  }

  return ret;
}

// Convert decoded bytes to string
std::string decode_to_string(const std::string& encoded) {
  std::vector<uint8_t> bytes = base64_decode(encoded);
  // Construct string from byte buffer: reinterpret bytes as chars
  if (bytes.empty()) return "";
  return std::string(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

// Test
int main() {
  std::string original = "Hello, Base64!";
  std::string encoded = base64_encode(original);
  std::string decoded = decode_to_string(encoded);

  std::cout << "Original: " << original << std::endl;
  std::cout << "Encoded:  " << encoded << std::endl;
  std::cout << "Decoded:  " << decoded << std::endl;

  return 0;
}