#ifndef SGL_SDL_MIXER_HPP
#define SGL_SDL_MIXER_HPP

#include <SGL/Core/Config.hpp>

#if defined(SGL_OS_WIN64) && SGL_USE_X64
    #include "../libs/64/SDL2/SDL_mixer.h"
#else
    #include "../libs/32/SDL2/SDL_mixer.h"
#endif

#endif
