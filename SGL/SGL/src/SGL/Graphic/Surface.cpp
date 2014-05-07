#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	Surface::Surface() : _surface(nullptr) {

	}

	Surface::Surface(SDL_Surface* srfc) : _surface(srfc) {

	}

	Surface::Surface(const std::string& filename) {
		this->loadFromFile(filename);
	}

	Surface::Surface(uint16 width, uint16 height, uint8 depth) {
		_surface = SDL_CreateRGBSurface(0, width, height, depth, R_MASK, G_MASK, B_MASK, A_MASK);
	}

	Surface::Surface(void* pixels, uint16 width, uint16 height, uint8 depth) {
		this->loadFromMemory(pixels, width, height, depth);
	}

	Surface::~Surface() {
		SDL_FreeSurface(_surface);
		_surface = nullptr;
	}

	void Surface::loadFromFile(const std::string& filename) {
		_surface = IMG_Load(filename.c_str());
		if (_surface == nullptr) {
			printf("Cannot load image %s: %s.\n", filename.c_str(), SDL_GetError());
			exit(1);
		}
	}

	void Surface::loadFromMemory(void* pixels, uint16 width, uint16 height, uint8 depth) {
		if (pixels == nullptr) {
			printf("No memory\n");
			exit(1);
		}

		_surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, width * (depth / 8), R_MASK, G_MASK, B_MASK, A_MASK);
	}

	void Surface::saveToFile(const std::string& filename) {
#if 1
		IMG_SavePNG(_surface, filename.c_str());
#else
		SDL_SaveBMP(_surface, filename.c_str());
#endif
	}

	void Surface::blit(const Surface& srfc, const ShortRect* dst, const ShortRect* src) {
		SDL_Rect _src;
		SDL_Rect _dst;

		SDL_Rect* psrc = Rect<short>::Copy(dst, _dst);
		SDL_Rect* pdst = Rect<short>::Copy(src, _src);

		SDL_BlitSurface(srfc._surface, psrc, _surface, pdst);
	}

	Surface Surface::subSurface(const ShortRect& rect) {
		Surface sub(rect.width, rect.height, this->bits());
		sub.blit(*this, nullptr, &rect);

		return sub;
	}

	void Surface::setColorKey(const Color& col, bool enable) const {
		const uint32 key = SDL_MapRGBA(_surface->format, col.red, col.green, col.blue, col.alpha);
		SDL_SetColorKey(_surface, enable, key);
	}

	Color Surface::getColorKey() const {
		uint32 key;
		SDL_GetColorKey(_surface, &key);

		uint8 r, g, b, a;
		SDL_GetRGBA(key, _surface->format, &r, &g, &b, &a);

		return Color(r, g, b, a);
	}

	void Surface::setColorMod(const Color& col) const {
		SDL_SetSurfaceColorMod(_surface, col.red, col.green, col.blue);
		SDL_SetSurfaceAlphaMod(_surface, col.alpha);
	}

	Color Surface::getColorMod() const {
		uint8 r, g, b, a;
		SDL_GetSurfaceColorMod(_surface, &r, &g, &b);
		SDL_GetSurfaceAlphaMod(_surface, &a);

		return Color(r, g, b, a);
	}

	void Surface::setClipRect(const ShortRect& rect) const {
		SDL_Rect a;
		SDL_Rect* ap = Rect<short>::Copy(&rect, a);

		SDL_SetClipRect(_surface, ap);
	}

	ShortRect Surface::getClipRect() const {
		SDL_Rect rect;
		SDL_GetClipRect(_surface, &rect);

		return ShortRect(rect.x, rect.y, rect.w, rect.h);
	}

	Surface::BlendMode Surface::getBlendMode() const {
		SDL_BlendMode blendMode;
		SDL_GetSurfaceBlendMode(_surface, &blendMode);

		return static_cast<BlendMode>(blendMode);
	}

	bool Surface::isMask(Mask mask, uint32 value) const {
		switch (mask) {
			case Mask::Red:
				return _surface->format->Rmask == value;
			case Mask::Green:
				return _surface->format->Gmask == value;
			case Mask::Blue:
				return _surface->format->Bmask == value;
			case Mask::Alpha:
				return _surface->format->Amask == value;
		}

		return false;
	}

	bool operator ==(const Surface& lhs, const Surface& rhs) {
		return lhs.ptr() == rhs.ptr();
	}

	bool operator !=(const Surface& lhs, const Surface& rhs) {
		return !(lhs == rhs);
	}

	bool operator ==(const Surface& lhs, const SDL_Surface* rhs) {
		return lhs.ptr() == rhs;
	}

	bool operator !=(const Surface& lhs, const SDL_Surface* rhs) {
		return !(lhs == rhs);
	}
}