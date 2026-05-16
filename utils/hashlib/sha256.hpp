/* SHA 256 implementation */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>

namespace hashlib {
    // SHA256 constant K.
    const uint32_t K[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,
        0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
        0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,
        0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
        0xc4f57f17,0xc9b00a25,0xd192e819,0xd6990624,
        0xf40e3585,0x106aa070,0x19a4c116,0x1e376c08,
        0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
        0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,
        0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,
        0xbef9a3f7,0xc67178f2
    };

    // Right-shift loop.
    inline uint32_t rotr(uint32_t x, int n) {
        return (x >> n) | (x << (32 - n));
    }

    // Σ0, Σ1, σ0, σ1(SHA256 core algorithm)
    inline uint32_t sig0(uint32_t x) {
        return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
    }
    inline uint32_t sig1(uint32_t x) {
        return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
    }
    inline uint32_t ep0(uint32_t x) {
        return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
    }
    inline uint32_t ep1(uint32_t x) {
        return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
    }
    inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
        return (x & y) ^ (~x & z);
    }
    inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
        return (x & y) ^ (x & z) ^ (y & z);
    }

    // SHA256 main function.
    std::string sha256(const std::string& input) {
        /* Initial hash value */
        uint32_t h[8] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };

        /* Preprocess: fill + resize */
        std::vector<uint8_t> msg(input.begin(), input.end());
        uint64_t bit_len = msg.size() * 8;

        /* Fill 0x80 */
        msg.push_back(0x80);
        // Fill 0 until (448 mod 512)
        while ((msg.size() * 8) % 512 != 448)
            msg.push_back(0x00);
        // Append 64 bits(big-endian)
        for (int i = 7; i >= 0; --i)
            msg.push_back((bit_len >> (i * 8)) & 0xFF);

        /* Parse parts, each part has 512 bits(64bytes). */
        for (size_t i = 0; i < msg.size(); i += 64) {
            uint32_t w[64] = {0};
            // Split to 16 32bits-big-endian numbers.
            for (int j = 0; j < 16; ++j) {
                w[j] = (msg[i + j*4] << 24) | (msg[i + j*4+1] << 16) |
                        (msg[i + j*4+2] << 8) | msg[i + j*4+3];
            }
            // Expand to 64
            for (int j = 16; j < 64; ++j) {
                w[j] = sig1(w[j-2]) + w[j-7] + sig0(w[j-15]) + w[j-16];
            }
            // Initialize working variables.
            uint32_t a=h[0], b=h[1], c=h[2], d=h[3];
            uint32_t e=h[4], f=h[5], g=h[6], hh=h[7];
            // zip for 64 loops.
            for (int j = 0; j < 64; ++j) {
                uint32_t t1 = hh + ep1(e) + ch(e,f,g) + K[j] + w[j];
                uint32_t t2 = ep0(a) + maj(a,b,c);
                hh = g; g = f; f = e; e = d + t1;
                d = c; c = b; b = a; a = t1 + t2;
            }
            // Update the hash value.
            h[0] += a; h[1] += b; h[2] += c; h[3] += d;
            h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
        }

        /* Finish */
        std::ostringstream oss;
        for (int i = 0; i < 8; ++i)
            oss << std::hex << std::setw(8) << std::setfill('0') << h[i];
        return oss.str();
    }

}