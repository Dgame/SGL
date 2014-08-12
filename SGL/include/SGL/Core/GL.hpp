#ifndef SGL_GL_HPP
#define SGL_GL_HPP

#include <SGL/Core/Config.hpp>

#if defined(SGL_OS_WIN32)
#include <GL/glew.h>
#elif defined(SGL_OS_LINUX)
#include <gl/gl.h>
#elif defined(SGL_OS_MAC)
#include <OpenGL/gl.h>
#elif defined(SGL_OS_FREE_BSD)
#include <gl/gl.h>
#else
#error Unsupported OS
#endif

#endif