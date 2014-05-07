#ifndef SURFACE_HPP
#define SURFACE_HPP

#ifdef _DEBUG
#include <iostream>
#endif

#include <string>
#include <SDL_image.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Math/Rect.hpp>
#include <SGL/Graphic/Color.hpp>

#define R_MASK 0 /** Default Red Mask. */
#define G_MASK 0 /** Default Green Mask. */
#define B_MASK 0 /** Default Blue Mask. */

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	#define A_MASK 0xff000000
#else
	#define A_MASK 0x000000ff
#endif

namespace sgl {
	class Surface {
	private:
		SDL_Surface* _surface;

	public:
		static const uint8 DefaultDepth = 32;

		enum class BlendMode {
			/**
			no blending
			dstRGBA = srcRGBA
			*/
			None = SDL_BLENDMODE_NONE,
			/**
			alpha blending
			dstRGB = (srcRGB * srcA) + (dstRGB * (1 - srcA))
			dstA = srcA + (dstA * (1 - srcA))
			*/
			Blend = SDL_BLENDMODE_BLEND,
			/**
			additive blending
			dstRGB = (srcRGB * srcA) + dstRGB
			dstA = dstA
			*/
			Add = SDL_BLENDMODE_ADD,
			/**
			color modulate
			dstRGB = srcRGB * dstRGB
			dstA = dstA
			*/
			Mod = SDL_BLENDMODE_MOD
		};

		enum class Mask : uint8 {
			Red,
			Green,
			Blue,
			Alpha
		};

	public:
		explicit Surface();
		explicit Surface(SDL_Surface* srfc);
		explicit Surface(const std::string& filename);
		explicit Surface(uint16 width, uint16 height, uint8 depth = DefaultDepth);
		explicit Surface(void* pixels, uint16 width, uint16 height, uint8 depth = DefaultDepth);

		virtual ~Surface();

		SDL_Surface* ptr() const {
			return _surface;
		}

		void loadFromFile(const std::string& filename);
		void loadFromMemory(void* pixel, uint16 width, uint16 height, uint8 depth = DefaultDepth);
		void saveToFile(const std::string& filename);
		void blit(const Surface& srfc, const ShortRect* dst = nullptr, const ShortRect* src = nullptr);
		Surface subSurface(const ShortRect& rect);

		void setRLE(bool enable) const {
			SDL_SetSurfaceRLE(_surface, enable);
		}

		void setColorKey(const Color& col, bool enable = true) const;
		Color getColorKey() const;
		void setColorMod(const Color& col) const;
		Color getColorMod() const;
		void setClipRect(const ShortRect& rect) const;
		ShortRect getClipRect() const;

		void setBlendMode(BlendMode bmode) const {
			SDL_SetSurfaceBlendMode(_surface, static_cast<SDL_BlendMode>(bmode));
		}

		BlendMode getBlendMode() const;

		uint16 width() const {
			if (_surface == nullptr)
				return 0;
			return _surface->w;
		}

		uint16 height() const {
			if (_surface == nullptr)
				return 0;
			return _surface->h;
		}

		uint8 bytes() const {
			if (_surface == nullptr)
				return 0;
			return _surface->format->BytesPerPixel;
		}

		uint8 bits() const {
			if (_surface == nullptr)
				return 0;
			return _surface->format->BitsPerPixel;
		}

		void* pixels() const {
			if (_surface == nullptr)
				return nullptr;
			return _surface->pixels;
		}

		bool isMask(Mask mask, uint32 value) const;
	};

	bool operator ==(const Surface& lhs, const Surface& rhs);
	bool operator !=(const Surface& lhs, const Surface& rhs);
	bool operator ==(const Surface& lhs, const SDL_Surface* rhs);
	bool operator !=(const Surface& lhs, const SDL_Surface* rhs);
}

#endif