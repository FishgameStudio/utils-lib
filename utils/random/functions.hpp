/* Random library functions implementation. */

#pragma once
#include <random>
#include <string>
#include <vector>
#include <stdexcept>

namespace random {
    using STR = std::string;
    using STRVEC = std::vector<STR>;
    template<typename T = double>
    using NUMVEC = std::vector<T>;
    using NUM = double;
    using INT = int;

    
    /* Create random engine object. */
    class RandomEngine {
    private:
        std::mt19937 engine; // Mersenne Twister engine
    public:
        explicit RandomEngine() : engine(std::random_device{}()) {}
        std::mt19937& get_engine() {
            return engine;
        }
        NUM rand_number(NUM min, NUM max) {
            std::uniform_real_distribution<NUM> dist(min, max);
            return dist(engine);
        }
        INT rand_int(INT min, INT max) {
            std::uniform_int_distribution<INT> dist(min, max);
            return dist(engine);
        }
    };

    NUM random(NUM min, NUM max) {
        /* Random a float number. */
        RandomEngine re;
        return re.rand_number(min, max);
    }
    INT randint(INT min, INT max) {
        /* Random an integer. */
        RandomEngine re;
        return re.rand_int(min, max);
    }
    STR randstr(size_t length) {
        /* Random a string of given length. */
        const STR chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        STR result;
        result.reserve(length);
        RandomEngine re;
        for (size_t i = 0; i < length; ++i) {
            result += chars[re.rand_int(0, static_cast<INT>(chars.size() - 1))];
        }
        return result;
    }
    NUMVEC<> randomMany(NUM min, NUM max, size_t count) {
        /* Random many float numbers. */
        RandomEngine re;
        NUMVEC<> result(count);
        for (size_t i = 0; i < count; ++i) {
            result[i] = re.rand_number(min, max);
        }
        return result;
    }
    NUMVEC<int> randintMany(INT min, INT max, size_t count) {
        /* Random many integers. */
        RandomEngine re;
        NUMVEC<int> result(count);
        for (size_t i = 0; i < count; ++i) {
            result[i] = re.rand_int(min, max);
        }
        return result;
    }
    STRVEC randstrMany(size_t length, size_t count) {
        /* Random many strings of given length. */
        STRVEC result(count);
        for (size_t i = 0; i < count; ++i) {
            result[i] = randstr(length);
        }
        return result;
    }
    template<typename... Args>
    decltype(auto) choice(Args&&... args) {
        using ReturnType = std::common_type_t<Args...>;
        ReturnType arr[] = { std::forward<Args>(args)... };
        const size_t size = sizeof...(Args);

        if (size == 0) {
            throw std::invalid_argument("choice: No argument inputted!");
        }
        size_t idx = RandomEngine().rand_int(0, size-1);

        return arr[idx];
    }
}