#ifndef SURFACE_HPP
#define SURFACE_HPP

#ifdef _DEBUG
#include <iostream>
#endif

#include <memory>
#include <string>
#include <SDL_image.h>
#include <Core\Types.h>
#include <Math\Rect.h>
#include <Graphic\Color.h>

#define DEFAULT_DEPTH 32

#define R_MASK 0 /** Default Red Mask. */
#define G_MASK 0 /** Default Green Mask. */
#define B_MASK 0 /** Default Blue Mask. */

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	#define A_MASK 0xff000000
#else
	#define A_MASK 0x000000ff
#endif

class Surface {
private:
	std::shared_ptr<SDL_Surface> _surface;
	uint8 _depth;

public:
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
	explicit Surface(uint16 width, uint16 height, uint8 depth = DEFAULT_DEPTH);
	explicit Surface(void* pixels, uint16 width, uint16 height, uint8 depth = DEFAULT_DEPTH);

	virtual ~Surface() {

	}

	void loadFromFile(const std::string& filename);
	void loadFromMemory(void* pixel, uint16 width, uint16 height, uint8 depth = DEFAULT_DEPTH);
	void saveToFile(const std::string& filename);
	void blit(const Surface& srfc, const ShortRect* dst = nullptr, const ShortRect* src = nullptr);
	Surface subSurface(const ShortRect& rect);

	void setRLE(bool enable) const {
		SDL_SetSurfaceRLE(_surface.get(), enable);
	}

	void setColorKey(const Color& col, bool enable = true) const;
	Color getColorKey() const;
	void setColorMod(const Color& col) const;
	Color getColorMod() const;
	void setClipRect(const ShortRect& rect) const;
	ShortRect getClipRect() const;
	void setBlendMode(BlendMode bmode) const;
	BlendMode getBlendMode() const;

	uint16 width() const {
		return _surface->w;
	}

	uint16 height() const {
		return _surface->h;
	}

	uint8 depth() const {
		return _depth;
	}

	void* pixels() const {
		return _surface->pixels;
	}

	bool isMask(Mask mask, uint32 value) const;

	SDL_Surface* ptr() const {
		return _surface.get();
	}
};

#endif