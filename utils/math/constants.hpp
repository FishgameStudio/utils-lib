/* Math constants. */

#pragma once
#include <limits>
#include <numbers>

namespace math {
    constexpr double INF     = std::numeric_limits<double>::infinity();
    constexpr double NEG_INF = -INF;
    constexpr double PI      = std::numbers::pi;
    constexpr float  PI_F    = std::numbers::pi_v<float>;
    constexpr float  PI_LB   = std::numbers::pi_v<long double>;
    constexpr double E       = std::numbers::e;
    constexpr double SQRT2   = std::numbers::sqrt2;      // sqrt(2)
    constexpr double SQRT3   = std::numbers::sqrt3;      // sqrt(3)
    constexpr double LN2     = std::numbers::ln2;        // ln(2)
    constexpr double LN10    = std::numbers::ln10;       // ln(10)
    constexpr double LOG2E   = std::numbers::log2e;      // log2(e)
    constexpr double LOG10E  = std::numbers::log10e;     // log10(e)
    constexpr double INV_PI  = std::numbers::inv_pi;     // 1 / π
    constexpr double INV_SQRT_PI = std::numbers::inv_sqrtpi; // 1 / sqrt(π)
    constexpr double INV_SQRT3   = std::numbers::inv_sqrt3;  // 1 / sqrt(3)
    constexpr double EGAMMA  = std::numbers::egamma;  // Euler's constant
    constexpr double PHI     = std::numbers::phi;     // Golden ratio
}