/* Core string functions. */

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "excepts.hpp"


namespace str {
    using STRREF = const std::string&;
    using STR    = std::string;

    size_t len(STRREF s) {
        return s.size();
    }
    STR left(STRREF s, size_t len) {
        /* Returns `len` characters in the left. */
        if (s.size() <= len) return s;
        if (len > s.size()) throw OutOfStringRange(s);
        return s.substr(0, len);
    }
    STR right(STRREF s, size_t len) {
        /* Returns `len` chars in the right. */
        if (s.size() <= len) return s;
        if (len > s.size()) throw OutOfStringRange(s);
        return s.substr(s.size() - len, len);
    }
    STR mid(STRREF s, size_t start, size_t len=std::string::npos) {
        /* Returns the specified `start` index to `start+len` chars of the string. */
        if (len == std::string::npos) len = s.size() - 1;
        if (start > s.size() - 1) throw OutOfStringRange(s);
        if ((int)len < 0) throw IndexUnderflow(len);
        if (start + len > s.size()) throw OutOfStringRange(s);
        return s.substr(start, len);
    }
    STR getleft(STRREF s, size_t len) noexcept {
        try {
            return left(s, len);
        } catch(...) {
            return s;
        }
    }
    STR getright(STRREF s, size_t len) noexcept {
        try {
            return right(s, len);
        } catch(...) {
            return s;
        }
    }
    STR getmid(STRREF s, size_t start, size_t len=std::string::npos) noexcept {
        try {
            return mid(s, start, len);
        } catch(...) {
            return s;
        }
    }
    STR upper(STR s) {
        /* Uppercase. */
        int len = (int)s.size();
        for(int i = 0; i < len; i++) {
            if(s[i] >= 'a' && s[i] <= 'z')
                s[i] -= 32;
        }
        return s;
    }
    bool isupper(STR s) {
        for (char c : s) {
            if (!(c >= 'A' && c <= 'Z')) return false;
        }
        return true;
    }
    bool isupper(char c) {
        return (c >= 'A' && c <= 'Z');
    }
    STR lower(STR s) {
        /* Lowercase. */
        int len = (int)s.size();
        for(int i = 0; i < len; i++) {
            if(s[i] >= 'A' && s[i] <= 'Z')
                s[i] += 32;
        }
        return s;
    }
    bool islower(STR s) {
        for (char c : s) {
            if (!(c >= 'a' && c <= 'z')) return false;
        }
        return true;
    }
    bool islower(char c) {
        return (c >= 'a' && c <= 'z');
    }
    STR title(STR s) {
        /* Title the string. */
        s = lower(s);
        bool inWord = false;
        for (char& c : s) {
            if (std::isspace(c)) {
                inWord = false;
                continue;
            }
            if (!inWord && !std::isspace(c)) {
                c = std::toupper(c);
                inWord = true;
                continue;
            }
            if (inWord) {
                c = std::tolower(c);
            }
        }
        return s;
    }
    STR capitalize(STR s) {
        int len = (int)s.size();
        if(!s.empty() && s[0] >= 'a' && s[0] <= 'z') s[0] -= 32;
        return s;
    }
    STR caseswap(STR s) {
        /* Swap the cases. */
        for (char& c : s) {
            if (isupper(c)) c = std::tolower(c);
            else if (islower(c)) c = std::toupper(c);
        }
        return s;
    }
    STR strip(STR s) {
        int l = 0, r = (int)s.size() - 1;
        while (s[l] == ' ') l++;
        while (r > l && s[r] == ' ') r--;
        return s.substr(l, r - l + 1);
    }
    std::vector<STR> split(STRREF s, char sep) {
        std::vector<STR> res{};
        STR temp;
        for(char c : s) {
            if(c == sep) {
                if(!temp.empty()) res.push_back(temp);
                temp.clear();
            } else {
                temp += c;
            }
        }
        // The last part.
        if(!temp.empty()) res.push_back(temp);
        return res;
    }
    size_t count(STRREF s, char subs) {
        size_t cnt = 0;
        for(char c : s) if(c == subs) cnt++;
        return cnt;
    }
    size_t find(STRREF s, STRREF subs) {
        return s.find(subs);
    }
    
}