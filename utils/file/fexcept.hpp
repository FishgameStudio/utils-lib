/* File exceptions & constants. */

#pragma once
#include <string>
#include <stdexcept>
#include <vector>

namespace file {
    using FNAME = const std::string&;
    using FSTRING = const std::string&;
    using FBINARY = const std::vector<uint8_t>&;

    class FileNotFoundException : std::runtime_error {
    public:
        explicit FileNotFoundException(std::string msg) 
        : runtime_error("File not found: " + (std::string)msg) {}
    };
    class FileReadFailException : std::runtime_error {
    public:
        explicit FileReadFailException(std::string msg) 
        : runtime_error("Failed to read file: " + (std::string)msg) {}
    };
    class FileWriteFailException : std::runtime_error {
    public:
        explicit FileWriteFailException(std::string msg) 
        : runtime_error("Failed to write file: " + (std::string)msg) {}
    };
    class FileOpenFailException : std::runtime_error {
    public:
        explicit FileOpenFailException(std::string msg) 
        : runtime_error("Failed to open file: " + (std::string)msg) {}
    };
    class FileInvalidAttributesException : std::runtime_error {
    public:
        explicit FileInvalidAttributesException(std::string msg) 
        : runtime_error("Invalid attributes of file: " + (std::string)msg) {}
    };
    
}

#define F_THROW_NOTFOUND(msg)    throw FileNotFoundException(msg)
#define F_THROW_READFAIL(msg)    throw FileReadFailException(msg)
#define F_THROW_WRITEFAIL(msg)   throw FileWriteFailException(msg)
#define F_THROW_OPENFAIL(msg)    throw FileOpenFailException(msg)
#define F_THROW_INVALIDATTR(msg) throw FileInvalidAttributesException(msg)

