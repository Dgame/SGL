#ifndef COLOR_HPP
#define COLOR_HPP

#include <sstream>
#include <SDL.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Array.hpp>

namespace sgl {
	static Array<uint16, 4> convertFromHex(const std::string& hex);

	struct GLColor {
		float red, green, blue, alpha;

		explicit GLColor(float r, float g, float b, float a = 1.f);
	};

	struct Color {
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;

		uint8 red, green, blue, alpha;

		explicit Color(uint8 pr, uint8 pg, uint8 pb, uint8 pa = 255);
		explicit Color(const std::string& hex);

		Color withTransparency(uint8 pa) const {
			return Color(red, green, blue, pa);
		}

		static Color FromGLMode(float pr, float pg, float pb, float pa = 1.f);
		static Color FromGLMode(const GLColor& glcol);
		static GLColor InGLMode(const Color& col);
		static void Copy(const Color* from, SDL_Color& too, const Color& def);
	};

	void operator +=(Color& lhs, uint8 value);
	void operator -=(Color& lhs, uint8 value);
	void operator *=(Color& lhs, uint8 value);

	Color operator +(const Color& lhs, const Color& rhs);
	Color operator -(const Color& lhs, const Color& rhs);
	Color operator *(const Color& lhs, const Color& rhs);

	bool operator ==(const Color& lhs, const Color& rhs);
	bool operator !=(const Color& lhs, const Color& rhs);

	std::ostream& operator <<(std::ostream& strm, const Color& col);
}

#endif