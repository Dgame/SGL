#ifndef SGL_DISPLAY_HPP
#define SGL_DISPLAY_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	class Window;

	ShortRect GetDisplayBounds(uint16 index = 0);
	int16 GetWindowDisplayIndex(const Window&);
	int16 GetNumVideoDisplays();
}

#endif // SGL_DISPLAY_HPP
