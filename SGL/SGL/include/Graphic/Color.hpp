#ifndef COLOR_HPP
#define COLOR_HPP

#include <array>
#include <SDL.h>
#include <Core/Types.hpp>

namespace sgl {
	struct Color {
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;

		uint8 red, green, blue, alpha;

		explicit Color(uint8 pr, uint8 pg, uint8 pb, uint8 pa = 255);

		Color withTransparency(uint8 pa) const {
			return Color(red, green, blue, pa);
		}

		static Color GL(float pr, float pg, float pb, float pa = 1.f);
		static void Copy(const Color* from, SDL_Color& too, const Color& def);
	};

	bool operator ==(const Color& lhs, const Color& rhs);
	bool operator !=(const Color& lhs, const Color& rhs);

}

#endif