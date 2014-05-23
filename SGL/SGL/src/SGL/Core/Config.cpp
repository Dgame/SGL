#include <SGL/Core/Config.hpp>

namespace sgl {
	namespace internal {
		static const uint16 Channels = 256;

		bool sdl_init() {
			FunctionScope fexit(sdl_quit);

			if (SDL_Init(SDL_INIT_VIDEO) != 0) {
				println("SDL_Init Error: ", SDL_GetError());

				return false;
			}

			// load support for the JPG and PNG image formats
			int flags = IMG_INIT_JPG | IMG_INIT_PNG;
			int initted = IMG_Init(flags);
			if ((initted & flags) != flags) {
				println("IMG_Init: Failed to init required jpg and png support.");
				println("IMG_Init: ", IMG_GetError());

				return false;
			}

			if (TTF_Init() == -1) {
				println("TTF_Init failed: ", TTF_GetError());

				return false;
			}

			flags = MIX_INIT_OGG | MIX_INIT_MP3;
			initted = Mix_Init(flags);
			if ((initted & flags) != flags) {
				println("Mix_Init: Failed to init required ogg and mod support.");
				println("Mix_Init: ", Mix_GetError());

				return false;
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				println("Mix_OpenAudio: ", Mix_GetError());

				return false;
			}

			Mix_AllocateChannels(Channels);
			const int reserved_count = Mix_ReserveChannels(Channels);
			if (reserved_count != Channels) {
				println(reserved_count, " reserved channels from default mixing.");
				println(Channels, " channels were not reserved.");
			}

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

			fexit.call = false;

			return true;
		}

		void sdl_quit() {
			Mix_CloseAudio();

			// force a quit
			while (Mix_Init(0)) {
				Mix_Quit();
			}

			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
		}
	}
}