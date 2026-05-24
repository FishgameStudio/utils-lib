# Documentation for Timer Library
Function usage: Provides thread-based stopwatch for precise time measurement in milliseconds.

# Documentation of Type Aliases
```cpp
using TIME = unsigned long long;
```
**Purpose**: Represents time value in milliseconds.

# Documentation of Class `Stopwatch`
Function usage: High-precision stopwatch with background thread timing, thread-safe operations.
Automatically manages background thread and ensures safe resource release.

## Constructor
```cpp
Stopwatch() = default;
```
Initializes stopwatch with time 0 and stopped status.

## Destructor
```cpp
~Stopwatch();
```
Automatically terminates the timing thread and releases resources.

## `start()`
```cpp
TIME start();
```
Starts or resumes the stopwatch.
Does nothing if already running.
Returns current time in milliseconds.

## `stop()`
```cpp
TIME stop();
```
Stops the stopwatch and terminates the timing thread.
Does nothing if already stopped.
Returns current time in milliseconds.

## `reset()`
```cpp
TIME reset();
```
Stops the timing thread and resets time to 0.
Returns 0 after reset.

## `get_time()`
```cpp
TIME get_time();
```
Returns current elapsed time in milliseconds.

## `terminate()`
```cpp
TIME terminate();
```
Forces stop the timing thread and stops the stopwatch.
Returns current time before termination.

## `is_running()`
```cpp
bool is_running();
```
Returns true if the stopwatch is currently running, false otherwise.