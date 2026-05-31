/* Core string functions. */


#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <windows.h>
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
        if (start > s.size()) throw OutOfStringRange(s);
        if (len == std::string::npos) len = s.size() - start;
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
        if (s.empty()) return s;
        size_t l = 0, r = s.size() - 1;
        while (l < s.size() && s[l] == ' ') l++;
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
    STR repeat(STRREF s, size_t time=1) {
        /* Repeat a string `time` times. */
        if (time < 0) throw IndexUnderflow(time);
        if (time == 1) return s;
        STR res{};
        for (auto i=1; i<=time; ++i) {
            res += s;
        }
        return res;
    }
    STR reverse(STRREF s) {
        /* Reverse a string. */
        STR res{};
        for (int i=s.size() - 1; i>=0; --i) res += s[i];
        return res;
    }
    STR replace(STR s, STRREF oldsubs, STRREF newsubs) {
        /* Replace all occurrences of `oldsubs` with `newsubs`. */
        size_t pos = 0;
        while ((pos = s.find(oldsubs, pos)) != std::string::npos) {
            s.replace(pos, oldsubs.length(), newsubs);
            pos += newsubs.length();
        }
        return s;
    }
    STR input(STRREF prompt="") {
        /* Get input from the user. */
        STR res;
        std::cout << prompt;
        std::getline(std::cin, res);
        return res;
    }
    STR inputpasswd(STRREF prompt="Password: ") {
        /* Get password input from the user. */
        STR res;
        std::cout << prompt;
        while (true) {
            char c = std::getchar();
            if (c == '\n') break;
            res += c;
            std::cout << '*'; // Print asterisk for each character entered.
        }
        std::cout << std::endl; // Move to the next line after input.
        return res;
    }
    STR getusername() {
        /* Get the username of the current user. */
        #ifdef _WIN32
            char username[256];
            DWORD size = sizeof(username);
            if (GetUserNameA(username, &size)) {
                return STR{username};
            } else {
                throw std::runtime_error("Failed to get username");
            }
        #else
            const char* username = std::getenv("USER");
            if (username) {
                return STR{username};
            } else {
                throw std::runtime_error("Failed to get username");
            }
        #endif
        return "";
    }
}