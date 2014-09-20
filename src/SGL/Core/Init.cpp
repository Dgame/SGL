#include <iostream>
#include <SGL/Core/SDL.hpp>
#include <SGL/Core/GL.hpp>
#include <SGL/Core/Check.hpp>
#include <SGL/Core/Init.hpp>

namespace Intern {
    void initSDL() {
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
                std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
                exit(1);
            }

            int flags = IMG_INIT_JPG | IMG_INIT_PNG;
            int initted = IMG_Init(flags);
            if ((initted & flags) != flags) {
                std::cerr << "Failed to init SDL_image: " << IMG_GetError() << std::endl;
                exit(1);
            }

            flags = MIX_INIT_OGG | MIX_INIT_MP3;
            initted = Mix_Init(flags);
            if ((initted & flags) != flags) {
                std::cerr << "Failed to init SDL_mixer: " << Mix_GetError() << std::endl;
                exit(1);
            }

            if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0) {
                std::cerr << "Error by Mix_OpenAudio: " << Mix_GetError() << std::endl;
                exit(1);
            }

            const int channels = Mix_AllocateChannels(256);
            if (channels < 256)
                std::cerr << "Could not reserve 256 channels, only " << channels << " " << Mix_GetError() << std::endl;

            if (TTF_Init() != 0) {
                std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
                exit(1);
            }
        }
    }

    void quitSDL(int count) {
        if (count <= 0) {
            TTF_Quit();
            Mix_ReserveChannels(0);
            Mix_CloseAudio();
            Mix_Quit();
            IMG_Quit();
            SDL_Quit();
        }
    }

    void initGL() {
        glCheck(glDisable(GL_DITHER));
        glCheck(glDisable(GL_LIGHTING));
        glCheck(glDisable(GL_DEPTH_TEST));
        glCheck(glDisable(GL_ALPHA_TEST));

        glCheck(glEnable(GL_CULL_FACE));
        glCheck(glEnable(GL_TEXTURE_2D));
        glCheck(glEnable(GL_BLEND));
        glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        glCheck(glCullFace(GL_FRONT));
        glCheck(glShadeModel(GL_FLAT));
        glCheck(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

        glCheck(glEnableClientState(GL_VERTEX_ARRAY));
        glCheck(glEnableClientState(GL_COLOR_ARRAY));
        glCheck(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
        // Hints
        glCheck(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST));

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        const GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Couldn't initialize GLEW: " << glewGetErrorString(err) << std::endl;
            exit(1);
        }
    }
}
