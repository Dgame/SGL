#include <System\Power.hpp>

namespace sgl {
	Power::Power(uint32 sec, uint8 perc, State _state) : seconds(sec), percent(perc), state(_state) {

	}

	/**
	* Returns the PowerInfo structure with the currently power informations
	*
	* See: PowerInfo struct
	*/
	Power Power::Info() {
		int secs, pct;
		SDL_PowerState state = SDL_GetPowerInfo(&secs, &pct);

		return Power(secs, pct, static_cast<State>(state));
	}
}