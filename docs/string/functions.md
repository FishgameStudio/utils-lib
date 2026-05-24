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
Function usage: Get substring starting at `start`, up to `len` characters.
Implementation:
```cpp
STR mid(STRREF s, size_t start, size_t len=std::string::npos) {
    if (start > s.size()) throw OutOfStringRange(s);
    if (len == std::string::npos) len = s.size() - start;
    if (start + len > s.size()) throw OutOfStringRange(s);
    return s.substr(start, len);
}
```
**Example**: `mid("hello", 1, 3)` → `"ell"`
**Behavior**: When `len` is omitted, returns the substring from `start` to the end.
**Exception**: `OutOfStringRange` if `start` is beyond the string or the requested range exceeds the string.


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
    /* Reverse a string using reverse iterators. */
    return STR{s.rbegin(), s.rend()};
}
```
**Example**: `reverse("hello")` → `"olleh"`


# Documentation of function `replace`
Function usage: Replace all occurrences of `oldsubs` with `newsubs`.
Implementation:
```cpp
STR replace(STR s, STRREF oldsubs, STRREF newsubs) {
    size_t pos = 0;
    while ((pos = s.find(oldsubs, pos)) != std::string::npos) {
        s.replace(pos, oldsubs.length(), newsubs);
        pos += newsubs.length();
    }
    return s;
}
```
**Example**: `replace("banana", "na", "na!")` → `"bana!na!"`
**Behavior**: Continues searching after each replacement to avoid infinite loops when `newsubs` contains `oldsubs`.


# Documentation of function `input`
Function usage: Read a full line of user input from standard input.
Implementation:
```cpp
STR input(STRREF prompt="") {
    STR res;
    std::cout << prompt;
    std::getline(std::cin, res);
    return res;
}
```
**Behavior**: Prints the prompt and returns the entered line as a string.


# Documentation of function `inputpasswd`
Function usage: Read a password from standard input while echoing `*` for each character.
Implementation:
```cpp
STR inputpasswd(STRREF prompt="Password: ") {
    STR res;
    std::cout << prompt;
    while (true) {
        char c = std::getchar();
        if (c == '\n') break;
        res += c;
        std::cout << '*';
    }
    std::cout << std::endl;
    return res;
}
```
**Behavior**: Masks typed characters with `*` and returns the entered text after Enter is pressed.


# Documentation of function `getusername`
Function usage: Get the current user name from the environment.
Implementation:
```cpp
STR getusername() {
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
```
**Behavior**: Reads the current username from system environment on POSIX, or from Windows API on Windows.
**Exception**: Throws if the username cannot be determined.
