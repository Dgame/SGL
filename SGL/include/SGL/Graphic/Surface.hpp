#ifndef SGL_SURFACE_HPP
#define SGL_SURFACE_HPP

#include <memory>
#include <string>
#include <SGL/Core/SDL.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	struct Surface {
		SDL_Surface* _surface = nullptr;

		Surface() = default;
		explicit Surface(SDL_Surface*);
		explicit Surface(const std::string&);
		explicit Surface(uint16 width, uint16 height, uint8 depth = 32, void* pixels = nullptr);

		virtual ~Surface();

		void loadFromFile(const std::string&);
		void loadFromMemory(void*, uint16 width, uint16 height, uint8 depth = 32);
		void saveToFile(const std::string&) const;

		void blit(const Surface&, const ShortRect&, const ShortRect* dest = nullptr) const;
		Surface subSurface(const ShortRect&) const;

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
	};

	bool operator ==(const Surface& lhs, const Surface& rhs);
	bool operator !=(const Surface& lhs, const Surface& rhs);
}

#endif