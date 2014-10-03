#include <SGL/Graphic/Surface.hpp>

namespace sgl {
    Surface::Surface(const std::string& filename) {
        this->loadFromFile(filename);
    }

    Surface::Surface(uint16 the_width, uint16 the_height, uint8 depth, void* the_pixels) {
        if (!the_pixels) {
            _surface = SDL_CreateRGBSurface(0, the_width, the_height, depth, R_MASK, G_MASK, B_MASK, A_MASK);
            if (!_surface)
                std::cerr << SDL_GetError() << std::endl;
        }  else
            this->loadFromMemory(the_pixels, the_width, the_height, depth);
    }

    Surface::Surface(SDL_Surface* surface) : _surface(surface) {
        if (!_surface)
            std::cerr << "Surface is null" << std::endl;
    }

    Surface::Surface(const Surface& other) {
        _surface = other._surface;
        _surface->refcount++;
    }

    Surface::~Surface() {
        SDL_FreeSurface(_surface);
    }

    bool Surface::loadFromFile(const std::string& filename) {
        SDL_FreeSurface(_surface);

        _surface = IMG_Load(filename.c_str());
        if (!_surface) {
            std::cerr << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    bool Surface::loadFromMemory(void* the_pixels, uint16 the_width, uint16 the_height, uint8 depth) {
        if (the_pixels) {
            SDL_FreeSurface(_surface);

            const uint16 pitch = the_width * (depth / 8);
            _surface = SDL_CreateRGBSurfaceFrom(the_pixels, the_width, the_height, depth, pitch, R_MASK, G_MASK, B_MASK, A_MASK);
            if (!_surface) {
                std::cerr << SDL_GetError() << std::endl;
                return false;
            }

            return true;
        }

        return false;
    }

    bool Surface::saveToFile(const std::string& filename) const {
        return SDL_Check(IMG_SavePNG(_surface, filename.c_str()));
    }

    void Surface::blit(const Surface& other, const ShortRect* src, const ShortRect* dest) const {
        SDL_Rect a, b;
        const SDL_Rect* srcp = src ? Copy(*src, &a) : nullptr;
        SDL_Rect* destp = dest ? Copy(*dest, &b) : nullptr;

        SDL_Check(SDL_BlitSurface(other._surface, srcp, _surface, destp));
    }

    Surface Surface::subSurface(const ShortRect& rect) const {
        Surface sub(rect.width, rect.height, this->bits());
        sub.blit(*this, &rect);

        return sub;
    }

    void Surface::setColorMod(const Color4b& col) const {
        if (_surface) {
            SDL_Check(SDL_SetSurfaceColorMod(_surface, col.red, col.green, col.blue));
            SDL_Check(SDL_SetSurfaceAlphaMod(_surface, col.alpha));
        }
    }

    Color4b Surface::getColorMod() const {
        Color4b col = Color4b::Black;
        if (_surface) {
            SDL_Check(SDL_GetSurfaceColorMod(_surface, &col.red, &col.green, &col.blue));
            SDL_Check(SDL_GetSurfaceAlphaMod(_surface, &col.alpha));
        }

        return col;
    }

    Color4b Surface::getMask() const {
        if (!_surface)
            return Color4b::Black;
        return Color4b(_surface->format->Rmask, _surface->format->Gmask, _surface->format->Bmask, _surface->format->Amask);
    }

    void Surface::fill(const Color4b& col) const {
        if (_surface) {
            const uint32 key = SDL_MapRGBA(_surface->format, col.red, col.green, col.blue, col.alpha);
            SDL_Check(SDL_FillRect(_surface, &_surface->clip_rect, key));
        }
    }

    void Surface::setRLE(bool enable) const {
        if (_surface)
            SDL_Check(SDL_SetSurfaceRLE(_surface, enable ? 1 : 0));
    }

    void Surface::setAsIcon() const {
        SDL_Window* window = SDL_GL_GetCurrentWindow();
        SDL_SetWindowIcon(window, _surface);
    }

    void* Surface::pixels() const {
        if (!_surface)
            return nullptr;

        if (SDL_MUSTLOCK(_surface))
            SDL_LockSurface(_surface);

        void* my_pixels = _surface->pixels;

        if (SDL_MUSTLOCK(_surface))
            SDL_UnlockSurface(_surface);

        return my_pixels;
    }

    Surface::operator bool() const {
        return _surface != nullptr;
    }

    bool Surface::operator ==(const Surface& other) {
        if (!_surface || !other._surface)
            return false;
        return _surface == other._surface;
    }

    bool Surface::operator !=(const Surface& other) {
        return !(*this == other);
    }
}
