#ifndef SGL_INIT_HPP
#define SGL_INIT_HPP

#include <SGL/Core/SDL.hpp>
#include <SGL/Core/GLCheck.hpp>
#include <SGL/Core/Config.hpp>
#include <SGL/Core/Types.hpp>

namespace Intern {
	void initSDL();
	void quitSDL(sgl::uint8 count);
	void initGL();
}

#endif