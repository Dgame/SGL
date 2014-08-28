#ifndef SGL_EVENT_HPP
#define SGL_EVENT_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/System/Keyboard.hpp>
#include <SGL/System/Mouse.hpp>

namespace sgl {
	struct Event {
		enum Type {
			Quit = SDL_QUIT,

			KeyUp = SDL_KEYUP,
			KeyDown = SDL_KEYDOWN,

			MouseButtonDown = SDL_MOUSEBUTTONDOWN,
			MouseButtonUp = SDL_MOUSEBUTTONUP,
			MouseWheel = SDL_MOUSEWHEEL,
			MouseMotion = SDL_MOUSEMOTION,

			WindowExposed = SDL_WINDOWEVENT_EXPOSED,
			WindowShown = SDL_WINDOWEVENT_SHOWN,
			WindowEnter = SDL_WINDOWEVENT_ENTER,
			WindowFocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,
			WindowHidden = SDL_WINDOWEVENT_HIDDEN,
			WindowLeave = SDL_WINDOWEVENT_LEAVE,
			WindowFocusLost = SDL_WINDOWEVENT_FOCUS_LOST,
			WindowClose = SDL_WINDOWEVENT_CLOSE,
			WindowMoved = SDL_WINDOWEVENT_MOVED,
			WindowResized = SDL_WINDOWEVENT_RESIZED,
			WindowMinimized = SDL_WINDOWEVENT_MINIMIZED,
			WindowMaximized = SDL_WINDOWEVENT_MAXIMIZED,
			WindowRestored = SDL_WINDOWEVENT_RESTORED
		};

		struct SizeEvent {
			int16 width;
			int16 height;
		};

		typedef struct {
			int16 x;
			int16 y;
		} MoveEvent, Delta;

		struct WindowEvent {
			union {
				SizeEvent size;
				MoveEvent move;
			};
		};

		struct KeyboardEvent {
			sgl::Key key;
			
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
			sgl::Mouse::Button button;

			int16 x;
			int16 y;
		};

		struct MouseMotionEvent {
			Delta delta;

			int16 x;
			int16 y;
		};

		struct MouseWheelEvent {
			int16 x;
			int16 y;

			Delta delta;
		};

		struct MouseEvent {
			union {
				MouseButtonEvent button;
				MouseMotionEvent motion;
				MouseWheelEvent wheel;
			};
		};

		Type type;

		uint32 timestamp; /** Milliseconds since the app is running. */
		int32 windowId;   /** The window which has raised this event. */

		union {
			WindowEvent window;
			KeyboardEvent key;
			MouseEvent mouse;
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
			case sgl::Event::Key::Down:
				
			break;
		}
	}
*/

#endif