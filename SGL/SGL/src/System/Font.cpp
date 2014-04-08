#include <System\Font.hpp>

namespace sgl {
	void Font::loadFromFile(const std::string& filename, uint8 fontSize) {
		_fontSize = fontSize == 0 ? _fontSize : fontSize;
		if (_fontSize == 0)
			_fontSize = 12;

		_ttf = TTF_OpenFont(filename.c_str(), _fontSize);
		if (_ttf == nullptr) {
			printf("Could not load font %s. TTF Error: %s.", filename.c_str(), TTF_GetError());
			exit(1);
		}
	}

	Surface Font::render(const std::string& text, Color* fg, Color* bg, Mode mode) const {
		SDL_Color _fg;
		SDL_Color _bg;

		Color::Copy(fg, _fg, Color::Black);
		Color::Copy(bg, _bg, Color::White);

		SDL_Surface* srfc = nullptr;
		switch (mode) {
			case Mode::Solid:
				srfc = TTF_RenderUTF8_Solid(_ttf, text.c_str(), _fg);
				break;
			case Mode::Shaded:
				srfc = TTF_RenderUTF8_Shaded(_ttf, text.c_str(), _fg, _bg);
				break;
			case Mode::Blended:
				srfc = TTF_RenderUTF8_Blended(_ttf, text.c_str(), _fg);
				break;
		}

		if (srfc == nullptr) {
			printf("NULL Surface: %s\n", SDL_GetError());
			exit(1);
		}

		SDL_PixelFormat fmt = *srfc->format;
		fmt.BitsPerPixel = 24;
		SDL_Surface* new_srfc = SDL_ConvertSurface(srfc, &fmt, 0);
		SDL_FreeSurface(srfc);

		return Surface(new_srfc);
	}
}