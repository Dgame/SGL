#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>
#include <SDL_mixer.h>
#include <SGL/Core/Types.hpp>

namespace sgl {
	class Sound {
	private:
		Mix_Chunk* _chunk = nullptr;

		static uint16 ChannelCount;

	public:
		const uint16 channel;

		explicit Sound(const std::string& filename, int8 volume = -1);

		virtual ~Sound() {
			Mix_FreeChunk(_chunk);
		}

		virtual void loadFromFile(const std::string& filename);

		void setVolume(int8 volume) const {
			Mix_VolumeChunk(_chunk, volume);
		}

		int8 getVolume() const {
			return Mix_VolumeChunk(_chunk, -1);
		}

		void play(int8 loops = 1, int16 delay = -1) const;

		void resume() const {
			Mix_Resume(this->channel);
		}

		void stop() const {
			Mix_HaltChannel(this->channel);
		}

		void pause() const {
			Mix_Pause(this->channel);
		}

		bool isPlaying() const {
			return Mix_Playing(this->channel) != 0;
		}

		bool isPaused() const {
			return Mix_Paused(this->channel) == 0;
		}

		static uint16 CountPlaying();
		static uint16 CountPaused();
	};
}

#endif