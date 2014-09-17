#ifndef SGL_MUSIC_HPP
#define SGL_MUSIC_HPP

#include <string>
#include <SDL_mixer.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Check.hpp>

namespace sgl {
	class Music {
	private:
		Mix_Music* _music;

	public:
		explicit Music(const std::string&, int8 volume = -1);
		Music(const Music&) = delete;
		virtual ~Music();

		bool loadFromFile(const std::string&);

		void setVolume(int8 volume) const;
		int8 getVolume() const;

		void play(int8 loops = 1, int16 delay = -1) const;

		void pause() const;
		void resume() const;
		void stop() const;
		void rewind() const;
		void setPosition(float seconds) const;

		bool isPlaying() const;
		bool isPaused() const;
	};
}

#endif
