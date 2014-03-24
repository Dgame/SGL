#include <Graphic/Color.h>

const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Transparent(0, 0, 0, 0);

Color::Color(uint8 pr, uint8 pg, uint8 pb, uint8 pa) : r(pr), g(pg), b(pb), alpha(pa) {

}

Color Color::GL(float pr, float pg, float pb, float pa) {
	Color result = Color::White;
	result.r = static_cast<uint8>(pr > 1.f ? pr : pr * 255);
	result.g = static_cast<uint8>(pg > 1.f ? pg : pg * 255);
	result.b = static_cast<uint8>(pb > 1.f ? pb : pb * 255);
	result.alpha = static_cast<uint8>(pa > 1.f ? pa : pa * 255);

	return result;
}

bool operator ==(const Color& lhs, const Color& rhs) {
	return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.alpha == rhs.alpha;
}

bool operator !=(const Color& lhs, const Color& rhs) {
	return !(lhs == rhs);
}