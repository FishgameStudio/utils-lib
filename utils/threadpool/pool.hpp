/* Thread pool implementation. */

#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <atomic>
#include <unordered_map>
#include <stdexcept>

namespace threadpool {

class THREADPOOL {
private:
    // Map to store worker threads and their running status
    // Key: thread ID, Value: (thread object, is_idle flag)
    std::unordered_map<std::thread::id, std::pair<std::thread, std::atomic<bool>>> workers;
    
    // Mutex for thread-safe operations
    mutable std::mutex mtx;

public:
    // Initialize thread pool with fixed number of threads
    THREADPOOL(size_t thread_count) {
        if (thread_count == 0) {
            throw std::out_of_range("Thread count must be greater than zero");
        }

        for (size_t i = 0; i < thread_count; ++i) {
            std::thread empty_thread;
            auto tid = empty_thread.get_id();
            workers[tid].first = std::move(empty_thread);
            workers[tid].second = std::move(true);
        }
    }

    // Destructor: wait all threads to finish
    ~THREADPOOL() {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& entry : workers) {
            auto& th = entry.second.first;
            if (th.joinable()) {
                th.join();
            }
        }
    }

    // Disable copy and assignment
    THREADPOOL(const THREADPOOL&) = delete;
    THREADPOOL& operator=(const THREADPOOL&) = delete;

    // Submit a task to an available thread
    template<typename Fn, typename... Args>
    void execute(Fn&& func, Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx);

        // Find the first available idle thread
        for (auto& entry : workers) {
            auto& th = entry.second.first;
            auto& idle_flag = entry.second.second;

            if (idle_flag) {
                // Join if thread is still running
                if (th.joinable()) {
                    th.join();
                }

                // Mark thread as busy
                idle_flag = false;

                // Launch task in thread
                th = std::thread([this, func, args...]() mutable {
                    std::invoke(func, args...);

                    // Mark thread as idle after task done
                    std::lock_guard<std::mutex> lock(mtx);
                    for (auto& p : workers) {
                        if (p.second.first.get_id() == std::this_thread::get_id()) {
                            p.second.second = true;
                            break;
                        }
                    }
                });
                break;
            }
        }
    }

    // Get the number of available idle threads
    size_t available_threads() const {
        std::lock_guard<std::mutex> lock(mtx);
        size_t count = 0;
        for (auto& entry : workers) {
            if (entry.second.second) {
                count++;
            }
        }
        return count;
    }

    // Wait for all running threads to finish
    void wait_all() {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& entry : workers) {
            auto& th = entry.second.first;
            if (th.joinable()) {
                th.join();
            }
        }
    }
};

}