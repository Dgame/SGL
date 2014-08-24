#ifndef SGL_BATTERY_HPP
#define SGL_BATTERY_HPP

#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Types.hpp>

namespace sgl {
	struct Battery {
		enum State {
			Unknown = SDL_POWERSTATE_UNKNOWN,    /** Cannot determine power status */
			OnBattery = SDL_POWERSTATE_ON_BATTERY, /** Not plugged in, running on the battery */
			NoBattery = SDL_POWERSTATE_NO_BATTERY, /** plugged in, no battery available */
			Charging = SDL_POWERSTATE_CHARGING,   /** plugged in, charging battery */
			Charged = SDL_POWERSTATE_CHARGED,    /** plugged in, battery charged **/
		};

		int32 seconds;
		int8 percent;
		State state;
	};

	Battery RemainingBattery();
}

#endif