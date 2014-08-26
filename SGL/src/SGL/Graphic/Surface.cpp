#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	Surface::Surface(const std::string& filename) {
		this->loadFromFile(filename);
	}

	Surface::Surface(uint16 width, uint16 height, uint8 depth, void* pixels) {
		if (!pixels) {
			_surface = SDL_CreateRGBSurface(0, width, height, depth, R_MASK, G_MASK, B_MASK, A_MASK);
			if (!_surface)
				std::cerr << SDL_GetError() << std::endl;
		}  else
			this->loadFromMemory(pixels, width, height, depth);
	}

	Surface::Surface(const Surface& other) {
		_surface = other._surface;
		_surface->refcount++;
	}

	Surface::~Surface() {
		_freeSurface();
	}

	void Surface::_freeSurface() {
		if (_surface && !(--_surface->refcount)) {
			SDL_Check(SDL_FreeSurface(_surface));
		}
	}

	void Surface::loadFromFile(const std::string& filename) {
		_freeSurface();
		_surface = IMG_Load(filename.c_str());
		if (!_surface)
			std::cerr << SDL_GetError() << std::endl;
	}

	void Surface::loadFromMemory(void* pixels, uint16 width, uint16 height, uint8 depth) {
		if (pixels) {
			_freeSurface();
			const uint16 pitch = width * (depth / 8);
			_surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, R_MASK, G_MASK, B_MASK, A_MASK);
			if (!_surface)
				std::cerr << SDL_GetError() << std::endl;
		}
	}

	void Surface::saveToFile(const std::string& filename) const {
		SDL_Check(IMG_SavePNG(_surface, filename.c_str()));
	}

	void Surface::blit(const Surface& other, const ShortRect& src, const ShortRect* dst) const {
		SDL_Rect a, b;

		if (dst != nullptr)
			SDL_Check(SDL_BlitSurface(other._surface, Copy(src, &a), _surface, Copy(*dst, &b)));
		else
			SDL_Check(SDL_BlitSurface(other._surface, Copy(src, &a), _surface, nullptr));
	}

	Surface Surface::subSurface(const ShortRect& rect) const {
		Surface sub(rect.width, rect.height, this->bits());
		sub.blit(*this, rect);

		return sub;
	}

	bool operator ==(const Surface& lhs, const Surface& rhs) {
		return lhs.getSurface() == rhs.getSurface();
	}

	bool operator !=(const Surface& lhs, const Surface& rhs) {
		return !(lhs == rhs);
	}
}