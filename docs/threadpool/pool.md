# Documentation for ThreadPool Library
Function usage: Implements fixed-size reusable thread pool to schedule and run concurrent tasks.

# Documentation of Class `THREADPOOL`
Function usage: Manages a group of worker threads, distributes incoming tasks to idle threads automatically, supports thread state query and task synchronization.

## Constructor
```cpp
explicit THREADPOOL(size_t thread_count);
```
Create thread pool with specified number of worker threads. Throw exception if input count is zero.

## Destructor
```cpp
~THREADPOOL();
```
Wait all ongoing tasks to complete and release occupied thread resources.

## Copy restriction
```cpp
THREADPOOL(const THREADPOOL&) = delete;
THREADPOOL& operator=(const THREADPOOL&) = delete;
```
Prohibit copy and assignment behavior to avoid abnormal thread state.

## `execute(func, args...)`
```cpp
template<typename Fn, typename... Args>
void execute(Fn&& func, Args&&... args);
```
Deliver target task to idle worker thread and execute asynchronously. Occupy thread resource and mark running status during execution.

## `available_threads()`
```cpp
size_t available_threads() const;
```
Count and return current quantity of idle threads that can accept new tasks.

## `wait_all()`
```cpp
void wait_all();
```
Block current execution flow until all running tasks finish processing.