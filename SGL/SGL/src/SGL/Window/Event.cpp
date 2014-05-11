#include <SGL/Window/Event.hpp>

namespace sgl {
	bool Event::_Process(Event& event, const SDL_Event& sdl_event) {
		const Event::Type sdl_type = static_cast<Event::Type>(sdl_event.type);

		switch (sdl_type) {
			case Event::Type::KeyDown:
			case Event::Type::KeyUp:
				event.type = sdl_type == Event::Type::KeyDown ? Event::Type::KeyDown : Event::Type::KeyUp;

				event.timestamp = sdl_event.key.timestamp;
				event.windowId = sdl_event.key.windowID;

				event.keyboard.key = static_cast<Keyboard::Code>(sdl_event.key.keysym.sym);
				event.keyboard.repeat = sdl_event.key.repeat != 0;
				event.keyboard.state = static_cast<Keyboard::State>(sdl_event.key.state);

				event.keyboard.mod = Keyboard::GetModifier();

				return true;
			case Event::Type::Window:
				event.type = Event::Type::Window;

				event.windowId = sdl_event.window.windowID;
				event.timestamp = sdl_event.window.timestamp;

				event.window.event = static_cast<Event::Window>(sdl_event.window.event);

				return true;
			case Event::Type::Quit:
				event.type = Event::Type::Quit;

				return true;
			case Event::Type::MouseButtonDown:
			case Event::Type::MouseButtonUp:
				if (sdl_type == Event::Type::MouseButtonUp)
					event.type = Event::Type::MouseButtonUp;
				else
					event.type = Event::Type::MouseButtonDown;

				event.timestamp = sdl_event.button.timestamp;
				event.windowId = sdl_event.button.windowID;

				event.mouseButton.button = static_cast<Mouse::Button>(sdl_event.button.button);

				event.mouseButton.x = sdl_event.button.x;
				event.mouseButton.y = sdl_event.button.y;

				return true;
			case Event::Type::MouseMotion:
				event.type = Event::Type::MouseMotion;

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
			case Event::Type::MouseWheel:
				event.type = Event::Type::MouseWheel;

				event.timestamp = sdl_event.wheel.timestamp;
				event.windowId = sdl_event.wheel.windowID;

				event.mouseWheel.x = sdl_event.wheel.x;
				event.mouseWheel.y = sdl_event.wheel.y;

				event.mouseWheel.delta_x = sdl_event.wheel.x;
				event.mouseWheel.delta_y = sdl_event.wheel.y;

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
	bool Event::Push(Event::Type type) {
		SDL_Event sdl_event;
		sdl_event.type = static_cast<int>(type);

		return SDL_PushEvent(&sdl_event) == 1;
	}


	/**
	* Clear the Event queue.
	*/
	void Event::Clear(Event::Type type) {
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