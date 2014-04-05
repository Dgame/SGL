#include <System\Keyboard.hpp>

namespace sgl {
	const uint8* Keyboard::GetState() {
		return SDL_GetKeyboardState(nullptr);
	}

	bool Keyboard::IsPressed(Code code) {
		SDL_Scancode scancode = SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(code));
		const uint8* keys = GetState();

		return keys[scancode] == 1;
	}

	Keyboard::Mod Keyboard::GetModifier() {
		return static_cast<Mod>(SDL_GetModState());
	}

	void Keyboard::SetModifier(Mod mod) {
		SDL_SetModState(static_cast<SDL_Keymod>(mod));
	}

	bool Keyboard::HasScreenSupport() {
		return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
	}
}