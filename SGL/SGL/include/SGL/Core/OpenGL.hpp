#ifndef OPENGL_HPP
#define OPENGL_HPP

#if defined(_WIN32) || defined(__WIN32__)

#ifdef _MSC_VER

#include <windows.h>

#undef min
#undef max

#endif

#include <GL/glew.h>

#elif defined(linux) || defined(__linux)

#include <gl/gl.h>

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

#include <OpenGL/gl.h>

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

#include <gl/gl.h>

#else

#error Unsupported OS

#endif

#if _DEBUG

#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))

#else

#define glCheck(call) (call)

#endif

void glCheckError(const char* file, unsigned int line);

#endif