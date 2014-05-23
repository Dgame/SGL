#include <SGL/Audio/Sound.hpp>

namespace sgl {
	uint16 Sound::ChannelCount = 0;

	Sound::Sound(const std::string& filename, int8 volume) : _channel(Sound::ChannelCount++) {
		this->loadFromFile(filename);
		if (volume > 0)
			this->setVolume(volume);
	}

	void Sound::loadFromFile(const std::string& filename) {
		_chunk = Mix_LoadWAV(filename.c_str());
		if (_chunk == nullptr)
			error("Could not load Wave File ", filename.c_str(), ':', Mix_GetError());
	}

	void Sound::play(int8 loops, int16 delay) const {
		loops = loops > 0 ? loops - 1 : loops;

		if (Mix_PlayChannelTimed(_channel, _chunk, loops, delay) == -1) {
			error("Could not play Sound: ", Mix_GetError());
		}
	}

	uint16 Sound::CountPlaying() {
		return Mix_Playing(-1);
	}

	uint16 Sound::CountPaused() {
		return Mix_Paused(-1);
	}
}