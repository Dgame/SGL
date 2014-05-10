#include <SGL/Window/Config.hpp>

namespace internal {
	static const uint16 Channels = 256;

	void sdl_init() {
		FunctionScope fexit(sdl_quit);

		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			printf("SDL_Init Error: %s\n", SDL_GetError());

			return;
		}

		// load support for the JPG and PNG image formats
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted & flags) != flags) {
			printf("IMG_Init: Failed to init required jpg and png support.\n");
			printf("IMG_Init: %s\n", IMG_GetError());

			return;
		}

		if (TTF_Init() == -1) {
			printf("TTF_Init failed: %s\n", TTF_GetError());

			return;
		}

		flags = MIX_INIT_OGG | MIX_INIT_MP3;
		initted = Mix_Init(flags);
		if ((initted & flags) != flags) {
			printf("Mix_Init: Failed to init required ogg and mod support!\n");
			printf("Mix_Init: %s\n", Mix_GetError());

			return;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			printf("Mix_OpenAudio: %s\n", Mix_GetError());

			return;
		}

		Mix_AllocateChannels(Channels);
		const int reserved_count = Mix_ReserveChannels(Channels);
		if (reserved_count != Channels) {
			printf("reserved %d channels from default mixing.\n", reserved_count);
			printf("%d channels were not reserved!\n", Channels);
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		fexit.call = false;
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