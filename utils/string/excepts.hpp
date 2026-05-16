/* Exceptions difinitions. */

#include <stdexcept>
#include <string>

namespace str {
    class OutOfStringRange : public std::out_of_range {
    public:
        OutOfStringRange(const std::string msg, const int idx=0)
         : std::out_of_range("Out of range: index out of \"" + (std::string)msg + "\"") {}
    };
    class IndexUnderflow : public std::out_of_range {
        public:
            IndexUnderflow(const int idx)
             : std::out_of_range("Index underflow: index " + std::to_string(idx) + " less than 0") {}
        };
}