#ifndef SGL_GL_CHECK_HPP
#define SGL_GL_CHECK_HPP

#include <iostream>
#include <SGL/Core/Config.hpp>

#if SGL_DEBUG
    #define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
    #define SDL_Check(call) (SDL_CheckError((call), __FILE__, __LINE__))
#else
    #define glCheck(call) (call)
    #define SDL_Check(call) (call)
#endif

void glCheckError(const char*, unsigned int line);
int SDL_CheckError(int ret, const char*, unsigned int line);

#endif
