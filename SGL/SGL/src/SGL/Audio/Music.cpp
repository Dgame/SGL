#include <SGL/Audio/Music.hpp>

namespace sgl {
	Music::Music(const std::string& filename, int8 volume) {
		loadFromFile(filename);
		setVolume(volume);
	}

	void Music::loadFromFile(const std::string& filename) {
		_music = Mix_LoadMUS(filename.c_str());

		if (!_music) {
			printf("Unable to load Music %s: %s\n", filename.c_str(), Mix_GetError());
			exit(1);
		}
	}

	void Music::play(int8 loops, int16 delay) const {
		loops = loops > 0 ? loops - 1 : loops;
		Mix_FadeInMusic(_music, loops, delay);
	}

	Music::Type Music::getType() const {
		Mix_MusicType mt = Mix_GetMusicType(_music);

		return static_cast<Type>(mt);
	}

	Music::Fading Music::isFading() const {
		Mix_Fading mf = Mix_FadingMusic();

		return static_cast<Fading>(mf);
	}
}