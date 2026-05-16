# Documentation of function `isInfinity`
Function usage: Judge whether a floating-point number is **positive infinity** based on the IEEE 754 standard.
Implementation:
```cpp
bool isInfinity(float f) {
    uint32_t bits = *reinterpret_cast<uint32_t*>(&f);
    return (bits & 0x7FFFFFFF) == 0x7F800000;
}
bool isInfinity(double d) {
    uint64_t bits = *reinterpret_cast<uint64_t*>(&d);
    return (bits & 0x7FFFFFFFFFFFFFFFULL) == 0x7FF0000000000000ULL;
}
```
**IEEE 754 rule**:
- float: exponent bits = all 1, mantissa = all 0 → infinity
- double: exponent bits = all 1, mantissa = all 0 → infinity
**Why this way**: Reads raw memory bits, **no library functions**, ultra-fast, cross-platform.


# Documentation of function `isNegInfinity`
Function usage: Judge whether a floating-point number is **negative infinity**.
Implementation:
```cpp
bool isNegInfinity(float f) {
    uint32_t bits = *reinterpret_cast<uint32_t*>(&f);
    return bits == 0xFF800000;
}
bool isNegInfinity(double d) {
    uint64_t bits = *reinterpret_cast<uint64_t*>(&d);
    return bits == 0xFFF0000000000000ULL;
}
```
**IEEE 754 rule**:
Sign bit = 1 + exponent all 1 + mantissa all 0 → negative infinity.


# Documentation of function `isNan`
Function usage: Judge whether a value is **NaN (Not a Number)**.
Implementation:
```cpp
bool isNan(float f) { return f != f; }
bool isNan(double d) { return d != d; }
```
**Core logic**:
**NaN is not equal to any value, including itself**.
This is the **fastest and most standard** way to judge NaN.


# Documentation of function `floatCmp`
Function usage: **Safe floating-point comparison** (avoids errors caused by precision loss).
Implementation:
```cpp
template<double esp=1e-4, typename T>
bool floatCmp(T x, T y) {
    if constexpr (std::is_same_v<int, T>) return x == y;
    else if constexpr (std::is_same_v<float, T> || std::is_same_v<double, T>)
        return absolute(x - y) < esp;
    return false;
}
```
**Why needed**:
Floating-point numbers (0.1 + 0.2 ≠ 0.3) have precision errors.
Direct `==` comparison is **unsafe**.
**Logic**: If the absolute difference is less than `esp`, they are considered equal.


# Documentation of function `isZero`
Function usage: Safely judge whether a floating-point number is **0** (avoid precision error).
Implementation:
```cpp
template<typename T>
bool isZero(T x) {
    return floatCmp<1e-7>(x, T(0));
}
```
**Logic**: Use ultra-high precision `1e-7` to judge if the value is close enough to 0.


# Documentation of function `absolute`
Function usage: Return the **absolute value** of any number.
Implementation:
```cpp
template<typename T>
T absolute(T x) {
    return (x < 0) ? -x : x;
}
```
**Logic**: If negative → return positive; if positive → keep unchanged.


# Documentation of function `pow`
Function usage: Calculate integer power (e.g., square, cube).
Implementation:
```cpp
template<int index = 2, typename T>
T pow(T x) {
    T res(1);
    for (int i = 0; i < index; ++i) res *= x;
    return res;
}
```
**Logic**: Multiply `x` by itself `index` times.
**Default**: square (index=2).


# Documentation of function `sqrt`
Function usage: Calculate **square root** using **Newton iteration method**.
Implementation:
```cpp
template<typename T>
T sqrt(T x) {
    if (x < 0) return 0;
    T guess = x, prev;
    do {
        prev = guess;
        guess = (guess + x / guess) / 2;
    } while (!floatCmp(guess, prev));
    return guess;
}
```
**Why Newton iteration**:
- Extremely fast convergence
- No library functions needed
- High precision & stable
**Logic**: Continuously approximate the real root until the value no longer changes.


# Documentation of function `cbrt`
Function usage: Calculate **cube root** using Newton iteration.
Implementation:
```cpp
template<typename T>
T cbrt(T x) {
    T guess = x, prev;
    do {
        prev = guess;
        guess = (2*guess + x/(guess*guess))/3;
    } while (!floatCmp(guess, prev));
    return guess;
}
```
**Same logic as sqrt**: Iterative approximation for cube root.


