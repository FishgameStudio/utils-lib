#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdint>

namespace hashlib {
    // Left-shift during the loop.
    constexpr uint32_t rotl(uint32_t x, uint32_t n) {
        return (x << n) | (x >> (32 - n));
    }

    /* Main function: output a stream of 20bytes. */
    static std::array<uint8_t, 20> __sha1(const std::vector<uint8_t>& input)
    {
        /* Initial hash value */
        uint32_t h0 = 0x67452301;
        uint32_t h1 = 0xEFCDAB89;
        uint32_t h2 = 0x98BADCFE;
        uint32_t h3 = 0x10325476;
        uint32_t h4 = 0xC3D2E1F0;

        const uint64_t original_bit_len = input.size() * 8;

        // fill
        std::vector<uint8_t> msg = input;
        msg.push_back(0x80);

        while ((msg.size() * 8 + 64) % 512 != 0) {
            msg.push_back(0x00);
        }

        /* Append origin length(big-endian) */
        for (int i = 7; i >= 0; --i) {
            msg.push_back(static_cast<uint8_t>(original_bit_len >> (i * 8)));
        }

        /* Parse parts. */
        for (size_t i = 0; i < msg.size(); i += 64)
        {
            std::array<uint32_t, 80> w{};

            // The 16bits in the front.
            for (int j = 0; j < 16; ++j) {
                w[j] = (static_cast<uint32_t>(msg[i + j*4 + 0]) << 24)
                    | (static_cast<uint32_t>(msg[i + j*4 + 1]) << 16)
                    | (static_cast<uint32_t>(msg[i + j*4 + 2]) << 8)
                    | (static_cast<uint32_t>(msg[i + j*4 + 3]) << 0);
            }

            // expend to 80.
            for (int j = 16; j < 80; ++j) {
                w[j] = rotl(w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16], 1);
            }

            uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

            // loop for 4 times.
            for (int j = 0; j < 80; ++j)
            {
                uint32_t f, k;

                if (j < 20) {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                } else if (j < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (j < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                const uint32_t temp = rotl(a, 5) + f + e + k + w[j];
                e = d;
                d = c;
                c = rotl(b, 30);
                b = a;
                a = temp;
            }

            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }

        /* Output 20 bytes. */
        std::array<uint8_t, 20> hash{};
        for (int i = 0; i < 4; ++i) hash[i+0]  = (h0 >> (24 - i*8)) & 0xFF;
        for (int i = 0; i < 4; ++i) hash[i+4]  = (h1 >> (24 - i*8)) & 0xFF;
        for (int i = 0; i < 4; ++i) hash[i+8]  = (h2 >> (24 - i*8)) & 0xFF;
        for (int i = 0; i < 4; ++i) hash[i+12] = (h3 >> (24 - i*8)) & 0xFF;
        for (int i = 0; i < 4; ++i) hash[i+16] = (h4 >> (24 - i*8)) & 0xFF;

        return hash;
    }

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
}
