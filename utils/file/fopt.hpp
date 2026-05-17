/* Core file & directory operations */
#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include "fexcept.hpp"
#include "fattr.hpp"
#include "fopt_tempfile.hpp"

namespace file {
    DIRPATH getWorkingDir() {
        /* Get the current working directory. */
        try {
            return std::filesystem::current_path().string();
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to get current working directory: " + std::string(e.what()));
        }
    }
    void chdir(DIRPATH path) {
        /* Set the current working directory. */
        if (!exists(path)) F_THROW_NOTFOUND(path);
        try {
            std::filesystem::current_path(path);
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to change directory to '" + (std::string)path + "': " + std::string(e.what()));
        }
    }
    void copy(FNAME src, FPATH dst) {
        /* Copy a file from one location to another. */
        if (!exists(src)) F_THROW_NOTFOUND(src);
        try {
            std::filesystem::copy(src, dst);
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to copy file from '" + (std::string)src + "' to '" + dst.string() + "': " + std::string(e.what()));
        }
    }
    void move(FNAME src, FPATH dst) {
        /* Move a file from one location to another. */
        if (!exists(src)) F_THROW_NOTFOUND(src);
        if (!exists(dst)) F_THROW_NOTFOUND(dst.string());
        try {
            std::filesystem::rename(src, dst);
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to move file from '" + std::string(src) + "' to '" + dst.string() + "': " + std::string(e.what()));
        }
    }
    void rename(FNAME src, FPATH new_name) {
        /* Rename a file. */
        if (!exists(src)) F_THROW_NOTFOUND(src);
        if (src == new_name) return; // No need to rename if the name is the same
        try {
            std::filesystem::rename(src, new_name);
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to rename file from '" + std::string(src) + "' to '" + new_name.string() + "': " + std::string(e.what()));
        }
    }
    bool isValidFilename(FNAME name) {
        #ifndef _WIN32
            return name.find('/') == std::string::npos && name.find('\0') == std::string::npos;
        #else
            static const std::string invalidChars = "\\/:*?\"<>|";
            for (char c : name) {
                if (c == '\0') continue; // null char is invalid but we check it separately
                if (std::find(
                    invalidChars.begin(), invalidChars.end(), c
                ) != invalidChars.end()) return false;
            }
            return true;
        #endif
    }
    void makeDir(DIRPATH path) {
        /* Create a new directory. */
        if (exists(path)) return;
        try {
            std::filesystem::create_directories(path);
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to create directory '" + (std::string)path + "': " + std::string(e.what()));
        }
    }
    void removeFile(FNAME path) {
        /* Remove a file. */
        if (!exists(path)) F_THROW_NOTFOUND(path);
        try {
            std::filesystem::remove(path);
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to remove file '" + (std::string)path + "': " + std::string(e.what()));
        }
    }
    void removeDir(DIRPATH path) {
        /* Remove a directory and all its contents. */
        if (!exists(path)) F_THROW_NOTFOUND(path);
        try {
            std::filesystem::remove_all(path); // remove all contents of the directory
        } catch (const std::filesystem::filesystem_error& e) {
            throw FileException("Failed to remove directory '" + (std::string)path + "': " + std::string(e.what()));
        }
    }

}