#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	Surface::Surface(SDL_Surface* srfc) : _surface(srfc) {

	}

	Surface::Surface(const std::string& filename) {
		this->loadFromFile(filename);
	}

	Surface::Surface(uint16 width, uint16 height, uint8 depth, void* pixels) {
		if (pixels == nullptr)
			_surface = SDL_CreateRGBSurface(0, width, height, depth, 0, 0, 0, 0);
		else
			this->loadFromMemory(pixels, width, height, depth);
	}

	Surface::~Surface() {
		if (_surface != nullptr)
			SDL_FreeSurface(_surface);
	}

	void Surface::loadFromFile(const std::string& filename) {
		if (_surface != nullptr)
			SDL_FreeSurface(_surface);

		_surface = IMG_Load(filename.c_str());
	}

	void Surface::loadFromMemory(void* pixels, uint16 width, uint16 height, uint8 depth) {
		_surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, width * (depth / 8), 0, 0, 0, 0);
	}

	void Surface::saveToFile(const std::string& filename) const {
		IMG_SavePNG(_surface, filename.c_str());
	}

	void Surface::blit(const Surface& srfc, const ShortRect& src, const ShortRect* dest) const {
		SDL_Rect a, b;

		if (dest != nullptr)
			SDL_BlitSurface(srfc._surface, src.copyTo(&a), _surface, dest->copyTo(&b));
		else
			SDL_BlitSurface(srfc._surface, src.copyTo(&a), _surface, nullptr);
	}

	Surface Surface::subSurface(const ShortRect& rect) const {
		Surface sub(rect.width, rect.height, this->bits());
		sub.blit(*this, rect);

		// SDL_Surface* s = sub._surface;
		// sub._surface = nullptr;

		// return Surface(s);
		return sub;
	}

	bool operator ==(const Surface& lhs, const Surface& rhs) {
		return lhs._surface == rhs._surface;
	}

	bool operator !=(const Surface& lhs, const Surface& rhs) {
		return !(lhs == rhs);
	}
}