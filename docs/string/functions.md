# Documentation of function `len`
Function usage: Get the length of the string.
Implementation:
```cpp
size_t len(STRREF s) {
    return s.size();
}
```
**Return**: Number of characters in the string.


# Documentation of function `left`
Function usage: Get the leftmost `len` characters of the string.
Implementation:
```cpp
STR left(STRREF s, size_t len) {
    if (s.size() <= len) return s;
    if (len > s.size()) throw OutOfStringRange(s);
    return s.substr(0, len);
}
```
**Example**: `left("hello", 2)` → `"he"`
**Exception**: `OutOfStringRange` if length exceeds string size.


# Documentation of function `right`
Function usage: Get the rightmost `len` characters of the string.
Implementation:
```cpp
STR right(STRREF s, size_t len) {
    if (s.size() <= len) return s;
    if (len > s.size()) throw OutOfStringRange(s);
    return s.substr(s.size() - len, len);
}
```
**Example**: `right("hello", 2)` → `"lo"`
**Exception**: `OutOfStringRange` on invalid length.


# Documentation of function `mid`
Function usage: Get substring starting at `start`, length `len`.
Implementation:
```cpp
STR mid(STRREF s, size_t start, size_t len=std::string::npos) {
    if (len == std::string::npos) len = s.size() - 1;
    if (start > s.size() - 1) throw OutOfStringRange(s);
    if ((int)len < 0) throw IndexUnderflow(len);
    if (start + len > s.size()) throw OutOfStringRange(s);
    return s.substr(start, len);
}
```
**Example**: `mid("hello", 1, 3)` → `"ell"`
**Exceptions**: `OutOfStringRange`, `IndexUnderflow`.


# Documentation of function `getleft`
Function usage: Safe version of `left` (no throw, returns original string on error).
Implementation:
```cpp
STR getleft(STRREF s, size_t len) noexcept {
    try { return left(s, len); } catch(...) { return s; }
}
```


# Documentation of function `getright`
Function usage: Safe version of `right` (no throw).
Implementation:
```cpp
STR getright(STRREF s, size_t len) noexcept {
    try { return right(s, len); } catch(...) { return s; }
}
```


# Documentation of function `getmid`
Function usage: Safe version of `mid` (no throw).
Implementation:
```cpp
STR getmid(STRREF s, size_t start, size_t len=std::string::npos) noexcept {
    try { return mid(s, start, len); } catch(...) { return s; }
}
```


# Documentation of function `upper`
Function usage: Convert all letters to uppercase.
Implementation:
```cpp
STR upper(STR s) {
    int len = (int)s.size();
    for(int i = 0; i < len; i++) {
        if(s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
    }
    return s;
}
```
**Example**: `"Hello"` → `"HELLO"`


# Documentation of function `isupper`
Function usage: Check if the entire string is uppercase.
Implementation:
```cpp
bool isupper(STR s) {
    for (char c : s) {
        if (!(c >= 'A' && c <= 'Z')) return false;
    }
    return true;
}
```


# Documentation of function `isupper(char)`
Function usage: Check if a character is uppercase.
Implementation:
```cpp
bool isupper(char c) {
    return (c >= 'A' && c <= 'Z');
}
```


# Documentation of function `lower`
Function usage: Convert all letters to lowercase.
Implementation:
```cpp
STR lower(STR s) {
    int len = (int)s.size();
    for(int i = 0; i < len; i++) {
        if(s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    }
    return s;
}
```
**Example**: `"Hello"` → `"hello"`


# Documentation of function `islower`
Function usage: Check if the entire string is lowercase.
Implementation:
```cpp
bool islower(STR s) {
    for (char c : s) {
        if (!(c >= 'a' && c <= 'z')) return false;
    }
    return true;
}
```


# Documentation of function `islower(char)`
Function usage: Check if a character is lowercase.
Implementation:
```cpp
bool islower(char c) {
    return (c >= 'a' && c <= 'z');
}
```


# Documentation of function `title`
Function usage: Convert string to title case (first letter of each word uppercase).
Implementation:
```cpp
STR title(STR s) {
    s = lower(s);
    bool inWord = false;
    for (char& c : s) {
        if (std::isspace(c)) { inWord = false; continue; }
        if (!inWord && !std::isspace(c)) {
            c = std::toupper(c);
            inWord = true;
            continue;
        }
        if (inWord) c = std::tolower(c);
    }
    return s;
}
```
**Example**: `"hello world"` → `"Hello World"`


# Documentation of function `capitalize`
Function usage: Capitalize only the first character of the string.
Implementation:
```cpp
STR capitalize(STR s) {
    int len = (int)s.size();
    if(!s.empty() && s[0] >= 'a' && s[0] <= 'z') s[0] -= 32;
    return s;
}
```
**Example**: `"hello"` → `"Hello"`


# Documentation of function `caseswap`
Function usage: Swap uppercase ↔ lowercase for all characters.
Implementation:
```cpp
STR caseswap(STR s) {
    for (char& c : s) {
        if (isupper(c)) c = std::tolower(c);
        else if (islower(c)) c = std::toupper(c);
    }
    return s;
}
```
**Example**: `"HeLLo"` → `"hEllO"`


# Documentation of function `strip`
Function usage: Remove leading and trailing spaces.
Implementation:
```cpp
STR strip(STR s) {
    int l = 0, r = (int)s.size() - 1;
    while (s[l] == ' ') l++;
    while (r > l && s[r] == ' ') r--;
    return s.substr(l, r - l + 1);
}
```
**Example**: `"  hello world  "` → `"hello world"`


# Documentation of function `split`
Function usage: Split string by separator character into vector of strings.
Implementation:
```cpp
std::vector<STR> split(STRREF s, char sep) {
    std::vector<STR> res{};
    STR temp;
    for(char c : s) {
        if(c == sep) {
            if(!temp.empty()) res.push_back(temp);
            temp.clear();
        } else temp += c;
    }
    if(!temp.empty()) res.push_back(temp);
    return res;
}
```
**Example**: `split("a,b,c", ',')` → `["a", "b", "c"]`


# Documentation of function `count`
Function usage: Count occurrences of a character in the string.
Implementation:
```cpp
size_t count(STRREF s, char subs) {
    size_t cnt = 0;
    for(char c : s) if(c == subs) cnt++;
    return cnt;
}
```
**Example**: `count("hello", 'l')` → `2`


# Documentation of function `find`
Function usage: Find the first position of a substring.
Implementation:
```cpp
size_t find(STRREF s, STRREF subs) {
    return s.find(subs);
}
```
**Return**: Start index, or `std::string::npos` if not found.


# Documentation of function `repeat`
Function usage: Repeat string `time` times.
Implementation:
```cpp
STR repeat(STRREF s, size_t time=1) {
    if (time < 0) throw IndexUnderflow(time);
    if (time == 1) return s;
    STR res{};
    for (auto i=1; i<=time; ++i) res += s;
    return res;
}
```
**Example**: `repeat("ab", 3)` → `"ababab"`
**Exception**: `IndexUnderflow` if time < 0.


# Documentation of function `reverse`
Function usage: Reverse the entire string.
Implementation:
```cpp
STR reverse(STRREF s) {
    size_t n = s.size() -1;
    STR res{};
    for (auto i = 0; i>=0; --i) {
        res += s[i];
    }
    return res;
}
```
**Example**: `reverse("hello")` → `"olleh"`