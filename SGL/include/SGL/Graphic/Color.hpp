#ifndef SGL_COLOR_HPP
#define SGL_COLOR_HPP

#include <algorithm>
#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Types.hpp>

namespace sgl {
	template <typename T>
	struct Color4;

	template <>
	struct Color4<uint8> {
		static const Color4<uint8> Red;
		static const Color4<uint8> Green;
		static const Color4<uint8> Blue;
		static const Color4<uint8> Yellow;
		static const Color4<uint8> Black;
		static const Color4<uint8> White;

		uint8 red, green, blue, alpha;

		explicit Color4(uint8 r, uint8 g, uint8 b, uint8 a = 255);
		Color4(const Color4<float>&);
	};

	template <>
	struct Color4<float> {
		static const Color4<float> Red;
		static const Color4<float> Green;
		static const Color4<float> Blue;
		static const Color4<float> Yellow;
		static const Color4<float> Black;
		static const Color4<float> White;

		float red, green, blue, alpha;

		explicit Color4(uint8 r, uint8 g, uint8 b, uint8 a = 255);
		explicit Color4(float r, float g, float b, float a = 1.0f);
		Color4(const Color4<uint8>&);
	};
	
	using Color4b = Color4<uint8>;
	using Color4f = Color4<float>;

	SDL_Color* Copy(const Color4b&, SDL_Color*);

	Color4b& operator +=(Color4b&, uint8 value);
	Color4b& operator -=(Color4b&, uint8 value);
	Color4b& operator *=(Color4b&, uint8 value);

	Color4b operator +(const Color4b&, const Color4b&);
	Color4b operator -(const Color4b&, const Color4b&);
	Color4b operator *(const Color4b&, const Color4b&);

	bool operator ==(const Color4b&, const Color4b&);
	bool operator !=(const Color4b&, const Color4b&);
}

#endif