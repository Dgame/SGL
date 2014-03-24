#ifndef COLOR_HPP
#define COLOR_HPP

#include <array>
#include <Core/Types.h>

struct Color {
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Transparent;

	uint8 r, g, b, alpha;

	explicit Color(uint8 pr, uint8 pg, uint8 pb, uint8 pa = 255);

	Color withTransparency(uint8 pa) const {
		return Color(r, g, b, pa);
	}

	static Color GL(float pr, float pg, float pb, float pa = 1.f);
};

bool operator ==(const Color& lhs, const Color& rhs);
bool operator !=(const Color& lhs, const Color& rhs);

#endif