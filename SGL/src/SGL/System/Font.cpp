#include <SGL/System/Font.hpp>
#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	Font::Font(const std::string& filename, uint8 fontSize) {
		this->loadFromFile(filename, fontSize);
	}

	Font::~Font() {
		TTF_CloseFont(_ttf);
	}

	void Font::loadFromFile(const std::string& filename, uint8 fontSize) {
		_fontSize = fontSize == 0 ? 10 : fontSize;
		_ttf = TTF_OpenFont(filename.c_str(), _fontSize);
		if (!_ttf)
			std::cerr << TTF_GetError() << std::endl;
	}

	void Font::setStyle(Font::Style style) {
		if (_ttf)
			TTF_SetFontStyle(_ttf, static_cast<int>(style));
		else
			std::cerr << "Font is null" << std::endl;
	}

	Font::Style Font::getStyle() const {
		if (_ttf)
			return static_cast<Style>(TTF_GetFontStyle(_ttf));

		std::cerr << "Font is null" << std::endl;

		return Style::Normal;
	}

	Surface Font::render(const std::string& text, const Color4b& fg, const Color4b& bg, Mode mode) const {
		if (!_ttf) {
			std::cerr << "Font is null:" << TTF_GetError() << std::endl;
			exit(1);
		}

		SDL_Color a;
		SDL_Color b;

		Copy(fg, &a);
		Copy(bg, &b);

		SDL_Surface* srfc = nullptr;
		switch (mode) {
			case Mode::Solid:
				srfc = TTF_RenderUTF8_Solid(_ttf, text.c_str(), a);
				break;
			case Mode::Shaded:
				srfc = TTF_RenderUTF8_Shaded(_ttf, text.c_str(), a, b);
				break;
			case Mode::Blended:
				srfc = TTF_RenderUTF8_Blended(_ttf, text.c_str(), a);
				break;
		}

		if (!srfc)
			std::cerr << SDL_GetError() << std::endl;
		else if (srfc->format->BitsPerPixel < 24) {
			Surface result(srfc->w, srfc->h, 32);
			result.blit(srfc);
			SDL_FreeSurface(srfc);

			return result;
		}

		return Surface(srfc);
	}
}