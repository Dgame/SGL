#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SDL.h>
#include <SGL/Math/Vector2.hpp>

namespace sgl {
	class Window;
	class Surface;

	namespace internal {
		class Cursor final {
		private:
			SDL_Cursor* _cursor = nullptr;

		public:
			~Cursor();
			void operator =(SDL_Cursor* cursor);
		};

		static Cursor CurrentCursor;
	}

	/**
	 * Represent the Mouse
	 */
	struct Mouse {
		/**
		 * Supported mouse buttons
		 */
		enum class Button : short {
			Left = 1, /** */
			Middle = 2, /** */
			Right = 3, /** */
			X1 = 4, /** */
			X2 = 5, /** */
			Other /** */
		};

		/**
		 * Supported mouse states
		 */
		enum class State : short {
			Released, /** */
			Pressed /** */
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

		static void SetCursor(Cursor cursor);
		static void SetCursor(const Surface& srfc);
		static void ShowCursor(bool show);
		static bool IsCursorShown();
		static void SetPosition(const Window& wnd, int16 x, int16 y);
		static void SetPosition(const Window& wnd, const Vector2s& position);
		static Vector2s GetPosition();
		static bool IsButtonPressed(Button btn);
	};
}

#endif