#include <Graphic\Surface.h>

Surface::Surface() : _surface(nullptr) {

}

Surface::Surface(SDL_Surface* srfc) : _surface(srfc) {

}

Surface::Surface(const std::string& filename) {
	this->loadFromFile(filename);
}

Surface::Surface(uint16 width, uint16 height, uint8 depth) : _depth(depth) {
	SDL_Surface* srfc = SDL_CreateRGBSurface(0, width, height, depth, R_MASK, G_MASK, B_MASK, A_MASK);
	_surface = std::shared_ptr<SDL_Surface>(srfc, SDL_FreeSurface);
}

Surface::Surface(void* pixels, uint16 width, uint16 height, uint8 depth) {
	this->loadFromMemory(pixels, width, height, depth);
}

void Surface::loadFromFile(const std::string& filename) {
	SDL_Surface* srfc = IMG_Load(filename.c_str());
	if (srfc == nullptr)
		throw "Cannot load this image. Check SDL_GetError for informations.";

	_surface = std::shared_ptr<SDL_Surface>(srfc, SDL_FreeSurface);
}

void Surface::loadFromMemory(void* pixels, uint16 width, uint16 height, uint8 depth) {
	if (pixels == nullptr)
		std::cerr << "Null memory" << std::endl;

	_depth = depth;

	SDL_Surface* srfc = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, width * (depth / 8), R_MASK, G_MASK, B_MASK, A_MASK);
	_surface = std::shared_ptr<SDL_Surface>(srfc, SDL_FreeSurface);
}

void Surface::saveToFile(const std::string& filename) {
	try {
		IMG_SavePNG(_surface.get(), filename.c_str());
	} catch(...) {
		SDL_SaveBMP(_surface.get(), filename.c_str());
	}
}

void Surface::blit(const Surface& srfc, const ShortRect* dst, const ShortRect* src) {
	SDL_Rect _src;
	SDL_Rect _dst;

	SDL_Rect* psrc = Rect<short>::Copy(dst, _dst);
	SDL_Rect* pdst = Rect<short>::Copy(src, _src);

	SDL_BlitSurface(srfc.ptr(), psrc, this->ptr(), pdst);
}

Surface Surface::subSurface(const ShortRect& rect) {
	Surface sub(rect.width, rect.height, _depth);
	sub.blit(*this, nullptr, &rect);

	return sub;
}

void Surface::setColorKey(const Color& col, bool enable) const {
	uint32 key = SDL_MapRGBA(_surface->format, col.red, col.green, col.blue, col.alpha);
	SDL_SetColorKey(_surface.get(), enable, key);
}

Color Surface::getColorKey() const {
	uint32 key;
	SDL_GetColorKey(_surface.get(), &key);

	uint8 r, g, b, a;
	SDL_GetRGBA(key, _surface->format, &r, &g, &b, &a);

	return Color(r, g, b, a);
}

void Surface::setColorMod(const Color& col) const {
	SDL_SetSurfaceColorMod(_surface.get(), col.red, col.green, col.blue);
	SDL_SetSurfaceAlphaMod(_surface.get(), col.alpha);
}

Color Surface::getColorMod() const {
	uint8 r, g, b, a;
	SDL_GetSurfaceColorMod(_surface.get(), &r, &g, &b);
	SDL_GetSurfaceAlphaMod(_surface.get(), &a);

	return Color(r, g, b, a);
}

void Surface::setClipRect(const ShortRect& rect) const {
	SDL_Rect a;
	SDL_Rect* ap = Rect<short>::Copy(&rect, a);

	SDL_SetClipRect(_surface.get(), ap);
}

ShortRect Surface::getClipRect() const {
	SDL_Rect rect;
	SDL_GetClipRect(_surface.get(), &rect);

	return ShortRect(rect.x, rect.y, rect.w, rect.h);
}

void Surface::setBlendMode(BlendMode bmode) const {
	SDL_SetSurfaceBlendMode(_surface.get(), static_cast<SDL_BlendMode>(bmode));
}

Surface::BlendMode Surface::getBlendMode() const {
	SDL_BlendMode blendMode;
	SDL_GetSurfaceBlendMode(_surface.get(), &blendMode);

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
