#ifndef SGL_SURFACE_HPP
#define SGL_SURFACE_HPP

#include <string>
#include <SDL_image.h>
#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Check.hpp>
#include <SGL/Math/Rect.hpp>

#define R_MASK 0
#define G_MASK 0
#define B_MASK 0

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define A_MASK 0xff000000
#else
#define A_MASK 0x000000ff
#endif

namespace sgl {
	class Surface {
	private:
		SDL_Surface* _surface = nullptr;

		void _freeSurface();

	public:
		Surface() = default;
		Surface(const Surface&);
		explicit Surface(const std::string&);
		explicit Surface(uint16 width, uint16 height, uint8 depth = 32, void* pixels = nullptr);

		virtual ~Surface();

		void loadFromFile(const std::string&);
		void loadFromMemory(void*, uint16 width, uint16 height, uint8 depth = 32);
		void saveToFile(const std::string&) const;

		void blit(const Surface&, const ShortRect&, const ShortRect* dest = nullptr) const;
		Surface subSurface(const ShortRect&) const;

		uint16 width() const {
			if (!_surface)
				return 0;
			return _surface->w;
		}

		uint16 height() const {
			if (!_surface)
				return 0;
			return _surface->h;
		}

		uint8 bytes() const {
			if (!_surface)
				return 0;
			return _surface->format->BytesPerPixel;
		}

		uint8 bits() const {
			if (!_surface)
				return 0;
			return _surface->format->BitsPerPixel;
		}

		void* pixels() const {
			if (!_surface)
				return nullptr;
			return _surface->pixels;
		}

		SDL_Surface* ptr() const {
			return _surface;
		}

		int32 useCount() const {
			if (!_surface)
				return 0;
			return _surface->refcount;
		}
	};

	bool operator ==(const Surface& lhs, const Surface& rhs);
	bool operator !=(const Surface& lhs, const Surface& rhs);
}

#endif