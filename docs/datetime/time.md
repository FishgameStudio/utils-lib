# Documentation for Date & Time Module
Function usage: Provides timestamp acquisition, current time parsing, time comparison, and formatted string output for cross-platform datetime operations.



# Documentation of Type Alias `TIMESTAMP`
Function usage: Alias for 64-bit integer, used to store Unix timestamps (seconds / milliseconds).
**Definition**:
```cpp
using TIMESTAMP = int64_t;
```



# Documentation of Class `DATETIME`
Function usage: Encapsulates current date, time, and timestamp, supporting comparison operators.
Automatically initializes to the current system time when constructed.

Member variables:
- `year`: Current year (YYYY)
- `month`: Current month (MM)
- `day`: Current day (DD)
- `min`: Current minute
- `sec`: Current second
- `ts`: Corresponding Unix timestamp (seconds)

Constructor:
```cpp
DATETIME()
```
Automatically fills all time fields using current system time.

Operator overloads:
```cpp
bool operator<(const DATETIME& object);
bool operator>(const DATETIME& object);
bool operator==(const DATETIME& object);
bool operator!=(const DATETIME& object);
bool operator=(const DATETIME& object);
```
Compare by internal timestamp `ts`.

Destructor:
```cpp
~DATETIME() = default;
```



# Documentation of function `timestamp`
Function usage: Get current Unix timestamp (seconds since 1970–01–01).

Implementation:
```cpp
TIMESTAMP timestamp() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}
```
**Return**: Second-level timestamp (`TIMESTAMP`).



# Documentation of function `timestamp_ms`
Function usage: Get current millisecond-level timestamp.

Implementation:
```cpp
TIMESTAMP timestamp_ms() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
```
**Return**: Millisecond-level timestamp.



# Documentation of function `currentDateTimeString`
Function usage: Return formatted current time string.
**Format**: `YYYY-MM-DD HH:MM:SS`

Implementation:
```cpp
std::string currentDateTimeString() {
    std::time_t t = timestamp();
    char buf[100];
    std::tm local_tm = *std::localtime(&t);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
    return buf;
}
```
**Example**: `2025-05-16 22:30:45`



# Documentation of function `currentYear`
Function usage: Get current year (YYYY).

Implementation:
```cpp
int currentYear() {
    std::time_t t = timestamp();
    std::tm lt = *localtime(&t);
    return lt.tm_year + 1900;
}
```
**Example**: `2025`



# Documentation of function `currentMonth`
Function usage: Get current month (1–12).

Implementation:
```cpp
int currentMonth() {
    std::time_t t = timestamp();
    std::tm lt = *localtime(&t);
    return lt.tm_mon + 1;
}
```



# Documentation of function `currentDay`
Function usage: Get current day of the month (1–31).

Implementation:
```cpp
int currentDay() {
    std::time_t t = timestamp();
    std::tm lt = *localtime(&t);
    return lt.tm_mday;
}
```



# Documentation of function `currentHour`
Function usage: Get current hour (0–23).

Implementation:
```cpp
int currentHour() {
    std::time_t t = timestamp();
    std::tm lt = *localtime(&t);
    return lt.tm_hour;
}
```



# Documentation of function `currentMinute`
Function usage: Get current minute (0–59).

Implementation:
```cpp
int currentMinute() {
    std::time_t t = timestamp();
    std::tm lt = *localtime(&t);
    return lt.tm_min;
}
```



# Documentation of function `currentSecond`
Function usage: Get current second (0–59).

Implementation:
```cpp
int currentSecond() {
    std::time_t t = timestamp();
    std::tm lt = *localtime(&t);
    return lt.tm_sec;
}
```