#include <string>
#include <vector>
#include <array>
#include <cstdint>

namespace hashlib
{
    /*
     * Rotate right 64-bit integer
     */
    constexpr uint64_t rotr64(uint64_t val, int shift) {
        return (val >> shift) | (val << (64 - shift));
    }

    /*
     * SHA-512 constant table
     */
    inline constexpr std::array<uint64_t, 80> K512 = {
        0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
        0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118,
        0xD807AA98A3030242, 0x12835B01457E72BE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
        0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694,
        0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
        0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
        0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
        0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70,
        0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
        0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353E,
        0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
        0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
        0x19A4C116B8D2D0C8, 0x1E376C0851CAEDAD, 0x2748774C85A06E49, 0x34B0BCB5E19B48A8,
        0x391C0CB3C5C95A63, 0x4ED8AA4A3418F31E, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3,
        0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
        0x90BEFFFA23631E28, 0xA450E19917C2105C, 0xBEF9A3F7BD2EC755, 0xC0ABBEE6A369218F,
        0xC88D17F2E6ADE698, 0xD58A797277E0E188, 0xDEA88D8C0A6510FA, 0xE7169D9145719359,
        0xF1CE47EE47638406, 0x1A0AD6FBF321C287, 0x1F2BB727B04772C8, 0x272B0A394A277A77,
        0x2B272CA2771B2F88, 0x32CA5E86BE446654, 0x3CB9E0A1C5BBE2D3, 0x431D67C49C100D4C,
        0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817
    };

    /** 
     * SHA-512 core hash function
     * @input: raw byte data
     * @return: 64-byte SHA512 digest
     */
    inline std::array<uint8_t, 64> __sha512(const std::vector<uint8_t>& data) {
        uint64_t h0 = 0x6A09E667F3BCC908;
        uint64_t h1 = 0xBB67AE8584CAA73B;
        uint64_t h2 = 0x3C6EF372FE94F82B;
        uint64_t h3 = 0xA54FF53A5F1D36F1;
        uint64_t h4 = 0x510E527FADE682D1;
        uint64_t h5 = 0x9B05688C2B3E6C1F;
        uint64_t h6 = 0x1F83D9ABFB41BD6B;
        uint64_t h7 = 0x5BE0CD19137E2179;

        uint64_t bit_len = static_cast<uint64_t>(data.size()) * 8ULL;
        std::vector<uint8_t> msg = data;

        /* Append 0x80 end marker */
        msg.push_back(0x80);

        /* Pad zero bytes */
        while ((msg.size() * 8 + 128) % 1024 != 0) {
            msg.push_back(0x00);
        }

        /* Append original bit length (big-endian 128-bit) */
        for (int i = 15; i >= 0; --i) {
            msg.push_back(static_cast<uint8_t>((bit_len >> (i * 8)) & 0xFF));
        }

        /* Process each 128-byte block */
        for (size_t offset = 0; offset < msg.size(); offset += 128) {
            std::array<uint64_t, 80> w{};

            /* Split block into first 16 64-bit words */
            for (int i = 0; i < 16; ++i) {
                w[i] =
                    (static_cast<uint64_t>(msg[offset + i*16 + 0]) << 56) |
                    (static_cast<uint64_t>(msg[offset + i*16 + 1]) << 48) |
                    (static_cast<uint64_t>(msg[offset + i*16 + 2]) << 40) |
                    (static_cast<uint64_t>(msg[offset + i*16 + 3]) << 32) |
                    (static_cast<uint64_t>(msg[offset + i*16 + 4]) << 24) |
                    (static_cast<uint64_t>(msg[offset + i*16 + 5]) << 16) |
                    (static_cast<uint64_t>(msg[offset + i*16 + 6]) << 8)  |
                    (static_cast<uint64_t>(msg[offset + i*16 + 7]) << 0);
            }

            /* Extend to 80 words */
            for (int i = 16; i < 80; ++i) {
                uint64_t s0 = rotr64(w[i-15], 1) ^ rotr64(w[i-15], 8) ^ (w[i-15] >> 7);
                uint64_t s1 = rotr64(w[i-2], 19) ^ rotr64(w[i-2], 61) ^ (w[i-2] >> 6);
                w[i] = w[i-16] + s0 + w[i-7] + s1;
            }

            uint64_t a = h0, b = h1, c = h2, d = h3;
            uint64_t e = h4, f = h5, g = h6, h = h7;

            /* Main compression loop */
            for (int i = 0; i < 80; ++i) {
                uint64_t s1 = rotr64(e, 14) ^ rotr64(e, 18) ^ rotr64(e, 41);
                uint64_t ch = (e & f) ^ (~e & g);
                uint64_t temp1 = h + s1 + ch + K512[i] + w[i];

                uint64_t s0 = rotr64(a, 28) ^ rotr64(a, 34) ^ rotr64(a, 39);
                uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
                uint64_t temp2 = s0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            /* Add compressed values to hash state */
            h0 += a; h1 += b; h2 += c; h3 += d;
            h4 += e; h5 += f; h6 += g; h7 += h;
        }

        /* Serialize hash result to big-endian 64-byte digest */
        std::array<uint8_t, 64> out{};
        auto write_u64 = [&](uint64_t val, size_t pos) {
            for (int i = 0; i < 8; ++i)
                out[pos + i] = static_cast<uint8_t>((val >> (56 - i*8)) & 0xFF);
        };
        write_u64(h0, 0);
        write_u64(h1, 8);
        write_u64(h2, 16);
        write_u64(h3, 24);
        write_u64(h4, 32);
        write_u64(h5, 40);
        write_u64(h6, 48);
        write_u64(h7, 56);
        return out;
    }

    /*
     * Convert SHA512 binary digest to lowercase hex string
     */
    inline std::string sha512(const std::string& plain_text) {
        std::vector<uint8_t> buf(plain_text.begin(), plain_text.end());
        auto digest = __sha512(buf);
        const char hex_tab[] = "0123456789abcdef";
        std::string res;
        res.reserve(128);
        for (uint8_t b : digest) {
            res += hex_tab[(b >> 4) & 0x0F];
            res += hex_tab[b & 0x0F];
        }
        return res;
    }
}
