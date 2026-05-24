/* Date & time generator. */

#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <thread>
#include <cstdint>

#include <pybind11/pybind11.h> // GIL management

using TIMESTAMP = int64_t;

namespace datetime {

    TIMESTAMP timestamp();
    TIMESTAMP timestamp_ms();
    std::string currentDateTimeString();
    int currentYear();
    int currentMonth();
    int currentDay();
    int currentHour();
    int currentMinute();
    int currentSecond();
    void sleep(int seconds);
    void sleepms(int milliseconds);

    class DATETIME {
    public:
        int year, month, day, min, sec;
        TIMESTAMP ts;
        DATETIME(): 
        year(currentYear()), month(currentMonth()), day(currentDay()), 
        min(currentMinute()), sec(currentSecond()), ts(timestamp()) {}

        bool operator<(const DATETIME& object) const {
            return this->ts < object.ts;
        }
        bool operator>(const DATETIME& object) const {
            return this->ts > object.ts;
        }
        bool operator==(const DATETIME& object) const {
            return this->ts == object.ts;
        }
        bool operator!=(const DATETIME& object) const {
            return this->ts != object.ts;
        }
        DATETIME& operator=(const DATETIME& object) {
            if (this != &object) {
                year = object.year;
                month = object.month;
                day = object.day;
                min = object.min;
                sec = object.sec;
                ts = object.ts;
            }
            return *this;
        }
        
        ~DATETIME() = default;
    };

    TIMESTAMP timestamp() {
        /* Get how many seconds passed since 1970. */
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }
    TIMESTAMP timestamp_ms() {
        /* Get how many milliseconds passed. */
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    std::string currentDateTimeString() {
        // Returns the string of current date-time.
        std::time_t t = timestamp();
        char buf[100];
        // Convert to local time.
        std::tm local_tm = *std::localtime(&t);
        // Formatted output: YYYY-MM-DD HH:MM:SS
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
        return buf;
    }
    int currentYear() {
        /* Returns the number of the current year(YYYY). */
        std::time_t t = timestamp();
        std::tm lt = *localtime(&t);
        return lt.tm_year + 1900;
    }
    int currentMonth() {
        /* Returns the number of the current month(MM). */
        std::time_t t = timestamp();
        std::tm lt = *localtime(&t);
        return lt.tm_mon + 1;
    }
    int currentDay() {
        /* Returns the number of the current day in the month. */
        std::time_t t = timestamp();
        std::tm lt = *localtime(&t);
        return lt.tm_mday;
    }
    int currentHour() {
        /* Returns the number of the current hour. */
        std::time_t t = timestamp();
        std::tm lt = *localtime(&t);
        return lt.tm_hour;
    }
    int currentMinute() {
        /* Returns the number of the current minute. */
        std::time_t t = timestamp();
        std::tm lt = *localtime(&t);
        return lt.tm_min;
    }
    int currentSecond() {
        std::time_t t = timestamp();
        std::tm lt = *localtime(&t);
        return lt.tm_sec;
    }

    // TODO: Fix the stuck when python calls this function. It may be caused by the GIL.
    void sleep(int seconds) {
        pybind11::call_guard<pybind11::gil_scoped_release>();
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
    void sleepms(int milliseconds) {
        pybind11::call_guard<pybind11::gil_scoped_release>();
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    
}

