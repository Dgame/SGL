#ifndef SGL_CONFIG_HPP
#define SGL_CONFIG_HPP

#if defined(_WIN64)
    #define SGL_OS_WIN64
#elif defined(_WIN32)
    #define SGL_OS_WIN32
#elif defined(__linux__)
    #define SGL_OS_LINUX
#elif defined(__APPLE__)
    #define SGL_OS_MAC
#elif defined(__FreeBSD__)
    #define SGL_OS_FREE_BSD
#endif

#if defined(SGL_OS_WIN32) || defined(SGL_OS_WIN64)
    #define SGL_OS_WINDOWS
#endif

#define SGL_USE_X64 0

#if defined(NDEBUG)
    #define SGL_DEBUG 0
#else
    #define SGL_DEBUG 1
#endif

#define SGL_MAYOR 0
#define SGL_MINOR 3
#define SGL_PATCH 0

#endif
