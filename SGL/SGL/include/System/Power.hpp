#ifndef POWER_HPP
#define POWER_HPP

#include <SDL.h>
#include <Core\Types.hpp>

namespace sgl {
	struct Power {
		/**
		* Power states
		*/
		enum class State {
			Unknown = SDL_POWERSTATE_UNKNOWN,    /** Cannot determine power status */
			OnBattery = SDL_POWERSTATE_ON_BATTERY, /** Not plugged in, running on the battery */
			NoBattery = SDL_POWERSTATE_NO_BATTERY, /** plugged in, no battery available */
			Charging = SDL_POWERSTATE_CHARGING,   /** plugged in, charging battery */
			Charged = SDL_POWERSTATE_CHARGED,    /** plugged in, battery charged **/
		};

		/**
		* Remaining time in seconds, or -1 if cannot determine power status
		*/
		uint32 seconds;
		/**
		* Remaining battery percent, or -1 if cannot determine power status
		*/
		uint8 percent;
		/**
		* Battery state
		*/
		State state;

		explicit Power(uint32 sec, uint8 perc, State _state);

		/**
		 * Returns the PowerInfo structure with the currently power informations
		 *
		 * See: PowerInfo struct
		 */
		static Power Info();
	};
}

#endif