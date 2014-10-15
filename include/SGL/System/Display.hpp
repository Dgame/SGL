#ifndef SGL_DISPLAY_HPP
#define SGL_DISPLAY_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	struct DisplayMode {
	    uint16 width = 0;
	    uint16 height = 0;
	    uint16 refresh_rate = 0;

	    DisplayMode() = default;
	    explicit DisplayMode(uint16 the_width, uint16 the_height, uint16 the_refresh_rate = 0);
	};

	void Copy(const SDL_DisplayMode*, DisplayMode&);
	void Copy(const DisplayMode&, SDL_DisplayMode*);

	int16 GetCurrentWindowDisplayIndex();

	DisplayMode GetDesktopDisplayMode(uint16 index = 0);
	DisplayMode GetCurrentDisplayMode(uint16 index = 0);

	DisplayMode GetClosestDisplayMode(const DisplayMode&, uint16 index = 0);
	int16 GetNumDisplayModes(uint16 index = 0);

	ShortRect GetDisplayBounds(uint16 index = 0);
	int16 GetNumVideoDisplays();
}

#endif // SGL_DISPLAY_HPP
