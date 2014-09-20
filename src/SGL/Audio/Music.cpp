#include <SGL/Audio/Music.hpp>

namespace sgl {
    Music::Music(const std::string& filename, int8 volume) {
        this->loadFromFile(filename);
        this->setVolume(volume);
    }

    Music::~Music() {
        Mix_FreeMusic(_music);
    }

    bool Music::loadFromFile(const std::string& filename) {
        _music = Mix_LoadMUS(filename.c_str());
        if (!_music) {
            std::cerr << Mix_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void Music::setVolume(int8 volume) const {
        Mix_VolumeMusic(volume);
    }

    int8 Music::getVolume() const {
        return Mix_VolumeMusic(-1);
    }

    void Music::play(int8 loops, int16 delay) const {
        if (_music) {
            loops = loops > 0 ? loops - 1 : loops;
            SDL_Check(Mix_FadeInMusic(_music, loops, delay));
        }
    }

    void Music::pause() const {
        Mix_PauseMusic();
    }

    void Music::resume() const {
        Mix_ResumeMusic();
    }

    void Music::stop() const {
        Mix_HaltMusic();
    }

    void Music::rewind() const {
        Mix_RewindMusic();
    }

    void Music::setPosition(float seconds) const {
        SDL_Check(Mix_SetMusicPosition(seconds));
    }

    bool Music::isPlaying() const {
        return Mix_PlayingMusic() != 0;
    }

    bool Music::isPaused() const {
        return Mix_PausedMusic() != 0;
    }
}
