#include <SGL/Window/Event.hpp>

namespace sgl {
	bool Event::_Process(Event& event, const SDL_Event& sdl_event) {
		const Type sdl_type = static_cast<Type>(sdl_event.type);

		switch (sdl_type) {
			case Type::KeyDown:
			case Type::KeyUp:
				event.type = sdl_type == Type::KeyDown ? Type::KeyDown : Type::KeyUp;

				event.timestamp = sdl_event.key.timestamp;
				event.windowId = sdl_event.key.windowID;

				event.keyboard.key = static_cast<Keyboard::Code>(sdl_event.key.keysym.sym);
				event.keyboard.repeat = sdl_event.key.repeat != 0;
				event.keyboard.state = static_cast<Keyboard::State>(sdl_event.key.state);

				event.keyboard.mod = Keyboard::GetModifier();

				return true;
			case Type::Window:
				event.type = Type::Window;

				event.windowId = sdl_event.window.windowID;
				event.timestamp = sdl_event.window.timestamp;

				event.window.event = static_cast<Window>(sdl_event.window.event);
				switch (event.window.event) {
					case Window::Resized:
						event.window.size.width = sdl_event.window.data1;
						event.window.size.height = sdl_event.window.data2;
						break;
					case Window::Moved:
						event.window.move.x = sdl_event.window.data1;
						event.window.move.y = sdl_event.window.data2;
						break;
				}

				return true;
			case Type::Quit:
				event.type = Type::Quit;
				event.timestamp = sdl_event.quit.timestamp;
				event.windowId = 0;

				return true;
			case Type::MouseButtonDown:
			case Type::MouseButtonUp:
				if (sdl_type == Type::MouseButtonUp)
					event.type = Type::MouseButtonUp;
				else
					event.type = Type::MouseButtonDown;

				event.timestamp = sdl_event.button.timestamp;
				event.windowId = sdl_event.button.windowID;

				event.mouseButton.button = static_cast<Mouse::Button>(sdl_event.button.button);

				event.mouseButton.x = sdl_event.button.x;
				event.mouseButton.y = sdl_event.button.y;

				return true;
			case Type::MouseMotion:
				event.type = Type::MouseMotion;

				event.timestamp = sdl_event.motion.timestamp;
				event.windowId = sdl_event.motion.windowID;

				if (sdl_event.button.state == SDL_PRESSED)
					event.mouseMotion.state = Mouse::State::Pressed;
				else
					event.mouseMotion.state = Mouse::State::Released;

				event.mouseMotion.x = sdl_event.motion.x;
				event.mouseMotion.y = sdl_event.motion.y;

				event.mouseMotion.rel_x = sdl_event.motion.xrel;
				event.mouseMotion.rel_y = sdl_event.motion.yrel;

				return true;
			case Type::MouseWheel:
				event.type = Type::MouseWheel;

				event.timestamp = sdl_event.wheel.timestamp;
				event.windowId = sdl_event.wheel.windowID;

				event.mouseWheel.x = sdl_event.wheel.x;
				event.mouseWheel.y = sdl_event.wheel.y;

				event.mouseWheel.delta_x = sdl_event.wheel.x;
				event.mouseWheel.delta_y = sdl_event.wheel.y;

				return true;
			case Type::TextInput:
				event.type = Type::TextInput;

				event.timestamp = sdl_event.text.timestamp;
				event.windowId = sdl_event.text.windowID;

				std::memcpy(&event.input.text, &sdl_event.text.text, sizeof(char) * 32);

				return true;
			case Type::TextEdit:
				event.type = Type::TextEdit;

				event.timestamp = sdl_event.edit.timestamp;
				event.windowId = sdl_event.edit.windowID;

				std::memcpy(&event.edit.text, &sdl_event.edit.text, sizeof(char) * 32);

				event.edit.start = sdl_event.edit.start;
				event.edit.length = sdl_event.edit.length;

				return true;
		}

		return false;
	}

	/**
	* Update the parameter event and set the data of the current event in it.
	*
	* Returns: true, if there was a valid event and false if not.
	*/
	bool Event::Poll(Event& event) {
		SDL_Event sdl_event;
		if (SDL_PollEvent(&sdl_event) == 0)
			return false;

		return Event::_Process(event, sdl_event);
	}

	/**
	* Push an event of the given type inside the Event queue.
	*
	* Returns: if the push was successfull or not.
	*/
	bool Event::Push(Type type) {
		SDL_Event sdl_event;
		sdl_event.type = static_cast<int>(type);

		return SDL_PushEvent(&sdl_event) == 1;
	}


	/**
	* Clear the Event queue.
	*/
	void Event::Clear(Type type) {
		SDL_FlushEvent(static_cast<int>(type));
	}

	/**
	* Set a state for a Type
	* Returns: the previous Type
	* See: State enum
	*/
	Event::State Event::SetState(Type type, Event::State state) {
		return static_cast<Event::State>(SDL_EventState(static_cast<int>(type), static_cast<int>(state)));
	}

	/**
	* Returns: if inside of the Event Queue is an Event of the given Type::
	*/
	bool Event::HasEvent(Type type) {
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
	bool Event::Wait(Event& event, int timeout) {
		int result = 0;
		SDL_Event sdl_event;

		if (timeout < 0)
			result = SDL_WaitEvent(&sdl_event);
		else
			result = SDL_WaitEventTimeout(&sdl_event, timeout);

		if (result > 0)
			return Event::_Process(event, sdl_event);

		return false;
	}
}