/* File exceptions & constants. */

#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include <filesystem>

namespace file {
    using FNAME = const std::string&;
    using FSTRING = const std::string&;
    using FBINARY = const std::vector<uint8_t>&;
    using FPATH = const std::filesystem::path&;
    using DIRPATH = const std::string&;

    class FileNotFoundException : public std::runtime_error {
    public:
        explicit FileNotFoundException(std::string msg) 
        : std::runtime_error("File or directory not found: " + (std::string)msg) {}
    };
    class FileReadFailException : public std::runtime_error {
    public:
        explicit FileReadFailException(std::string msg) 
        : std::runtime_error("Failed to read file: " + (std::string)msg) {}
    };
    class FileWriteFailException : public std::runtime_error {
    public:
        explicit FileWriteFailException(std::string msg) 
        : std::runtime_error("Failed to write file: " + (std::string)msg) {}
    };
    class FileOpenFailException : public std::runtime_error {
    public:
        explicit FileOpenFailException(std::string msg) 
        : std::runtime_error("Failed to open file: " + (std::string)msg) {}
    };
    class FileInvalidAttributesException : public std::runtime_error {
    public:
        explicit FileInvalidAttributesException(std::string msg) 
        : std::runtime_error("Invalid attributes of file: " + (std::string)msg) {}
    };
    class FileException : public std::runtime_error {
    public:
        explicit FileException(std::string msg) 
        : std::runtime_error("File or directory error: " + (std::string)msg) {}
    };
    
}

#define F_THROW_NOTFOUND(msg)    throw FileNotFoundException(msg)
#define F_THROW_READFAIL(msg)    throw FileReadFailException(msg)
#define F_THROW_WRITEFAIL(msg)   throw FileWriteFailException(msg)
#define F_THROW_OPENFAIL(msg)    throw FileOpenFailException(msg)
#define F_THROW_INVALIDATTR(msg) throw FileInvalidAttributesException(msg)

