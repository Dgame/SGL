#ifndef SDL_HPP
#define SDL_HPP

#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <SGL/Core/Scope.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Output.hpp>

namespace sgl {
	namespace internal {
		bool sdl_init();
		void sdl_quit();
	}
}

#endif