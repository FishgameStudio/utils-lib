/* File attributes functions. */

#pragma once
#include <filesystem>
#include <string>
#include "fexcept.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

namespace file {

    bool exists(FNAME name) {
        return std::filesystem::exists(name);
    }
    bool isRegular(FNAME name) {
        if (!exists(name)) F_THROW_NOTFOUND(name);
        return std::filesystem::is_regular_file(name);
    }
    std::string relativePathOf(FNAME name) {
        // The relative path of a file.
        // e.g. /usr/xxx/abc.txt -> abc.txt
        if (!exists(name)) F_THROW_NOTFOUND(name);
        return std::filesystem::relative(name).string();
    }
    std::string absPathOf(FNAME name) {
        // Returns the absolute path.
        // e.g. abc.txt -> /usr/xxx/abc.txt
        if (!exists(name)) F_THROW_NOTFOUND(name);
        return std::filesystem::absolute(name).string();
    }
    std::string extensionOf(FNAME name) {
        // Returns the extension of the file.
        // abc.txt -> .txt
        if (!exists(name)) F_THROW_NOTFOUND(name);
        return std::filesystem::path(name).extension().string();
    }
    std::string stemOf(FNAME name) {
        // Returns the stem of the file.
        // abc.txt -> abc
        if (!exists(name)) F_THROW_NOTFOUND(name);
        return std::filesystem::path(name).stem().string();
    }
    bool isReadOnly(FNAME name) {
        if (!exists(name)) F_THROW_NOTFOUND(name);
        #ifdef _WIN32
        DWORD attr = GetFileAttributesA(name.c_str());
        // Invalid file attributes
        if (attr == INVALID_FILE_ATTRIBUTES) {
            F_THROW_INVALIDATTR(name);
        }
        /* Read-only mark: FILE_ATTRIBUTE_READONLY */
        return (attr & FILE_ATTRIBUTE_READONLY) != 0;
        
        #else
        struct stat fileStat{};

        if (stat(name.c_str(), &fileStat) != 0) {
            F_THROW_NOTFOUND(name); // File not fonud
        }

        // 0222 = All users not writable -> readonly.
        return (fileStat.st_mode & S_IWUSR) == 0; // Owner unwritable
        #endif
    }
    size_t size(FNAME name) {
        /* Size of the file.(bytes) */
        size_t res=0;
        try {
            res = static_cast<uint64_t>(std::filesystem::file_size(name));
        } catch(...) {
            F_THROW_NOTFOUND(name);
        }
        return res;
    }
    bool isHidden(FNAME name) {
        if (!exists(name)) F_THROW_NOTFOUND(name);
        #ifdef _WIN32
        DWORD attr = GetFileAttributesA(name.c_str());
        if (attr == INVALID_FILE_ATTRIBUTES) F_THROW_INVALIDATTR(name);
        return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
        #else
        const std::filesystem::path path(name);
        auto namestring = path.filename().string();
        // The hidden file starts with '.'.
        return !namestring.empty() && name.front() == '.';

        #endif
    }

}