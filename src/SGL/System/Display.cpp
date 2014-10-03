#include <SGL/System/Display.hpp>
#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Check.hpp>

namespace sgl {
    DisplayMode::DisplayMode(uint16 the_width, uint16 the_height, uint16 the_refresh_rate) :
        width(the_width), height(the_height), refresh_rate(the_refresh_rate)
    {

    }

    void Copy(const SDL_DisplayMode* sdl_mode, DisplayMode& mode) {
        mode.width = sdl_mode->w;
        mode.height = sdl_mode->h;
        mode.refresh_rate = sdl_mode->refresh_rate;
    }

	void Copy(const DisplayMode& mode, SDL_DisplayMode* sdl_mode) {
        sdl_mode->format = SDL_PIXELFORMAT_UNKNOWN;
        sdl_mode->w = mode.width;
        sdl_mode->h = mode.height;
        sdl_mode->refresh_rate = mode.refresh_rate;
        sdl_mode->driverdata = nullptr;
	}

    int16 GetWindowDisplayIndex() {
        SDL_Window* window = SDL_GL_GetCurrentWindow();

        return SDL_Check(SDL_GetWindowDisplayIndex(window));
    }

    DisplayMode GetDesktopDisplayMode(uint16 index) {
        SDL_DisplayMode sdl_mode;
        DisplayMode mode;

        const int result = SDL_Check(SDL_GetDesktopDisplayMode(index, &sdl_mode));
	    if (result == 0)
            Copy(&sdl_mode, mode);

	    return mode;
	}

	DisplayMode GetCurrentDisplayMode(uint16 index) {
	    SDL_DisplayMode sdl_mode;
        DisplayMode mode;

        const int result = SDL_Check(SDL_GetCurrentDisplayMode(index, &sdl_mode));
	    if (result == 0)
            Copy(&sdl_mode, mode);

	    return mode;
	}

    DisplayMode GetClosestDisplayMode(const DisplayMode& mode, uint16 index) {
        SDL_DisplayMode sdl_mode;
        Copy(mode, &sdl_mode);

        DisplayMode closest;
        SDL_DisplayMode sdl_closest;
        if (SDL_GetClosestDisplayMode(index, &sdl_mode, &sdl_closest))
            Copy(&sdl_closest, closest);

        return closest;
    }

	int16 GetNumDisplayModes(uint16 index) {
	    return SDL_Check(SDL_GetNumDisplayModes(index));
	}

	ShortRect GetDisplayBounds(uint16 index) {
		SDL_Rect sdl_rect;
		const int result = SDL_Check(SDL_GetDisplayBounds(index, &sdl_rect));

		ShortRect rect;
		if (result == 0)
			Copy(&sdl_rect, rect);

		return rect;
	}

	int16 GetNumVideoDisplays() {
		return SDL_Check(SDL_GetNumVideoDisplays());
	}
}
