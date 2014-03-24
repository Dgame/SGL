#pragma once

#include <math.h>
#include <SDL.h>
#include <Core\Types.h>

/**
* To convert the Clock milliseconds to seconds
*/
float asSeconds(uint32 n);

/**
* To convert the Clock milliseconds to minutes
*/
float asMinutes(uint32 n);

/**
* To convert the Clock milliseconds to hours
*/
uint16 asHours(uint32 n);

/**
* The Time struct converts ticks to msecs, seconds, minutes and hours.
*/
struct Time {
	/// Milliseconds = Ticks
	uint32 msecs;
	/// Seconds = Milliseconds / 1000
	float seconds;
	//// Minutes = Seconds / 60
	float minutes;
	/// Hours = Minutes / 60
	uint16 hours;

	/**
	* CTor
	*/
	explicit Time(uint32 ms);

	/**
	* Calculate the <b>remaining</b> time.
	*/
	static Time Remain(Time time);
};

class Clock {
private:
	uint32 _startTime;
	uint32 _numFrames;
	uint32 _currentFps;
	float _fpsTime;

public:
	explicit Clock();

	/**
	* Reset the clock time
	*/
	void reset() {
		_startTime = SDL_GetTicks();
	}

	/**
	* Returns the elapsed Time since the last reset.
	*/
	Time getElapsedTime() const {
		return Time(getElapsedTicks());
	}

	/**
	* Returns only the milliseconds since the last reset.
	*/
	uint32 getElapsedTicks() const {
		return SDL_GetTicks() - _startTime;
	}

	/**
	* Returns the current framerate per seconds.
	*/
	uint32 getCurrentFps();

	/**
	* Returns the Time since the last Frame.
	*/
	float getFpsTime() const {
		return _fpsTime;
	}

	/**
	* Returns the milliseconds since the application was started.
	*/
	static uint32 GetTicks();

	/**
	* Returns the Time since the application was started.
	*/
	static Time GetTime();

	/**
	* Wait for msecs milliseconds, which means that the application freeze for this time.
	*/
	static void Wait(uint32 msecs);
};