# Documentation of function `ln`
Function usage: Calculate **natural logarithm** using **Taylor series expansion**.
Implementation:
```cpp
template<typename T>
T ln(T x) {
    T y = (x-1)/(x+1);
    T y2 = y*y;
    T res = y;
    // Taylor series: 2*(y + y³/3 + y⁵/5 + ...)
    for (int i=0; i<100; ++i) { ... }
    return 2*res;
}
```
**Why Taylor series**:
Pure mathematical implementation, **no standard library dependencies**, high precision.


# Documentation of function `log` / `log2` / `log10`
Function usage: Calculate logarithms with any base (base 2, base 10).
Implementation:
```cpp
template<int base=2, typename T>
T log(T x) {
    return ln(x) / ln(T(base));
}
```
**Mathematical principle**:
**log_b(a) = ln(a) / ln(b)**
Unified implementation using natural logarithm.


# Documentation of function `floor`
Function usage: **Round down** (toward negative infinity).
Implementation:
```cpp
template<typename T>
T floor(T x) {
    long long i = (long long)x;
    if (x >= 0) return i;
    return floatCmp(x, i) ? i : i-1;
}
```
**Example**:
3.7 → 3
-2.3 → -3


# Documentation of function `ceil`
Function usage: **Round up** (toward positive infinity).
Implementation:
```cpp
template<typename T>
T ceil(T x) {
    long long i = (long long)x;
    if (x <= 0) return i;
    return floatCmp(x, i) ? i : i+1;
}
```
**Example**:
3.2 → 4
-2.8 → -2


# Documentation of function `round`
Function usage: Standard rounding.
Implementation:
```cpp
template<typename T>
T round(T x) {
    return floor(x + 0.5);
}
```
**Logic**: Add 0.5 then round down → simplest rounding method.


# Documentation of function `mod`
Function usage: **Safe modulus** (supports floating-point & negative numbers).
Implementation:
```cpp
template<typename T>
T mod(T a, T b) {
    if (isZero(b)) return 0;
    return a - b * floor(a / b);
}
```
**Why safe**:
- Avoid division by 0
- Correctly handle negative numbers
- Support floating-point modulus


# Documentation of function `isPrime`
Function usage: Judge whether a number is **prime**.
Implementation:
```cpp
bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x%2==0) return false;
    for (int i=3; i*i<=x; i+=2)
        if (x%i==0) return false;
    return true;
}
```
**Optimization logic**:
- Even numbers > 2 → not prime
- Only iterate up to **sqrt(x)**
- Only check odd divisors → **fast**


# Documentation of function `gcd`
Function usage: Calculate **greatest common divisor** using **Euclidean algorithm**.
Implementation:
```cpp
int gcd(int x, int y) {
    x = absolute(x);
    y = absolute(y);
    while (y != 0) {
        int rem = x % y;
        x = y;
        y = rem;
    }
    return x;
}
```
**Why Euclidean algorithm**:
The **fastest known GCD algorithm**, O(log min(x,y)).


# Documentation of function `lcm`
Function usage: Calculate **least common multiple**.
Implementation:
```cpp
int lcm(int x, int y) {
    return x / gcd(x,y) * y;
}
```
**Mathematical formula**:
**LCM(a,b) = a*b / GCD(a,b)**
Order: divide first → avoid integer overflow.


# Documentation of function `deg2rad`
Function usage: Convert **degrees to radians** (for trigonometric functions).
Implementation:
```cpp
template<typename T>
constexpr T deg2rad(T deg) {
    return deg * T(PI) / T(180);
}
```
**Formula**: rad = deg × π ÷ 180.


# Documentation of function `sin` / `cos` / `tan`
Function usage: Calculate trigonometric functions using **Taylor series**.
Implementation:
```cpp
template<typename T>
T sin(T deg) {
    T x = deg2rad(deg);
    // Periodic compression to [-π, π]
    T res = x;
    // Taylor: x - x³/3! + x⁵/5! ...
    for (int n=3; n<=20; n+=2) { ... }
    return res;
}
```
**Why Taylor series**:
- Pure software implementation
- No library or hardware dependency
- High precision for daily use
**Logic**: Expand infinite series to 20 terms → sufficient precision.