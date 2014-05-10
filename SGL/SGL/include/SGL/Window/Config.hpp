#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <SGL/Core/Scope.hpp>
#include <SGL/Core/Types.hpp>

using sgl::FunctionScope;

namespace internal {
	void sdl_init();
	void sdl_quit();
}

#endif