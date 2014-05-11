#include <SGL/System/Font.hpp>

namespace sgl {
	void Font::loadFromFile(const std::string& filename, uint8 fontSize) {
		_fontSize = fontSize == 0 ? _fontSize : fontSize;
		if (_fontSize == 0)
			_fontSize = DefaultSize;

		_ttf = TTF_OpenFont(filename.c_str(), _fontSize);
		if (_ttf == nullptr) {
			println("Could not load font: ", filename, " TTF Error: ", TTF_GetError());
			exit(1);
		}
	}

	Surface Font::render(const std::string& text, const Color* fg, const Color* bg, Mode mode) const {
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
			println("NULL Surface: ", SDL_GetError());
			exit(1);
		}

		if (srfc->format->BitsPerPixel < 24) {
			SDL_PixelFormat fmt = *(srfc->format);
			fmt.BitsPerPixel = 24;

			SDL_Surface* new_srfc = SDL_ConvertSurface(srfc, &fmt, 0);
			SDL_FreeSurface(srfc);

			if (new_srfc == nullptr) {
				println("NULL Surface (convert): ", SDL_GetError());
				exit(1);
			}

			return Surface(new_srfc);
		}

		return Surface(srfc);
	}
}