#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <SDL.h>
#include <SGL/Core/Types.hpp>
#include <SGL/System/Mouse.hpp>
#include <SGL/System/Keyboard.hpp>

/*
*******************************************************************************************
* Dgame (a D game framework) - Copyright (c) Randy Schütt
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim
*    that you wrote the original software. If you use this software in a product,
*    an acknowledgment in the product documentation would be appreciated but is
*    not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*******************************************************************************************
*/

namespace sgl {
	/**
	* The Event structure.
	* Event defines a system event and it's parameters
	*
	* Author: rschuett
	*/
	struct Event {
		/**
		* Specific Window Events.
		*/
		enum class Window : short {
			None,           /** Nothing happens */
			Shown,          /** Window has been shown */
			Hidden,         /** Window has been hidden */
			Exposed,        /** Window has been exposed and should be redrawn */
			Moved,          /** Window has been moved to data1, data2  */
			Resized,        /** Window has been resized to data1Xdata2 */
			/**
			* The window size has changed,
			* either as a result of an API call or through
			* the system or user changing the window size.
			*/
			SizeChanged,
			Minimized,      /** Window has been minimized. */
			Maximized,      /** Window has been maximized. */
			Restored,       /** Window has been restored to normal size and position. */
			Enter,          /** Window has gained mouse focus. */
			Leave,          /** Window has lost mouse focus. */
			FocusGained,    /** Window has gained keyboard focus. */
			FocusLost,      /** Window has lost keyboard focus. */
			Close           /** The window manager requests that the window be closed. */
		};

		/**
		* All supported Event Types.
		*/
		enum class Type {
			Quit = SDL_QUIT,			/** Quit Event. Time to close the window. */
			Window = SDL_WINDOWEVENT,	/** Something happens with the window. */
			KeyDown = SDL_KEYDOWN,		/** A key is pressed. */
			KeyUp = SDL_KEYUP,		/** A key is released. */
			MouseMotion = SDL_MOUSEMOTION,	/** The mouse has moved. */
			MouseButtonDown = SDL_MOUSEBUTTONDOWN,	/** A mouse button is pressed. */
			MouseButtonUp = SDL_MOUSEBUTTONUP,	/** A mouse button is released. */
			MouseWheel = SDL_MOUSEWHEEL,		/** The mouse wheel has scolled. */
			TextEdit = SDL_TEXTEDITING,            /**< Keyboard text editing (composition) */
			TextInput = SDL_TEXTINPUT              /**< Keyboard text input */
		};

		enum class State {
			Query = SDL_QUERY,
			Ignore = SDL_IGNORE,
			Disable = SDL_DISABLE,
			Enable = SDL_ENABLE
		};

		Type type; /** The Event Type. */

		uint32 timestamp; /** Milliseconds since the app is running. */
		uint32 windowId;   /** The window which has raised this event. */

		/**
		* The Keyboard Event structure.
		*/
		struct KeyboardEvent {
			Keyboard::State state;	/** Keyboard State. See: Keyboard::State */
			Keyboard::Code key;	/** The Key which is released or pressed. */
			Keyboard::Mod mod;	/** The Key modifier. */

			bool repeat;	/** true, if this is a key repeat. */
		};

		/**
		* Keyboard text editing event structure
		*/
		struct TextEditEvent {
			std::string text; /**< The editing text */
			short start; /**< The start cursor of selected editing text */
			uint16 length; /**< The length of selected editing text */
		};

		/**
		* Keyboard text input event structure
		*/
		struct TextInputEvent {
			std::string text; /**< The input text */
		};

		/**
		* The Window Event structure.
		*/
		struct WindowEvent {
			Window event; /** < The Window Event id. */
		};

		/**
		* The Mouse button Event structure.
		*/
		struct MouseButtonEvent {
			Mouse::Button button; /** The mouse button which is pressed or released. */

			short x; /** Current x position. */
			short y; /** Current y position. */
		};

		/**
		* The Mouse motion Event structure.
		*/
		struct MouseMotionEvent {
			Mouse::State state; /** Mouse State. See: Dgame.Input.Mouse. */

			short x; /** Current x position. */
			short y; /** Current y position. */

			short rel_x; /** Relative motion in the x direction. */
			short rel_y; /** Relative motion in the y direction. */
		};

		/**
		* The Mouse wheel Event structure.
		*/
		struct MouseWheelEvent {
			short x; /** Current x position. */
			short y; /** Current y position. */

			short delta_x; /** The amount scrolled horizontally. */
			short delta_y; /** The amount scrolled vertically. */
		};

		union {
			KeyboardEvent keyboard; /** Keyboard Event. */
			WindowEvent	  window;	/** Window Event. */
			MouseButtonEvent mouseButton; /** Mouse button Event. */
			MouseMotionEvent mouseMotion; /** Mouse motion Event. */
			MouseWheelEvent  mouseWheel;  /** Mouse wheel Event. */
			//TextEditEvent	 textEdit;	  /** Text edit Event. */
			//TextInputEvent textInput;	  /** Text input Event. */
		};

	private:
		static bool _Process(Event& event, const SDL_Event& sdl_event);

	public:
		/**
		* Update the parameter event and set the data of the current event in it.
		*
		* Returns: true, if there was a valid event and false if not.
		*/
		static bool Poll(Event& event);

		/**
		* Push an event of the given type inside the Event queue.
		* Returns: if the push was successfull or not.
		*/
		static bool Push(Event::Type type);

		/**
		* Clear the Event queue.
		*/
		static void Event::Clear(Event::Type type) {
			SDL_FlushEvent(static_cast<int>(type));
		}

		/**
		* Set a state for a Event::Type
		* Returns: the previous Type
		* See: State enum
		*/
		Event::State Event::SetState(Event::Type type, Event::State state) {
			return static_cast<Event::State>(SDL_EventState(static_cast<int>(type), static_cast<int>(state)));
		}

		/**
		* Returns: if inside of the Event Queue is an Event of the given Type::
		*/
		bool Event::HasEvent(Event::Type type) {
			return SDL_HasEvent(static_cast<int>(type)) == SDL_TRUE;
		}

		/**
		* Returns: if the current Event queue has the Quit Event.
		*/
		bool Event::HasQuitEvent() {
			return SDL_QuitRequested();
		}

		/**
		* Waits for the given Event.
		* If the seconds parameter is greater then -1, it waits maximal timeout seconds.
		*/
		static bool Wait(Event& event, int timeout = -1);
	};
}

#endif