#ifndef SGL_MOUSE_HPP
#define SGL_MOUSE_HPP

#include <SGL/Core/SDL.hpp>

namespace sgl {
	/**
	 * Represent the Mouse
	 */
	struct Mouse {
		/**
		 * Supported mouse buttons
		 */
		enum class Button {
			Left = 1, /** */
			Middle = 2, /** */
			Right = 3, /** */
			X1 = 4, /** */
			X2 = 5, /** */
			Other = 6 /** */
		};

		enum class Cursor {
			Arrow = SDL_SYSTEM_CURSOR_ARROW,
			IBeam = SDL_SYSTEM_CURSOR_IBEAM,
			Wait = SDL_SYSTEM_CURSOR_WAIT,
			CrossHair = SDL_SYSTEM_CURSOR_CROSSHAIR,
			WaitArrow = SDL_SYSTEM_CURSOR_WAITARROW,
			SizeNWSE = SDL_SYSTEM_CURSOR_SIZENWSE,
			SizeNESW = SDL_SYSTEM_CURSOR_SIZENESW,
			SizeWE = SDL_SYSTEM_CURSOR_SIZEWE,
			SizeNS = SDL_SYSTEM_CURSOR_SIZENS,
			SizeAll = SDL_SYSTEM_CURSOR_SIZEALL,
			No = SDL_SYSTEM_CURSOR_NO,
			Hand = SDL_SYSTEM_CURSOR_HAND
		};
	};
}

#endif