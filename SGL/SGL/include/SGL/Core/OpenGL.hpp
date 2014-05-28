#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <SGL/Core/Config.hpp>

#if SGL_DEBUG
#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#else
#define glCheck(call) (call)
#endif

void glCheckError(const char* file, unsigned int line);

#endif