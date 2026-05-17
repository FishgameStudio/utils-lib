# Documentation for Random Library
Function usage: Provides easy-to-use random number & string generation based on the Mersenne Twister engine.

# Documentation of Type Aliases
```cpp
using STR = std::string;
using STRVEC = std::vector<STR>;
template<typename T = double> using NUMVEC = std::vector<T>;
using NUM = double;
using INT = int;
```
**Purpose**: Simplify type signatures for strings, vectors, numbers, and integers.

# Documentation of Class `RandomEngine`
Function usage: Core random generator wrapper using `std::mt19937` (Mersenne Twister).
Automatically seeds with `std::random_device` for secure randomness.

## Constructor
```cpp
explicit RandomEngine();
```
Initializes the Mersenne Twister engine with a random seed.

## `get_engine()`
```cpp
std::mt19937& get_engine();
```
Returns the underlying random engine for advanced usage.

## `rand_number(min, max)`
```cpp
NUM rand_number(NUM min, NUM max);
```
Generates a **uniform random floating-point number** in `[min, max]`.

## `rand_int(min, max)`
```cpp
INT rand_int(INT min, INT max);
```
Generates a **uniform random integer** in `[min, max]`.

# Documentation of function `random`
Function usage: Generate a single random floating-point number.
Implementation:
```cpp
NUM random(NUM min, NUM max);
```
**Example**: `random(0.0, 1.0)` → `0.723...`

# Documentation of function `randint`
Function usage: Generate a single random integer.
Implementation:
```cpp
INT randint(INT min, INT max);
```
**Example**: `randint(1, 10)` → `6`

# Documentation of function `randstr`
Function usage: Generate a random alphanumeric string of specified length.
Character set: `a-z, A-Z, 0-9`
Implementation:
```cpp
STR randstr(size_t length);
```
**Example**: `randstr(8)` → `"k9Tq7P2x"`

# Documentation of function `randomMany`
Function usage: Generate multiple random floating-point numbers.
Implementation:
```cpp
NUMVEC<> randomMany(NUM min, NUM max, size_t count);
```
**Example**: `randomMany(0, 1, 3)` → `[0.22, 0.45, 0.67]`

# Documentation of function `randintMany`
Function usage: Generate multiple random integers.
Implementation:
```cpp
NUMVEC<int> randintMany(INT min, INT max, size_t count);
```
**Example**: `randintMany(1, 10, 3)` → `[3, 7, 2]`

# Documentation of function `randstrMany`
Function usage: Generate multiple random alphanumeric strings.
Implementation:
```cpp
STRVEC randstrMany(size_t length, size_t count);
```
**Example**: `randstrMany(4, 2)` → `["a1B2", "x9Z7"]`