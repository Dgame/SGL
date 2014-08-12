#include <SGL/System/Event.hpp>

namespace sgl {
	bool PollEvent(Event* event) {
		SDL_Event src;
		if (SDL_PollEvent(&src) == 0)
			return false;

		return TranslateEvent(&src, event);
	}

	bool PushEvent(Event::Type type) {
		SDL_Event dst;
		dst.type = static_cast<int>(type);

		return SDL_PushEvent(&dst) == 1;
	}

	bool WaitEvent(Event* event, int32 timeout) {
		SDL_Event src;

		int result = 0;
		if (timeout < 0)
			result = SDL_WaitEvent(&src);
		else
			result = SDL_WaitEventTimeout(&src, timeout);

		if (result != 0)
			return TranslateEvent(&src, event);

		return false;
	}

	bool HasEvent(Event::Type type) {
		if (type == Event::Quit)
			return SDL_QuitRequested();
		return SDL_HasEvent(static_cast<int>(type)) == SDL_TRUE;
	}
}

namespace {
	bool TranslateEvent(const SDL_Event* src, sgl::Event* event) {
		if (src->type == SDL_WINDOWEVENT) {
			event->timestamp = src->window.timestamp;
			event->windowId = src->window.windowID;

			switch (src->window.event) {
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					event->type = sgl::Event::Window::Focus;
					event->window.focus = sgl::Event::Focus::Gain;

					return true;
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					event->type = sgl::Event::Window::Focus;
					event->window.focus = sgl::Event::Focus::Lost;

					return true;
				case SDL_WINDOWEVENT_CLOSE:
					//event->type = sgl::Event::Quit;
					event->type = sgl::Event::Window::Close;

					return true;
				case SDL_WINDOWEVENT_MOVED:
					event->type = sgl::Event::Window::Moved;

					event->window.move.x = src->window.data1;
					event->window.move.y = src->window.data2;

					return true;
				case SDL_WINDOWEVENT_RESIZED:
					event->type = sgl::Event::Window::Resized;

					event->window.size.width = src->window.data1;
					event->window.size.height = src->window.data2;

					return true;
				case SDL_WINDOWEVENT_MINIMIZED:
					event->type = sgl::Event::Window::Minimized;

					return true;
				case SDL_WINDOWEVENT_MAXIMIZED:
					event->type = sgl::Event::Window::Maximized;

					return true;
				case SDL_WINDOWEVENT_RESTORED:
					event->type = sgl::Event::Window::Restored;

					return true;
			}

			return false;
		}

		switch (src->type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if (src->type == SDL_KEYUP)
					event->type = sgl::Event::Key::Up;
				else
					event->type = sgl::Event::Key::Down;

				event->timestamp = src->key.timestamp;
				event->windowId = src->key.windowID;

				event->key.key = static_cast<sgl::Keyboard::Key>(src->key.keysym.sym);
				event->key.repeat = src->key.repeat != 0;

				{
					const SDL_Keymod mod = SDL_GetModState();
					if (mod & KMOD_NUM)
						event->key.numpad = true;
					if (mod & KMOD_CAPS)
						event->key.capslock = true;
					if (mod & KMOD_SHIFT)
						event->key.shift = true;
					if (mod & KMOD_ALT)
						event->key.alt = true;
					if (mod & KMOD_CTRL)
						event->key.control = true;
					if (mod & KMOD_GUI)
						event->key.system = true;
					if (mod & KMOD_MODE)
						event->key.mode = true;
				}

				return true;
			case SDL_QUIT:
				event->type = sgl::Event::Quit;
				event->timestamp = src->quit.timestamp;
				event->windowId = 0;

				return true;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				if (src->type == SDL_MOUSEBUTTONUP)
					event->type = sgl::Event::Mouse::Button::Up;
				else
					event->type = sgl::Event::Mouse::Button::Down;

				event->timestamp = src->button.timestamp;
				event->windowId = src->button.windowID;

				event->mouse.type = sgl::Event::Mouse::Button;
				event->mouse.button.button = static_cast<sgl::Mouse::Button>(src->button.button);
				event->mouse.button.x = src->button.x;
				event->mouse.button.y = src->button.y;

				return true;
			case SDL_MOUSEMOTION:
				event->type = sgl::Event::Mouse::Motion;
				event->timestamp = src->motion.timestamp;
				event->windowId = src->motion.windowID;

				if (src->motion.state == SDL_PRESSED)
					event->mouse.motion.button = sgl::Event::Mouse::Button::Down;
				else
					event->mouse.motion.button = sgl::Event::Mouse::Button::Up;

				event->mouse.type = sgl::Event::Mouse::Motion;
				event->mouse.motion.x = src->motion.x;
				event->mouse.motion.y = src->motion.y;
				event->mouse.motion.delta.x = src->motion.xrel;
				event->mouse.motion.delta.y = src->motion.yrel;

				return true;
			case SDL_MOUSEWHEEL:
				event->type = sgl::Event::Mouse::Wheel;
				event->timestamp = src->wheel.timestamp;
				event->windowId = src->wheel.windowID;

				event->mouse.type = sgl::Event::Mouse::Wheel;
				event->mouse.wheel.delta.x = src->wheel.x;
				event->mouse.wheel.delta.y = src->wheel.y;

				return true;
			/*
			case sgl::Event::Type::TextInput:
				event->timestamp = src->text.timestamp;
				event->windowId = src->text.windowID;

				std::memcpy(&event->input.text, &src->text.text, sizeof(char) * 32);

				return true;
			case sgl::Event::Type::TextEdit:
				event->timestamp = src->edit.timestamp;
				event->windowId = src->edit.windowID;

				std::memcpy(&event->edit.text, &src->edit.text, sizeof(char) * 32);

				event->edit.start = src->edit.start;
				event->edit.length = src->edit.length;

				return true;*/
		}

		return false;
	}
}