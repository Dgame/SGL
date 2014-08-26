#ifndef SGL_GL_CHECK_HPP
#define SGL_GL_CHECK_HPP

#include <iostream>

#if SGL_DEBUG
#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#define SDL_Check(call) ((call), SDL_CheckError(__FILE__, __LINE__))
#else
#define glCheck(call) (call)
#define SDL_Check(call) (call)
#endif

void glCheckError(const char*, unsigned int line);
void SDL_CheckError(const char*, unsigned int line);

#endif