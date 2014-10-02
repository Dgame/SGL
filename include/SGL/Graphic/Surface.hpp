#ifndef SGL_SURFACE_HPP
#define SGL_SURFACE_HPP

#include <string>
#include <SGL/Core/SDL_Image.hpp>
#include <SGL/Core/Check.hpp>
#include <SGL/Math/Rect.hpp>
#include <SGL/Graphic/Color.hpp>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define R_MASK 0xff000000
    #define G_MASK 0x00ff0000
    #define B_MASK 0x0000ff00
    #define A_MASK 0x000000ff
#else
    #define R_MASK 0x000000ff
    #define G_MASK 0x0000ff00
    #define B_MASK 0x00ff0000
    #define A_MASK 0xff000000
#endif

namespace sgl {
    class Window;

    class Surface {
    private:
        friend class Window;

        SDL_Surface* _surface = nullptr;

    public:
        Surface() = default;
        Surface(const Surface&);
        explicit Surface(const std::string&);
        explicit Surface(uint16 width, uint16 height, uint8 depth = 32, void* pixels = nullptr);
        explicit Surface(SDL_Surface*);

        virtual ~Surface();

        bool loadFromFile(const std::string&);
        bool loadFromMemory(void*, uint16 width, uint16 height, uint8 depth = 32);
        bool saveToFile(const std::string&) const;

        void blit(const Surface&, const ShortRect* src = nullptr, const ShortRect* dest = nullptr) const;
        Surface subSurface(const ShortRect&) const;

        void setColorMod(const Color4b&) const;
        Color4b getColorMod() const;
        Color4b getMask() const;
        void fill(const Color4b&) const;

        void setRLE(bool enable) const;

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

        void* pixels() const;

        int32 useCount() const {
            if (!_surface)
                return 0;
            return _surface->refcount;
        }

        bool operator ==(const Surface&);
        bool operator !=(const Surface&);
    };
}

#endif
