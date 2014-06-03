#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>
#include <SDL_mixer.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Output.hpp>

namespace sgl {
	class Sound {
	private:
		Mix_Chunk* _chunk = nullptr;
		uint16 _channel = 0;

		static uint16 ChannelCount;

	public:
		explicit Sound(const std::string& filename, int8 volume = -1);

		virtual ~Sound() {
			Mix_FreeChunk(_chunk);
		}

		uint16 channel() const {
			return _channel;
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
			Mix_Resume(_channel);
		}

		void stop() const {
			Mix_HaltChannel(_channel);
		}

		void pause() const {
			Mix_Pause(_channel);
		}

		bool isPlaying() const {
			return Mix_Playing(_channel) != 0;
		}

		bool isPaused() const {
			return Mix_Paused(_channel) == 0;
		}

		static uint16 CountPlaying();
		static uint16 CountPaused();
	};
}

#endif