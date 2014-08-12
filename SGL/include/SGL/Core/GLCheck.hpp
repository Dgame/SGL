#ifndef SGL_GL_CHECK_HPP
#define SGL_GL_CHECK_HPP

#include <SGL/Core/GL.hpp>

#if SGL_DEBUG
#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#else
#define glCheck(call) (call)
#endif

void glCheckError(const char*, unsigned int line);

#endif