#include <SGL/Event/Event.hpp>

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
		if (type == Event::Type::Quit)
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
					event->type = sgl::Event::Type::GainFocus;

					return true;
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					event->type = sgl::Event::Type::LostFocus;

					return true;
				case SDL_WINDOWEVENT_CLOSE:
					event->type = sgl::Event::Type::Quit;

					return true;
				case SDL_WINDOWEVENT_MOVED:
					event->type = sgl::Event::Type::Moved;

					event->move.x = src->window.data1;
					event->move.y = src->window.data2;

					return true;
				case SDL_WINDOWEVENT_RESIZED:
					event->type = sgl::Event::Type::Resized;

					event->size.width = src->window.data1;
					event->size.height = src->window.data2;

					return true;
				case SDL_WINDOWEVENT_MINIMIZED:
					event->type = sgl::Event::Type::Minimized;

					return true;
				case SDL_WINDOWEVENT_MAXIMIZED:
					event->type = sgl::Event::Type::Maximized;

					return true;
				case SDL_WINDOWEVENT_RESTORED:
					event->type = sgl::Event::Type::Restored;

					return true;
			}

			return false;
		}

		event->type = static_cast<sgl::Event::Type>(src->type);

		switch (event->type) {
			case sgl::Event::Type::KeyDown:
			case sgl::Event::Type::KeyUp:
				event->timestamp = src->key.timestamp;
				event->windowId = src->key.windowID;

				event->keyboard.code = static_cast<sgl::Keyboard::Code>(src->key.keysym.sym);
				event->keyboard.repeat = src->key.repeat != 0;
				event->keyboard.state = static_cast<sgl::Event::State>(src->key.state);
			{
				const SDL_Keymod mod = SDL_GetModState();
				if (mod & KMOD_NUM)
					event->keyboard.numpad = true;
				if (mod & KMOD_CAPS)
					event->keyboard.capslock = true;
				if (mod & KMOD_SHIFT)
					event->keyboard.shift = true;
				if (mod & KMOD_ALT)
					event->keyboard.alt = true;
				if (mod & KMOD_CTRL)
					event->keyboard.control = true;
				if (mod & KMOD_GUI)
					event->keyboard.system = true;
				if (mod & KMOD_MODE)
					event->keyboard.mode = true;
			}
				return true;
			case sgl::Event::Type::Quit:
				event->timestamp = src->quit.timestamp;
				event->windowId = 0;

				return true;
			case sgl::Event::Type::MouseButtonDown:
			case sgl::Event::Type::MouseButtonUp:
				event->timestamp = src->button.timestamp;
				event->windowId = src->button.windowID;

				event->mouseButton.button = static_cast<sgl::Mouse::Button>(src->button.button);

				event->mouseButton.x = src->button.x;
				event->mouseButton.y = src->button.y;

				return true;
			case sgl::Event::Type::MouseMotion:
				event->timestamp = src->motion.timestamp;
				event->windowId = src->motion.windowID;

				event->mouseMotion.state = static_cast<sgl::Event::State>(src->button.state);

				event->mouseMotion.x = src->motion.x;
				event->mouseMotion.y = src->motion.y;

				event->mouseMotion.delta.x = src->motion.xrel;
				event->mouseMotion.delta.y = src->motion.yrel;

				return true;
			case sgl::Event::Type::MouseWheel:
				event->timestamp = src->wheel.timestamp;
				event->windowId = src->wheel.windowID;

				event->mouseWheel.delta.x = src->wheel.x;
				event->mouseWheel.delta.y = src->wheel.y;

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