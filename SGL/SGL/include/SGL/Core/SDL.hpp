#ifndef SDL_HPP
#define SDL_HPP

#include <memory>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <SGL/Core/Config.hpp>
#include <SGL/Core/Output.hpp>

namespace sgl {
	namespace internal {
		struct SDL {
			explicit SDL(int flags);
			SDL(const SDL&) = delete;
			~SDL();
		};

		struct SDL_Image {
			explicit SDL_Image(int flags);
			SDL_Image(const SDL_Image&) = delete;
			~SDL_Image();
		};

		struct SDL_TTF {
			SDL_TTF();
			SDL_TTF(const SDL_TTF&) = delete;
			~SDL_TTF();
		};


#define SDL_MIX_CHANNELS 256

		struct SDL_Mixer {
			explicit SDL_Mixer(int flags);
			SDL_Mixer(const SDL_Mixer&) = delete;
			~SDL_Mixer();
		};

		static std::unique_ptr<const SDL> sdl_vid_ptr;
		static std::unique_ptr<const SDL_Image> sdl_img_ptr;
		static std::unique_ptr<const SDL_TTF> sdl_ttf_ptr;
		static std::unique_ptr<const SDL_Mixer> sdl_mix_ptr;

		void initSDL();
	}
}

#endif