#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include <stdio.h>
#include <SDL_mixer.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Math/Vector2.hpp>

namespace sgl {
	class Music {
	public:
		enum class Type {
			None = MUS_NONE,
			Cmd = MUS_CMD,
			Wave = MUS_WAV,
			Mod = MUS_MOD,
			Midi = MUS_MID,
			Ogg = MUS_OGG,
			Mp3 = MUS_MP3
		};

		enum class Fading {
			No = MIX_NO_FADING,
			Out = MIX_FADING_OUT,
			In = MIX_FADING_IN
		};

	private:
		Mix_Music* _music = nullptr;

	public:
		explicit Music(const std::string& filename, int8 volume = -1);

		virtual ~Music() {
			Mix_FreeMusic(_music);
		}

		void loadFromFile(const std::string& filename);

		void setVolume(int8 volume) const {
			Mix_VolumeMusic(volume);
		}

		int8 getVolume() const {
			Mix_VolumeMusic(-1);
		}

		void play(int8 loops = 1, int16 delay = -1) const;

		void pause() const {
			Mix_PauseMusic();
		}

		void resume() const {
			Mix_ResumeMusic();
		}

		void stop() const {
			Mix_HaltMusic();
		}

		void rewind() const {
			Mix_RewindMusic();
		}

		void setPosition(float seconds) const {
			Mix_SetMusicPosition(seconds);
		}

		Type getType() const;

		bool isPlaying() const {
			return Mix_PlayingMusic() != 0;
		}

		bool isPaused() const {
			return Mix_PausedMusic() != 0;
		}

		Fading isFading() const;
	};
}

#endif