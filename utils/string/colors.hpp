/* Core colors constants. */

#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <string>

// Is in Windows Terminal?
bool isWindowsTerminal() {
    DWORD len = GetEnvironmentVariableA("WT_SESSION", nullptr, 0);
    return len > 0;
}

// Try to enalbe VT processing on Windows 10+ (including Windows Terminal). 
// Returns true if successful or already enabled, false otherwise.
bool enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return false; // not a console or error

    // has VT processing already enabled?
    if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) return true;

    // Try to enable it, but if it fails, just return false 
    // and let the caller decide what to do.
    DWORD newMode = mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, newMode)) {
        return false;
    }
    return true;
}

#endif

namespace str {
    inline constexpr std::string RESET   = "\033[0m";

    inline constexpr std::string BLACK   = "\033[30m";
    inline constexpr std::string RED     = "\033[31m";
    inline constexpr std::string ORANGE  = "\033[38;5;208m";
    inline constexpr std::string YELLOW  = "\033[33m";
    inline constexpr std::string GREEN   = "\033[32m";
    inline constexpr std::string CYAN    = "\033[36m";
    inline constexpr std::string BLUE    = "\033[34m";
    inline constexpr std::string PURPLE  = "\033[35m";
    inline constexpr std::string MAGENTA = "\033[35m";
    inline constexpr std::string WHITE   = "\033[37m";

    inline constexpr std::string BOLD    = "\033[1m";
    inline constexpr std::string UNDERLINE = "\033[4m";
    inline constexpr std::string REVERSED = "\033[7m";
    inline constexpr std::string ITALIC   = "\033[3m";

    inline constexpr std::string LINK_START = "\033]8;;";
    inline constexpr std::string LINK_MIDDLE = "\033\\";
    inline constexpr std::string LINK_END = "\033]8;;\033\\";

    inline std::string makelink(const std::string& text, const std::string& url) {
        #ifdef _WIN32 
        if (!isWindowsTerminal() || !enableVirtualTerminalProcessing()) {
            // If we're not in Windows Terminal or 
            // couldn't enable VT processing, return plain text.
            return text;
        }
        #endif

        return LINK_START + (std::string)url + LINK_MIDDLE + text + LINK_END;
    }
    inline void cprint(const std::string& text, const std::string& color) {
        #ifdef _WIN32 
        if (!isWindowsTerminal() || !enableVirtualTerminalProcessing()) {
            std::cout << text;
            return;
        }
        #endif

        std::cout << color << text << RESET;
    }
    inline void cprintln(const std::string& text, const std::string& color) {
        #ifdef _WIN32 
        if (!isWindowsTerminal() || !enableVirtualTerminalProcessing()) {
            std::cout << text << std::endl;
            return;
        }
        #endif
        
        std::cout << color << text << RESET << std::endl;
    }
}