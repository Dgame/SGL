#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Check.hpp>
#include <SGL/System/Display.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	ShortRect GetDisplayBounds(uint16 index) {
		SDL_Rect sdl_rect;
		const int result = SDL_Check(SDL_GetDisplayBounds(index, &sdl_rect));

		ShortRect rect;
		if (result == 0)
			Copy(&sdl_rect, rect);

		return rect;
	}

	int16 GetWindowDisplayIndex(const Window& wnd) {
		SDL_Window* window = SDL_GetWindowFromID(wnd.getID());

		return SDL_GetWindowDisplayIndex(window);
	}

	int16 GetNumVideoDisplays() {
		return SDL_GetNumVideoDisplays();
	}
}
