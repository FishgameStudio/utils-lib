/* File read functions implementation. */

#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include "fexcept.hpp"
#include "fattr.hpp"

namespace file {
    std::string readFile(FNAME name) {
        /* Read the file & return the text. */
        if (!exists(name)) F_THROW_NOTFOUND(name);
        std::ifstream ifs;
        try {
            ifs.open(name);
        } catch(...) {
            F_THROW_OPENFAIL(name);
        }
        std::string s;
        try {
            ifs >> s;
        } catch(...) {
            F_THROW_READFAIL(name);
        }
        return s;
    }
    std::vector<uint8_t> readBinary(FNAME name) {
        /* Read the file & return the bytes. */
        if (!exists(name)) F_THROW_NOTFOUND(name);
        std::ifstream ifs;
        try {
            ifs.open(name, std::ios::binary);
        } catch(...) {
            F_THROW_OPENFAIL(name);
        }
        try {
            return std::vector<uint8_t>(
                std::istreambuf_iterator<char>(ifs),
                std::istreambuf_iterator<char>()
            );
        } catch(...) {
            F_THROW_READFAIL(name);
        }
        return {};
    }
    
} // namespace file

