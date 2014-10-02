#include <algorithm>
#include <SGL/Core/SDL.hpp>
#include <SGL/Graphic/Color.hpp>

namespace sgl {
    const Color4b Color4b::Red(255, 0, 0);
    const Color4b Color4b::Green(0, 255, 0);
    const Color4b Color4b::Blue(0, 0, 255);
    const Color4b Color4b::Yellow(0, 255, 255);
    const Color4b Color4b::Black(0, 0, 0);
    const Color4b Color4b::White(255, 255, 255);

    const Color4f Color4f::Red(Color4b::Red);
    const Color4f Color4f::Green(Color4b::Green);
    const Color4f Color4f::Blue(Color4b::Blue);
    const Color4f Color4f::Yellow(Color4b::Yellow);
    const Color4f Color4f::Black(Color4b::Black);
    const Color4f Color4f::White(Color4b::White);

    Color4b::Color4(uint8 r, uint8 g, uint8 b, uint8 a) : red(r), green(g), blue(b), alpha(a) {

    }

    Color4b::Color4(const Color4<float>& col) {
        this->red = static_cast<uint8>(col.red * 255);
        this->green = static_cast<uint8>(col.green * 255);
        this->blue = static_cast<uint8>(col.blue * 255);
        this->alpha = static_cast<uint8>(col.alpha * 255);
    }

    SDL_Color* Copy(const Color4b& src, SDL_Color* dst) {
        if (dst) {
            dst->r = src.red;
            dst->g = src.green;
            dst->b = src.blue;
            dst->a = src.alpha;
        }

        return dst;
    }

    Color4<float>::Color4(uint8 r, uint8 g, uint8 b, uint8 a) : red(r / 255.f), green(g / 255.f), blue(b / 255.f), alpha(a / 255.f) {

    }

    Color4<float>::Color4(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) {

    }

    Color4<float>::Color4(const Color4b& col) : Color4(col.red, col.green, col.blue, col.alpha) {

    }

    Color4b& operator +=(Color4b& lhs, uint8 value) {
        lhs.red += value;
        lhs.green += value;
        lhs.blue += value;
        lhs.alpha += value;

        return lhs;
    }

    Color4b& operator -=(Color4b& lhs, uint8 value) {
        lhs.red -= value;
        lhs.green -= value;
        lhs.blue -= value;
        lhs.alpha -= value;

        return lhs;
    }

    Color4b& operator *=(Color4b& lhs, uint8 value) {
        lhs.red *= value;
        lhs.green *= value;
        lhs.blue *= value;
        lhs.alpha *= value;

        return lhs;
    }

    Color4b operator +(const Color4b& lhs, const Color4b& rhs) {
        return Color4b(std::min(lhs.red + rhs.red, 255),
                     std::min(lhs.green + rhs.green, 255),
                     std::min(lhs.blue + rhs.blue, 255),
                     std::min(lhs.alpha + rhs.alpha, 255));
    }

    Color4b operator -(const Color4b& lhs, const Color4b& rhs) {
        return Color4b(std::min(lhs.red - rhs.red, 0),
                     std::min(lhs.green - rhs.green, 0),
                     std::min(lhs.blue - rhs.blue, 0),
                     std::min(lhs.alpha - rhs.alpha, 0));
    }

    Color4b operator *(const Color4b& lhs, const Color4b& rhs) {
        return Color4b((lhs.red * rhs.red) / 255,
                     (lhs.green * rhs.green) / 255,
                     (lhs.blue * rhs.blue) / 255,
                     (lhs.alpha * rhs.alpha) / 255);
    }

    bool operator ==(const Color4b& lhs, const Color4b& rhs) {
        return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha;
    }

    bool operator !=(const Color4b& lhs, const Color4b& rhs) {
        return !(lhs == rhs);
    }
}
