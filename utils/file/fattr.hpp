/* File attributes functions. */

#pragma once
#include <filesystem>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

namespace file {
    using FNAME = const std::string&;

    bool exists(FNAME name) {
        return std::filesystem::exists(name);
    }
    bool isRegular(FNAME name) {
        if (!exists(name)) return false;
        return std::filesystem::is_regular_file(name);
    }
    bool isReadOnly(FNAME name) {
        if (!exists(name)) return false;
        #ifdef _WIN32
        DWORD attr = GetFileAttributesA(name.c_str());
        // Invalid file attributes
        if (attr == INVALID_FILE_ATTRIBUTES) {
            return false; // File not found / permission denied.
        }
        /* Read-only mark: FILE_ATTRIBUTE_READONLY */
        return (attr & FILE_ATTRIBUTE_READONLY) != 0;
        #else
        struct stat fileStat{};

        if (stat(name.c_str(), &fileStat) != 0) {
            return false; // File not fonud
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
        } catch (...) {
            return 0;
        }
        return res;
    }
}