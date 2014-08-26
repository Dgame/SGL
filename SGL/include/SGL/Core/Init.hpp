#ifndef SGL_INIT_HPP
#define SGL_INIT_HPP

#include <SGL/Core/Config.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Check.hpp>
#include <SGL/Core/GL.hpp>

namespace Intern {
	void initSDL();
	void quitSDL(sgl::uint8 count);
	void initGL();
}

#endif