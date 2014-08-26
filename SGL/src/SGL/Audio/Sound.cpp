#include <SGL/Audio/Sound.hpp>

namespace sgl {
	uint16 Sound::ChannelCount = 0;

	Sound::Sound(const std::string& filename, int8 volume) : _channel(Sound::ChannelCount++) {
		this->loadFromFile(filename);
		if (volume != -1)
			this->setVolume(volume);
	}

	Sound::~Sound() {
		if (_chunk)
			Mix_FreeChunk(_chunk);
	}

	void Sound::loadFromFile(const std::string& filename) {
		_chunk = Mix_LoadWAV(filename.c_str());
		if (!_chunk)
			std::cerr << Mix_GetError() << std::endl;
	}

	void Sound::setVolume(int8 volume) const {
		Mix_VolumeChunk(_chunk, volume);
	}

	int8 Sound::getVolume() const {
		return Mix_VolumeChunk(_chunk, -1);
	}

	void Sound::play(int8 loops, int16 delay) const {
		loops = loops > 0 ? loops - 1 : loops;
		SDL_Check(Mix_PlayChannelTimed(_channel, _chunk, loops, delay));
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

	bool Sound::isPlaying() const {
		return Mix_Playing(_channel) != 0;
	}

	bool Sound::isPaused() const {
		return Mix_Paused(_channel) == 0;
	}
}