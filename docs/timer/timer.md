# Documentation for Timer Library
Function usage: Provides periodic thread-based timer to execute a custom task at a fixed interval.

# Documentation of Type Aliases
```cpp
using TIME = unsigned long long;
```
**Purpose**: Represents time interval in milliseconds.

# Documentation of Class `Timer`
Function usage: Periodic task scheduler with background thread, safe execution, and exception handling.
Supports binding arbitrary functions and arguments, non-copyable.

## Constructor
```cpp
template<typename FUNC, class... ARGS>
Timer(TIME interval_ms, FUNC&& func, ARGS&&... args);
```
Creates and starts a timer that executes the given function every `interval_ms` milliseconds.
Automatically binds the function and its arguments, launches the background thread.

## Destructor
```cpp
~Timer();
```
Automatically stops the timer, joins the background thread, and releases all resources.

## `stop()`
```cpp
void stop();
```
Stops the timer and terminates the background thread.
Safe, thread‑synchronized, and waits for the thread to exit.

## `continue_()`
```cpp
void continue_();
```
Resumes the timer if it was stopped.
Restarts the background thread and continues periodic execution.

## Deleted Methods
```cpp
Timer(const Timer&) = delete;
Timer& operator=(const Timer&) = delete;
```
**Purpose**: Disables copy and assignment to avoid thread safety issues and invalid state duplication.