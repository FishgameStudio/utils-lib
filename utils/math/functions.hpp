/* Math functions implement logic. */

#pragma once
#include <cstdint>
#include <type_traits>
#include "constants.hpp"


namespace math {
    bool isInfinity(float f) {
        /* 
         * IEEE 754 float: Exponential 8-bit all 1s, 
         * Last 23 bit all 0 => infinity 
         */
        uint32_t bits = *reinterpret_cast<uint32_t*>(&f);
        return (bits & 0x7FFFFFFF) == 0x7F800000;
    }
    bool isInfinity(double d) {
        // IEEE 754 double: Exponential 11 bits all 1, 
        // mantissa 52 bits all 0 => infinity
        uint64_t bits = *reinterpret_cast<uint64_t*>(&d);
        return (bits & 0x7FFFFFFFFFFFFFFFULL) == 0x7FF0000000000000ULL;
    }
    bool isNegInfinity(float f) {
        uint32_t bits = *reinterpret_cast<uint32_t*>(&f);
        return bits == 0xFF800000;
    }
    bool isNegInfinity(double d) {
        uint64_t bits = *reinterpret_cast<uint64_t*>(&d);
        return bits == 0xFFF0000000000000ULL;
    }
    bool isNan(float f) {
        /* NaN isn't equal to any number, including NaN. */
        return f != f;
    }
    bool isNan(double d) {
        return d != d;
    }
    template<double esp=1e-4, typename T>
    bool floatCmp(T x, T y) {
        if constexpr (std::is_same_v<int, T>) return x == y;
        else if constexpr (std::is_same_v<float, T>) return absolute(x - y) < esp;
        else if constexpr (std::is_same_v<double, T>) return absolute(x - y) < esp;
        return false;
    }
    template<typename T>
    bool isZero(T x) {
        return floatCmp<1e-7>(x, T(0));
    }
    template<typename T> 
    T absolute(T x) {
        /*
         * Return the absolute value. 
         * Cast a number to positive.
         */ 
        return (x < 0) ? -x : x;
    }

    template<int index = 2, typename T>
    T pow(T x) {
        T res(1);
        for (int i = 0; i < index; ++i) {
            res *= x;
        }
        return res;
    }

    template<typename T>
    T sqrt(T x) {
        /* Calc the square root of x. */
        if (x < T(0)) return T(0);
        if (isZero(x)) return T(0);
        
        /* Newton interation method. */
        T guess = x, prev;
        do {
            prev = guess;
            guess = (guess + x / guess) / T(2);
        } while (!floatCmp(guess, prev));

        return guess;
    }
    
    template<typename T>
    T cbrt(T x) {
        if (isZero(x)) return T(0);
        
        T guess = x, prev;
        do {
            prev = guess;
            guess = (T(2) * guess + x / (guess * guess)) / T(3);
        } while (!floatCmp(guess, prev));

        return guess;
    }

    template<typename T>
    T ln(T x) {
        /* Natural logarithm ln(x) */
        if (T(0) > x) return T(0);
        if (floatCmp(x, T(1))) return T(0);

        T y = (x - T(1)) / (x + T(1));
        T y2 = y * y;
        T res = y;
        T term = y;
        T n = T(3);

        for (int i = 0; i < 100; ++i) {
            term *= y2;
            T add = term / n;
            res += add;
            if (isZero(add)) break;
            n += T(2);
        }

        return T(2) * res;

    }

    template<int base=2, typename T>
    T log(T x) {
        /* Calc the power of x to base */
        return ln(x) / ln(T(base));
    }
    template<typename T>
    T log2(T x) {
        return log<2>(x);
    }
    template<typename T>
    T log10(T x) {
        return log<10>(x);
    }
    template<typename T>
    T floor(T x) {
        /* Round down x. */
        long long i = static_cast<long long>(x);
        if (x >= T(0)) return T(i);
        return (floatCmp(x, T(i))) ? T(i) : T(i - 1);
    }
    template<typename T>
    T ceil(T x) {
        /* Round up x. */

        long long i = static_cast<long long>(x);
        if (x <= T(0)) return T(i);
        return floatCmp(x, T(i)) ? T(i) : T(i + 1);
    }
    template<typename T>
    T round(T x) {
        /*
         * If the decimal part of x is less than 0.5, return floor (x) 
         * Else return ceil(x).
         */
        if constexpr (std::is_same_v<int, T>) return x;
        return floor(x + T(0.5));
    }
    template<typename T>
    T mod(T a, T b) {
        // Safe mod.
        if (isZero(b)) return T(0);
        T res = a - b * floor(a / b);
        return res;
    }
    bool isPrime(int x) {
        if (x < 2) return false;
        if (x == 2) return true;
        if (x % 2 == 0) return false;

        for (int i = 3; i * i <= x; i += 2) 
            if (x % i == 0) return false;
        return true;
    }
    int gcd(int x, int y) {
        /* Returns the Greatest common divisor */
        x = absolute(x);
        y = absolute(y);
        while (y != 0) {
            int rem = x % y;
            x = y;
            y = rem;
        }
        return x;
    }
    int lcm(int x, int y) {
        /* Returns the Lowest common multiple. */
        if (x == 0 || y == 0) return 0; // Cannot be zero.
        /**
         * GCD | A   B
         *     |_________
         *       a   b
         * a * GCD = A, b * GCD = B.
         */
        return x / gcd(x, y) * y;
    }
    // Degress to radians.
    template<typename T>
    constexpr T deg2rad(T deg) {
        return deg * T(PI) / T(180);
    }

    template<typename T>
    T sin(T deg) {
        /* Calc sine of degrees. */

        T x = deg2rad(deg);
        // Periodic folding to [pi, pi] converges faster
        while (x > T(PI))  x -= T(2)*T(PI);
        while (x < -T(PI)) x += T(2)*T(PI);

        T res = x;
        T term = x;
        int sign = -1;
        // Taylor series: sinx = x - x³/3! + x⁵/5! - ...
        for (int n = 3; n <= 20; n += 2) {
            term *= x*x / (T(n-1)*T(n));
            res += sign * term;
            if (isZero(term)) break;
            sign = -sign;
        }
        return res;
    }
    template<typename T>
    T cos(T deg) {
        /* Cosine. */
        T x = deg2rad(deg);
        while (x > T(PI))  x -= T(2)*T(PI);
        while (x < -T(PI)) x += T(2)*T(PI);

        T res = T(1);
        T term = T(1);
        int sign = -1;
        // cosx = 1 - x²/2! + x⁴/4! - ...
        for (int n = 2; n <= 20; n += 2) {
            term *= x*x / (T(n-1)*T(n));
            res += sign * term;
            if (isZero(term)) break;
            sign = -sign;
        }
        return res;
    }
    template<typename T>
    T tan(T deg) {
        /* Tangent. */
        if (isZero(cos(deg))) return T(0);
        return sin(deg) / cos(deg);
    }
}