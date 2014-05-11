#include <SGL/Graphic/Color.hpp>

namespace sgl {
	Array<uint16, 4> convertFromHex(const std::string& hex) {
		uint8 offset = 0;
		if (hex[0] == '#')
			offset = 1;
		else if (hex[0] == '0' && hex[1] == 'x')
			offset = 2;

		const uint32 len = hex.size() - offset;

		Array<char, 3> rc;
		Array<char, 3> gc;
		Array<char, 3> bc;
		Array<char, 3> ac;

		if (len == 3) {
			rc = {hex[offset], hex[offset], '\0'};
			gc = {hex[offset + 1], hex[offset + 1], '\0'};
			bc = {hex[offset + 2], hex[offset + 2], '\0'};
		} else if (len == 6) {
			rc = {hex[offset], hex[offset + 1], '\0'};
			gc = {hex[offset + 2], hex[offset + 3], '\0'};
			bc = {hex[offset + 4], hex[offset + 5], '\0'};
		} else if (len == 8) {
			rc = {hex[offset], hex[offset + 1], '\0'};
			gc = {hex[offset + 2], hex[offset + 3], '\0'};
			bc = {hex[offset + 4], hex[offset + 5], '\0'};
			ac = {hex[offset + 6], hex[offset + 7], '\0'};
		} else {
			rc = {0, 0, '\0'};
			gc = {0, 0, '\0'};
			bc = {0, 0, '\0'};
		}

		std::stringstream ss;
		Array<uint16, 4> rgba;

		ss << std::hex << rc.data;
		ss >> rgba.data[0];
		ss.clear();
		ss << std::hex << gc.data;
		ss >> rgba.data[1];
		ss.clear();
		ss << std::hex << bc.data;
		ss >> rgba.data[2];

		if (len == 8) {
			ss.clear();
			ss << std::hex << ac.data;
			ss >> rgba.data[3];
		} else {
			rgba.data[3] = 255;
		}

		return std::move(rgba);
	}

	GLColor::GLColor(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) {

	}

	const Color Color::Black(0, 0, 0);
	const Color Color::White(255, 255, 255);
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Yellow(255, 255, 0);

	Color::Color(uint8 pr, uint8 pg, uint8 pb, uint8 pa) : red(pr), green(pg), blue(pb), alpha(pa) {

	}

	Color::Color(const std::string& hex) {
		const Array<uint16, 4> rgba = convertFromHex(hex);

		this->red = rgba.at(0) % 256;
		this->green = rgba.at(1) % 256;
		this->blue = rgba.at(2) % 256;
		this->alpha = rgba.at(3) % 256;
	}

	Color Color::FromGLMode(const GLColor& gl_col) {
		return Color::FromGLMode(gl_col.red, gl_col.green, gl_col.blue, gl_col.alpha);
	}

	Color Color::FromGLMode(float pr, float pg, float pb, float pa) {
		const float r = static_cast<uint8>(pr > 1.f ? pr : pr * 255);
		const float g = static_cast<uint8>(pg > 1.f ? pg : pg * 255);
		const float b = static_cast<uint8>(pb > 1.f ? pb : pb * 255);
		const float a = static_cast<uint8>(pa > 1.f ? pa : pa * 255);

		return Color(r, g, b, a);
	}

	GLColor Color::InGLMode(const Color& col) {
		const float r = col.red / 255.f;
		const float g = col.green / 255.f;
		const float b = col.blue / 255.;
		const float a = col.alpha / 255.f;

		return GLColor(r, g, b, a);
	}

	void Color::Copy(const Color* from, SDL_Color& too, const Color& def) {
		if (from == nullptr) {
			too.r = def.red;
			too.g = def.green;
			too.b = def.blue;
			too.a = def.alpha;
		} else {
			too.r = from->red;
			too.g = from->green;
			too.b = from->blue;
			too.a = from->alpha;
		}
	}

	void operator +=(Color& lhs, uint8 value) {
		lhs.red += value;
		lhs.green += value;
		lhs.blue += value;
		lhs.alpha += value;
	}

	void operator -=(Color& lhs, uint8 value) {
		lhs.red -= value;
		lhs.green -= value;
		lhs.blue -= value;
		lhs.alpha -= value;
	}

	void operator *=(Color& lhs, uint8 value) {
		lhs.red *= value;
		lhs.green *= value;
		lhs.blue *= value;
		lhs.alpha *= value;
	}

	Color operator +(const Color& lhs, const Color& rhs) {
		return Color(std::min(lhs.red + rhs.red, 255),
					 std::min(lhs.green + rhs.green, 255),
					 std::min(lhs.blue + rhs.blue, 255),
					 std::min(lhs.alpha + rhs.alpha, 255));
	}

	Color operator -(const Color& lhs, const Color& rhs) {
		return Color(std::min(lhs.red - rhs.red, 0),
					 std::min(lhs.green - rhs.green, 0),
					 std::min(lhs.blue - rhs.blue, 0),
					 std::min(lhs.alpha - rhs.alpha, 0));
	}

	Color operator *(const Color& lhs, const Color& rhs) {
		return Color((lhs.red * rhs.red) / 255,
					 (lhs.green * rhs.green) / 255,
					 (lhs.blue * rhs.blue) / 255,
					 (lhs.alpha * rhs.alpha) / 255);
	}

	bool operator ==(const Color& lhs, const Color& rhs) {
		return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha;
	}

	bool operator !=(const Color& lhs, const Color& rhs) {
		return !(lhs == rhs);
	}

	std::ostream& operator <<(std::ostream& strm, const Color& col) {
		return strm << "Color("
			<< static_cast<int16>(col.red)
			<< ',' << static_cast<int16>(col.green)
			<< ',' << static_cast<int16>(col.blue)
			<< ',' << static_cast<int16>(col.alpha) << ")";
	}
}