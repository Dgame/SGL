#ifndef SGL_SOUND_HPP
#define SGL_SOUND_HPP

#include <string>
#include <SDL_mixer.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Check.hpp>

namespace sgl {
	class Sound {
	private:
		Mix_Chunk* _chunk;
		uint16 _channel;

		static uint16 ChannelCount;

	public:
		explicit Sound(const std::string&, int8 volume = -1);
		Sound(const Sound&) = delete;
		virtual ~Sound();

		uint16 getChannel() const {
			return _channel;
		}

		bool loadFromFile(const std::string&);
		void setVolume(int8 volume) const;
		int8 getVolume() const;

		void play(int16 loops = 1, int16 delay = -1) const;
		void resume() const;
		void stop() const;
		void pause() const;
		bool isPlaying() const;
		bool isPaused() const;
	};
}

#endif