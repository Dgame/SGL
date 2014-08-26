#ifndef SGL_CONFIG_HPP
#define SGL_CONFIG_HPP

#if defined(_WIN32) || defined(__WIN32__)
#define SGL_OS_WIN32
#elif defined(linux) || defined(__linux)
#define SGL_OS_LINUX
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#define SGL_OS_MAC
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define SGL_OS_FREE_BSD
#endif

#ifndef _DEBUG
#ifndef NDEBUG
#define SGL_DEBUG 1
#else
#define SGL_DEBUG 0
#endif
#else
#define SGL_DEBUG 1
#endif

#define SGL_MAYOR 0
#define SGL_MINOR 2

#endif