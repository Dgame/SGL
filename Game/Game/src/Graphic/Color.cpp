#include <Graphic/Color.h>

namespace sgl {
	const Color Color::Black(0, 0, 0);
	const Color Color::White(255, 255, 255);
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Yellow(255, 255, 0);

	Color::Color(uint8 pr, uint8 pg, uint8 pb, uint8 pa) : red(pr), green(pg), blue(pb), alpha(pa) {

	}

	Color Color::GL(float pr, float pg, float pb, float pa) {
		Color result = Color::White;
		result.red = static_cast<uint8>(pr > 1.f ? pr : pr * 255);
		result.green = static_cast<uint8>(pg > 1.f ? pg : pg * 255);
		result.blue = static_cast<uint8>(pb > 1.f ? pb : pb * 255);
		result.alpha = static_cast<uint8>(pa > 1.f ? pa : pa * 255);

		return result;
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

	bool operator ==(const Color& lhs, const Color& rhs) {
		return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha;
	}

	bool operator !=(const Color& lhs, const Color& rhs) {
		return !(lhs == rhs);
	}
}