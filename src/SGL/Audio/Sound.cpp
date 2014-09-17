#include <SGL/Audio/Sound.hpp>

namespace sgl {
	uint16 Sound::ChannelCount = 0;

	Sound::Sound(const std::string& filename, int8 volume) : _channel(Sound::ChannelCount++) {
		this->loadFromFile(filename);
		this->setVolume(volume);
	}

	Sound::~Sound() {
		Mix_FreeChunk(_chunk);
	}

	bool Sound::loadFromFile(const std::string& filename) {
		_chunk = Mix_LoadWAV(filename.c_str());
		if (!_chunk) {
			std::cerr << Mix_GetError() << std::endl;
			return false;
		}

		return true;
	}

	void Sound::setVolume(int8 volume) const {
	    if (_chunk)
		    Mix_VolumeChunk(_chunk, volume);
	}

	int8 Sound::getVolume() const {
	    if (_chunk)
		    return Mix_VolumeChunk(_chunk, -1);
        return 0;
	}

	void Sound::play(int16 loops, int16 delay) const {
	    if (_chunk) {
            loops = loops > 0 ? loops - 1 : loops;
            SDL_Check(Mix_PlayChannelTimed(_channel, _chunk, loops, delay));
	    }
	}

	void Sound::resume() const {
		Mix_Resume(_channel);
	}

	void Sound::stop() const {
		Mix_HaltChannel(_channel);
	}

	void Sound::pause() const {
		Mix_Pause(_channel);
	}

	void Sound::expire(uint16 ticks) {
	    Mix_ExpireChannel(_channel, ticks);
	}

	bool Sound::isPlaying() const {
		return Mix_Playing(_channel) != 0;
	}

	bool Sound::isPaused() const {
		return Mix_Paused(_channel) == 0;
	}
}
