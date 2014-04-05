#include <System\Clock.hpp>

namespace sgl {
	/**
	* To convert the Clock milliseconds to seconds
	*/
	float asSeconds(uint32 n) {
		return n >= 1000 ? (n / 1000.f) : 0.f;
	}

	/**
	* To convert the Clock milliseconds to minutes
	*/
	float asMinutes(uint32 n) {
		const float secs = asSeconds(n);

		return secs >= 60 ? (secs / 60) : 0;
	}

	/**
	* To convert the Clock milliseconds to hours
	*/
	uint16 asHours(uint32 n) {
		const float mins = asMinutes(n);

		return mins >= 60 ? static_cast<uint16>(mins / 60.f) : 0;
	}

	/**
	* CTor
	*/
	Time::Time(uint32 ms) : msecs(ms) {
		seconds = asSeconds(msecs);
		minutes = asMinutes(msecs);
		hours = asHours(msecs);
	}

	/**
	* Calculate the <b>remaining</b> time.
	*/
	Time Time::Remain(Time time) {
		const float min = time.minutes;
		const float sec = time.seconds;

		time.minutes -= time.hours * 60;
		time.minutes = floor(time.minutes);
		time.seconds -= floor(min) * 60;
		time.msecs -= static_cast<uint32>(floor(sec) * 1000);

		return time;
	}

	Clock::Clock() : _startTime(0), _numFrames(0), _currentFps(0), _fpsTime(0) {
		reset();
	}

	/**
	* Returns the current framerate per seconds.
	*/
	uint32 Clock::getCurrentFps() {
		const uint32 elapsed_ticks = getElapsedTicks();

		if (elapsed_ticks >= 1000) {
			_currentFps = _numFrames;
			_fpsTime = (0.f + elapsed_ticks) / _numFrames;

			_numFrames = 0;
			reset();
		}

		_numFrames++;

		return _currentFps;
	}

	/**
	* Returns the milliseconds since the application was started.
	*/
	uint32 Clock::GetTicks() {
		return SDL_GetTicks();
	}

	/**
	* Returns the Time since the application was started.
	*/
	Time Clock::GetTime() {
		return Time(Clock::GetTicks());
	}

	/**
	* Wait for msecs milliseconds, which means that the application freeze for this time.
	*/
	void Clock::Wait(uint32 msecs) {
		SDL_Delay(msecs);
	}
}