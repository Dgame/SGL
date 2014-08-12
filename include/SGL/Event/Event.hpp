#ifndef SGL_EVENT_HPP
#define SGL_EVENT_HPP

#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/System/Keyboard.hpp>
#include <SGL/System/Mouse.hpp>

namespace sgl {
	struct Event {
		enum class Type {
			Quit = SDL_QUIT,	/** Quit Event. Time to close the window. */
			
			Moved,
			Restored,
			Resized,
			Maximized,
			Minimized,

			GainFocus,
			LostFocus,

			KeyDown = SDL_KEYDOWN,	/** A key is pressed. */
			KeyUp = SDL_KEYUP,		/** A key is released. */

			MouseMotion = SDL_MOUSEMOTION,			/** The mouse has moved. */
			MouseButtonDown = SDL_MOUSEBUTTONDOWN,	/** A mouse button is pressed. */
			MouseButtonUp = SDL_MOUSEBUTTONUP,		/** A mouse button is released. */
			MouseWheel = SDL_MOUSEWHEEL,			/** The mouse wheel has scrolled. */
		};

		enum class State {
			Pressed = 1,
			Released = 0
		};

		struct SizeEvent {
			int16 width;
			int16 height;
		};

		typedef struct {
			int16 x;
			int16 y;
		} MoveEvent, Delta;

		struct KeyboardEvent {
			State state;
			Keyboard::Code code;
			
			bool repeat;
			bool alt;
			bool shift;
			bool control;
			bool system;
			bool capslock;
			bool numpad;
			bool mode;
		};

		struct MouseButtonEvent {
			Mouse::Button button;

			int16 x;
			int16 y;
		};

		struct MouseMotionEvent {
			State state;

			int16 x;
			int16 y;

			Delta delta;
		};

		struct MouseWheelEvent {
			int16 x;
			int16 y;

			Delta delta;
		};

		Type type;

		uint32 timestamp; /** Milliseconds since the app is running. */
		int32 windowId;   /** The window which has raised this event. */

		union {
			SizeEvent size;
			MoveEvent move;
			KeyboardEvent keyboard;
			MouseButtonEvent mouseButton;
			MouseWheelEvent mouseWheel;
			MouseMotionEvent mouseMotion;
		};
	};

	bool PollEvent(Event*);
	bool PushEvent(Event::Type type);
	bool WaitEvent(Event*, int32 timeout = -1);
	bool HasEvent(Event::Type type);
}

namespace {
	bool TranslateEvent(const SDL_Event*, sgl::Event*);
}

/**
	sgl::Event event;
	while (sgl::PollEvent(&event)) {
		switch (event.type) {
			case sgl::Event::KeyDown:
				
			break;
		}
	}
*/

#endif