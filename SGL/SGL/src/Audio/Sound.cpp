#include <Audio\Sound.hpp>

namespace sgl {
	uint16 Sound::ChannelCount = 0;

	Sound::Sound(const std::string& filename, int8 volume) : _chunk(nullptr), channel(Sound::ChannelCount++) {
		loadFromFile(filename);
		if (volume > 0)
			setVolume(volume);
	}

	void Sound::loadFromFile(const std::string& filename) {
		_chunk = Mix_LoadWAV(filename.c_str());

		if (!_chunk) {
			printf("Copuld not load Wave File %s: %s\n", filename.c_str(), Mix_GetError());
			exit(1);
		}
	}

	void Sound::play(int8 loops, int16 delay) const {
		loops = loops > 0 ? loops - 1 : loops;

		if (Mix_PlayChannelTimed(this->channel, _chunk, loops, delay) == -1) {
			printf("Could not play Sound: %s\n", Mix_GetError());
			exit(1);
		}
	}

	uint16 Sound::CountPlaying() {
		return Mix_Playing(-1);
	}

	uint16 Sound::CountPaused() {
		return Mix_Paused(-1);
	}
}