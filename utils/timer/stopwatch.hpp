/* Stopwatch engine implementation. */

#pragma once
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>


namespace timer {
    using TIME = unsigned long long; // milliseconds
    class Stopwatch {
    private:
        TIME current_time_ms=0; // milliseconds
        std::atomic<bool> status{false}; // is running
        std::thread timer;
        std::mutex mtx;
        void run() {    
            while (status) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                std::lock_guard<std::mutex> lock(mtx);
                current_time_ms++;
            }
        }
    public:
        Stopwatch() = default;
        ~Stopwatch() {
            terminate();
        }
        TIME start() {
            std::lock_guard<std::mutex> lock(mtx);
            if (!status) {
                status = true;
                if (timer.joinable()) timer.join(); // stop the thread if already running
                timer = std::thread(&Stopwatch::run, this);
            }
            return current_time_ms;
        }
        TIME stop() {
            std::lock_guard<std::mutex> lock(mtx);
            if (status) {
                status = false;
                if (timer.joinable()) timer.join(); // stop the thread
            }
            return current_time_ms;
        }
        TIME reset() {
            std::lock_guard<std::mutex> lock(mtx);
            current_time_ms = 0;
            status = false;
            if (timer.joinable()) timer.join(); // stop the thread if running
            return current_time_ms;
        }
        TIME get_time() {
            std::lock_guard<std::mutex> lock(mtx);
            return current_time_ms;
        }
        TIME terminate() {
            std::lock_guard<std::mutex> lock(mtx);
            status = false;
            if (timer.joinable()) timer.join(); // stop the thread
            return current_time_ms;
        }
        bool is_running() {
            std::lock_guard<std::mutex> lock(mtx);
            return status;
        }
    };
}