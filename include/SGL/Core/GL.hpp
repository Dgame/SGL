#ifndef SGL_GL_HPP
#define SGL_GL_HPP

#include <SGL/Core/Config.hpp>

#if defined(SGL_OS_WINDOWS)
    #if defined(SGL_OS_WIN64) && SGL_USE_X64
        #include "../libs/64/GL/glew.h"
    #else
        #include "../libs/32/GL/glew.h"
    #endif
#elif defined(SGL_OS_MAC)
    #include <OpenGL/gl.h>
#endif

#if defined(SGL_OS_WINDOWS) || defined(SGL_OS_LINUX) || defined(SGL_OS_FREE_BSD)
    #include <gl/gl.h>
#endif

#if defined(SGL_OS_WINDOWS)
    #define NOMINMAX 1
    #include <windows.h>
    #undef NOMINMAX
#endif

#endif
