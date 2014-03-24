#include <System\Keyboard.h>

namespace Keyboard {
	const uint8* GetState() {
		return SDL_GetKeyboardState(nullptr);
	}

	bool IsPressed(Code code) {
		SDL_Scancode scancode = SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(code));
		const uint8* keys = GetState();

		return keys[scancode] == 1;
	}

	Mod GetModifier() {
		return static_cast<Mod>(SDL_GetModState());
	}

	void SetModifier(Mod mod) {
		SDL_SetModState(static_cast<SDL_Keymod>(mod));
	}

	bool HasScreenSupport() {
		return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
	}
}