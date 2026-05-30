/* Some useful macros. */

// This header if a part of the utils library,
// but it is not included by default when including the library, 
// because we don't like macro pollution.



#ifdef __UTILS_LIB_INCLUDE_ALL
#include <stdexcept>
#include <mutex>


// =============== ERROR CODE ===============
#define EC_ERROR 1
#define EC_SUCCESS 0
#define EC_INVALID_ARGUMENT 2
#define EC_OUT_OF_MEMORY 3
#define EC_FILE_NOT_FOUND 4
#define EC_PERMISSION_DENIED 5
#define EC_UNKNOWN_ERROR 6
#define EC_TIMEOUT 7
#define EC_NOT_IMPLEMENTED 8
#define EC_ALREADY_EXISTS 9

// =============== NETWORKING REQUEST CODE ===============
#define NRC_NOT_FOUND 404
#define NRC_OK 200
#define NRC_BAD_REQUEST 400
#define NRC_UNAUTHORIZED 401
#define NRC_FORBIDDEN 403
#define NRC_INTERNAL_SERVER_ERROR 500
#define NRC_SERVICE_UNAVAILABLE 503
#define NRC_GATEWAY_TIMEOUT 504
#define NRC_HTTP_VERSION_NOT_SUPPORTED 505
#define NRC_NETWORK_AUTHENTICATION_REQUIRED 511
#define NRC_CONTINUE 100
#define NRC_SWITCHING_PROTOCOLS 101
#define NRC_PROCESSING 102
#define NRC_EARLY_HINTS 103
#define NRC_MULTIPLE_CHOICES 300
#define NRC_MOVED_PERMANENTLY 301
#define NRC_FOUND 302
#define NRC_SEE_OTHER 303
#define NRC_NOT_MODIFIED 304
#define NRC_USE_PROXY 305
#define NRC_TEMPORARY_REDIRECT 307
#define NRC_PERMANENT_REDIRECT 308

// =============== LOGGING LEVEL ===============
#define LL_DEBUG 0
#define LL_INFO 1
#define LL_WARNING 2
#define LL_ERROR 3
#define LL_CRITICAL 4
#define LL_VERBOSE 5
#define LL_SILLY 6
#define LL_TRACE 7
#define LL_FATAL 8
#define LL_OFF 9
#define LL_ASSERT 10

// =============== MODIFIER & PREFIX =============== 
#define _UNUSED [[maybe_unused]]   
#define _DEPRECATED [[deprecated]]
#define _NODISCARD [[nodiscard]]
#define _INLINE inline
#define _NOEXCEPT noexcept
#define _CONSTEXPR constexpr
#define DEPRECATED(msg) [[deprecated(msg)]]
#ifdef _MSC_VER
#  define _ALWAYS_INLINE __forceinline
#else
#  define _ALWAYS_INLINE inline __attribute__((always_inline))
#endif

#define THROW_WHEN_EXCEPT(exception, lambda) \
    do {                                    \
        try {                               \
            lambda();                       \
        } catch (...) {                     \
            throw exception;                \
        }                                   \
    } while (0);


// =============== MISC ===============
#define __LOCK_MTX(mtx) std::lock_guard<std::mutex> lock(mtx);


#endif // __UTILS_LIB_INCLUDE_ALL
