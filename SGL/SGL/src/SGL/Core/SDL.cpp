#include <SGL/Core/SDL.hpp>

namespace sgl {
	namespace internal {
		void initSDL() {
			sdl_vid_ptr = std::make_unique<const SDL>(SDL_INIT_VIDEO);
			sdl_img_ptr = std::make_unique<const SDL_Image>(IMG_INIT_JPG | IMG_INIT_PNG);
			sdl_ttf_ptr = std::make_unique<const SDL_TTF>();
			sdl_mix_ptr = std::make_unique<const SDL_Mixer>(MIX_INIT_OGG | MIX_INIT_MP3);
		}

		SDL::SDL(int flags) {
			if (SDL_Init(flags) != 0)
				error("SDL_Init Error: ", SDL_GetError());
#if SGL_DEBUG
			println("Init SDL Video");
#endif
		}

		SDL::~SDL() {
#if SGL_DEBUG
			println("Quit SDL Video");
#endif
			SDL_Quit();
		}

		SDL_Image::SDL_Image(int flags) {
			int initted = IMG_Init(flags);
			if ((initted & flags) != flags)
				error("IMG_Init: Failed to init required jpg and png support: ", IMG_GetError());
#if SGL_DEBUG
			println("Init SDL Image");
#endif
		}

		SDL_Image::~SDL_Image() {
#if SGL_DEBUG
			println("Quit SDL Image");
#endif
			IMG_Quit();
		}

		SDL_TTF::SDL_TTF() {
			if (TTF_Init() == -1)
				error("TTF_Init failed: ", TTF_GetError());
#if SGL_DEBUG
			println("Init SDL TTF");
#endif
		}

		SDL_TTF::~SDL_TTF() {
#if SGL_DEBUG
			println("Quit SDL TTF");
#endif
			TTF_Quit();
		}

		SDL_Mixer::SDL_Mixer(int flags) {
			int initted = Mix_Init(flags);
			if ((initted & flags) != flags)
				error("Mix_Init: Failed to init required ogg and mod support: ", Mix_GetError());

			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
				error("Mix_OpenAudio: ", Mix_GetError());

			Mix_AllocateChannels(SDL_MIX_CHANNELS);
			const int reserved_count = Mix_ReserveChannels(SDL_MIX_CHANNELS);
			if (reserved_count != SDL_MIX_CHANNELS)
				println(reserved_count, " reserved channels from default mixing, ", SDL_MIX_CHANNELS, " channels were not reserved.");

#if SGL_DEBUG
			println("Init SDL Mixer");
#endif
		}

		SDL_Mixer::~SDL_Mixer() {
#if SGL_DEBUG
			println("Quit SDL Mixer");
#endif
			Mix_CloseAudio();

			// force a quit
			while (Mix_Init(0)) {
				Mix_Quit();
			}
		}
	}
}