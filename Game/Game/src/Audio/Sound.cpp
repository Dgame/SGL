#include <Audio\Sound.h>

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
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
			throw "Copuld not load Wave File";
		}
	}

	void Sound::play(int8 loops, int16 delay) const {
		loops = loops > 0 ? loops - 1 : loops;

		if (Mix_PlayChannelTimed(this->channel, _chunk, loops, delay) == -1) {
			printf("Mix_PlayChannel: %s\n", Mix_GetError());

			throw "Could not play Sound";
		}
	}

	uint16 Sound::CountPlaying() {
		return Mix_Playing(-1);
	}

	uint16 Sound::CountPaused() {
		return Mix_Paused(-1);
	}
}