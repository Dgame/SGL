#include <SGL/System/Event.hpp>

namespace {
    bool TranslateEvent(const SDL_Event* src, sgl::Event* event) {
        if (src->type == SDL_WINDOWEVENT) {
            event->type = static_cast<sgl::Event::Type>(src->window.event);
            event->timestamp = src->window.timestamp;
            event->windowId = src->window.windowID;

            switch (src->window.event) {
                case SDL_WINDOWEVENT_MOVED:
                    event->window.move.x = src->window.data1;
                    event->window.move.y = src->window.data2;
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    event->window.size.width = src->window.data1;
                    event->window.size.height = src->window.data2;
                    break;
            }

            return true;
        }

        event->type = static_cast<sgl::Event::Type>(src->type);

        switch (src->type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                event->timestamp = src->key.timestamp;
                event->windowId = src->key.windowID;

                event->key.key = static_cast<sgl::Key>(src->key.keysym.sym);
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
                event->timestamp = src->quit.timestamp;
                event->windowId = 0;

                return true;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                event->timestamp = src->button.timestamp;
                event->windowId = src->button.windowID;

                event->mouse.button.button = static_cast<sgl::Mouse::Button>(src->button.button);
                event->mouse.button.x = src->button.x;
                event->mouse.button.y = src->button.y;

                return true;
            case SDL_MOUSEMOTION:
                event->timestamp = src->motion.timestamp;
                event->windowId = src->motion.windowID;

                event->mouse.motion.x = src->motion.x;
                event->mouse.motion.y = src->motion.y;
                event->mouse.motion.delta.x = src->motion.xrel;
                event->mouse.motion.delta.y = src->motion.yrel;

                return true;
            case SDL_MOUSEWHEEL:
                event->timestamp = src->wheel.timestamp;
                event->windowId = src->wheel.windowID;

                event->mouse.wheel.delta.x = src->wheel.x;
                event->mouse.wheel.delta.y = src->wheel.y;

                return true;
        }

        return false;
    }
}

namespace sgl {
    bool PollEvent(Event* event) {
        SDL_Event src;
        if (SDL_PollEvent(&src) == 0)
            return false;

        return TranslateEvent(&src, event);
    }

    bool PushEvent(Event::Type type) {
        SDL_Event dst;
        dst.type = static_cast<SDL_EventType>(type);

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
        return SDL_HasEvent(static_cast<SDL_EventType>(type)) == SDL_TRUE;
    }
}
