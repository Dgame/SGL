#ifndef SGL_EVENT_HPP
#define SGL_EVENT_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/System/Keyboard.hpp>
#include <SGL/System/Mouse.hpp>

namespace sgl {
	struct Event {
		enum class Focus {
			Lost = SDL_WINDOWEVENT_FOCUS_GAINED,
			Gain = SDL_WINDOWEVENT_FOCUS_LOST
		};

		struct Window {
			enum Event {
				Moved = SDL_WINDOWEVENT_MOVED,
				Restored = SDL_WINDOWEVENT_RESTORED,
				Resized = SDL_WINDOWEVENT_RESIZED,
				Maximized = SDL_WINDOWEVENT_MAXIMIZED,
				Minimized = SDL_WINDOWEVENT_MINIMIZED,
				Close = SDL_WINDOWEVENT_CLOSE,
				Focus = SDL_WINDOW_INPUT_FOCUS
			};
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
			Focus focus;

			union {
				SizeEvent size;
				MoveEvent move;
			};
		};

		struct Key {
			enum Type {
				Down = SDL_KEYDOWN,
				Up = SDL_KEYUP
			};
		};

		struct KeyboardEvent {
			Keyboard::Key key;
			
			bool repeat;
			bool alt;
			bool shift;
			bool control;
			bool system;
			bool capslock;
			bool numpad;
			bool mode;
		};

		struct Mouse {
			enum Type {
				Button = 0x10,
				Wheel = 0x20,
				Motion = 0x30
			};

			struct Button {
				enum Type {
					Down = SDL_MOUSEBUTTONDOWN,
					Up = SDL_MOUSEBUTTONUP
				};
			};
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

			Mouse::Button::Type button;
		};

		struct MouseWheelEvent {
			int16 x;
			int16 y;

			Delta delta;
		};

		struct MouseEvent {
			Mouse::Type type;

			union {
				MouseButtonEvent button;
				MouseMotionEvent motion;
				MouseWheelEvent wheel;
			};
		};

		enum {
			Quit = SDL_QUIT
		};

		typedef uint32 Type;

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