#ifndef SGL_STOPWATCH_HPP
#define SGL_STOPWATCH_HPP

#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Types.hpp>

namespace sgl {
	struct Time {
		uint16 seconds;
		uint16 minutes;
		uint16 msecs;
		uint16 hours;

		explicit Time(uint32 ms);
	};

	class StopWatch {
	private:
		uint32 _startTime = 0;
		uint32 _numFrames = 0;
		uint32 _currentFps = 0;
		float _fpsTime = 0;

	public:
		StopWatch();
		/**
		* Reset the StopWatch time
		*/
		void reset();
		/**
		* Returns the elapsed Time since the last reset.
		*/
		Time getElapsedTime() const;
		/**
		* Returns the milliseconds since the last reset.
		*/
		uint32 getElapsedMs() const;
		/**
		* Returns the current framerate per second.
		*/
		uint32 getFPS(uint32* elapsedMs = nullptr);
	};

	/**
	* Returns the milliseconds since the application was started.
	*/
	uint32 DurationMs();
	/**
	* Returns the Time since the application was started.
	*/
	Time DurationTime();
	/**
	* Wait for msecs milliseconds, which means that the application freeze for this time.
	*/
	void WaitFor(uint32 msecs);
}

#endif