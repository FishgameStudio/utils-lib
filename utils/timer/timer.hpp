    #pragma once
    #include <chrono>
    #include <atomic>
    #include <thread>
    #include <mutex>
    #include <functional>

    namespace timer {
        using TIME = unsigned long long;

        class Timer {
        private:
            std::thread timer_;
            std::function<void()> task_; // The function to execute
            TIME interval_ms_ = 0;
            std::atomic<bool> running_{false};  // Running status
            std::mutex mtx_;

            void run() {
                while (running_) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms_));

                    if (running_ && task_) {
                        try {
                            task_();  // Execute
                        } catch (...) {
                            // Don't let exceptions escape the timer thread
                        }
                    }
                }
            }
        public:
            template<typename FUNC, class... ARGS>
            Timer(TIME interval_ms, FUNC&& func, ARGS&&... args)
                : interval_ms_(interval_ms)
            {
                /* Bind function and arguments. */
                task_ = std::bind(std::forward<FUNC>(func), std::forward<ARGS>(args)...);

                /* Start timer thread. */
                running_ = true;
                timer_ = std::thread(&Timer::run, this);
            }

            void stop() {
                std::lock_guard<std::mutex> lock(mtx_);
                if (running_) {
                    running_ = false;
                }
                if (timer_.joinable()) {
                    timer_.join();
                }
            }

            void continue_() {
                std::lock_guard<std::mutex> lock(mtx_);
                if (!running_) {
                    running_ = true;
                    timer_ = std::thread(&Timer::run, this);
                }
            }
            ~Timer() {
                stop();
            }
            // Disable copy and assignment
            Timer(const Timer&) = delete;
            Timer& operator=(const Timer&) = delete;
        };
    }