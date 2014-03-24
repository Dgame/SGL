#ifndef OPENGL_HPP
#define OPENGL_HPP

#if defined(_WIN32) || defined(__WIN32__)

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <GL/gl.h>

#elif defined(linux) || defined(__linux)

#include <GL/gl.h>

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

#include <OpenGL/gl.h>

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

#include <GL/gl.h>

#else

#error Unsupported OS

#endif

#endif