/* Core file write functions. */

#pragma once
#include <fstream>
#include "fexcept.hpp"
#include "fattr.hpp"
#include <string>

namespace file {
    void writeFile(FNAME name, FSTRING s) {
        /* Write text to a file. */
        if(!exists(name)) F_THROW_NOTFOUND(name);
        std::ofstream ofs;
        try {
            ofs.open(name, std::ios::out);
        } catch(...) {
            F_THROW_OPENFAIL(name);
        }
        try {
            ofs << s;
        } catch(...) {
            F_THROW_WRITEFAIL(name);
        }
    }
    void appendFile(FNAME name, FSTRING s) {
        /* Append text to a file. */
        if(!exists(name)) F_THROW_NOTFOUND(name);
        std::ofstream ofs;
        try {
            ofs.open(name, std::ios::app);
        } catch(...) {
            F_THROW_OPENFAIL(name);
        }
        try {
            ofs << s;
        } catch(...) {
            F_THROW_WRITEFAIL(name);
        }
    }
    void writeBinary(FNAME name, FBINARY bin) {
        /* Write binary to a file. */
        if(!exists(name)) F_THROW_NOTFOUND(name);
        std::ofstream ofs;
        try {
            ofs.open(name, std::ios::binary);
        } catch(...) {
            F_THROW_OPENFAIL(name);
        }
        try {
            // Write binary, cast vector to binary data.
            ofs.write((const char*)bin.data(), bin.size());
        } catch(...) {
            F_THROW_WRITEFAIL(name);
        }
    }
}