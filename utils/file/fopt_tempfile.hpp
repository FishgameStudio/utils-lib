/* The temporary file operations. */
#pragma once
#include "fexcept.hpp"
#include "fattr.hpp"
#include "fread.hpp"
#include "../datetime/datetime.h"
#include <string>
#include <fstream>
#include <filesystem>

namespace file {
    class TempFile {
    private:
        std::string name;
    public:
        TempFile(std::string file="") {
            name = (std::string)file;
            if (name.empty()) {
                /* Generate a unique temporary file name. */
                this->name = (std::string)(
                    std::to_string(datetime::timestamp()) 
                    + "_" + std::to_string(std::rand()) + ".tmp"
                );
                name = static_cast<std::string>(std::filesystem::temp_directory_path().string() + "/" + name);
            }
            if (!exists(name)) {
                // Create the file if it doesn't exist.
                std::ofstream ofs;
                try {
                    ofs.open(name);
                } catch(...) {
                    F_THROW_OPENFAIL(name);
                }
            }
        }
        std::string getContent() const {
            return file::readFile(name);
        }
        std::vector<uint8_t> getBinary() const {
            return file::readBinary(name);
        }
        std::string getName() const {
            return name;
        }
        void remove() {
            try {
                std::filesystem::remove(name);
            } catch(...) {
                throw FileException(name);
            }
        }
        ~TempFile() {
            try {
                std::filesystem::remove(name);
            } catch(...) {
                // Ignore any exceptions during cleanup.
            }
        }
    };
} // namespace file