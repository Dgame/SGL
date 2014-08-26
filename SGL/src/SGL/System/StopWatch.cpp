#include <SGL/System/StopWatch.hpp>
#include <cmath>

namespace sgl {
	Time::Time(uint32 ms) {
		this->seconds = ms / 1000;
		while (this->seconds >= 60) {
			this->seconds -= 60;
			this->minutes++;
		}

		while (this->minutes >= 60) {
			this->minutes -= 60;
			this->hours++;
		}
		
		this->msecs = static_cast<uint16>(fmod(ms, 1000));
	}

	StopWatch::StopWatch() {
		this->reset();
	}

	void StopWatch::reset() {
		_startTime = DurationMs();
	}

	Time StopWatch::getElapsedTime() const {
		return Time(this->getElapsedMs());
	}

	uint32 StopWatch::getElapsedMs() const {
		return DurationMs() - _startTime;
	}

	/**
	* Returns the current framerate per seconds.
	*/
	uint32 StopWatch::getFPS(uint32* elapsedMs) {
		const uint32 elapsed_ms = this->getElapsedMs();
		if (elapsedMs)
			*elapsedMs = elapsed_ms;

		if (elapsed_ms >= 1000) {
			_currentFps = _numFrames;
			_numFrames = 0;

			this->reset();
		}

		_numFrames++;

		return _currentFps;
	}

	/**
	* Returns the milliseconds since the application was started.
	*/
	uint32 DurationMs() {
		return SDL_GetTicks();
	}

	/**
	* Returns the Time since the application was started.
	*/
	Time DurationTime() {
		return Time(DurationMs());
	}

	/**
	* Wait for msecs milliseconds, which means that the application freeze for this time.
	*/
	void WaitFor(uint32 msecs) {
		SDL_Delay(msecs);
	}
}