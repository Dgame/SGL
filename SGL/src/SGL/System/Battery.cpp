#include <SGL/System/Battery.hpp>

namespace sgl {
	Battery RemainingBattery() {
		int32 secs, pct;
		SDL_PowerState state = SDL_GetPowerInfo(&secs, &pct);

		return Battery{secs, pct, static_cast<Battery::State>(state)};
	}
}