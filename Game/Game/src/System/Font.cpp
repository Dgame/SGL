#include <System\Font.h>

namespace sgl {
	void Font::loadFromFile(const std::string& filename, uint8 fontSize) {
		_filename = filename;

		_fontSize = fontSize == 0 ? _fontSize : fontSize;
		if (_fontSize == 0)
			_fontSize = 12;

		TTF_Font* font = TTF_OpenFont(filename.c_str(), _fontSize);
		if (font == nullptr) {
			printf("Could not load font %s. TTF Error: %s.", filename.c_str(), TTF_GetError());
			throw "Error while opening TTF_Font";
		}

		_ttf = std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
	}

	//Surface Font::render(const std::string& text, std::array<Color*, 2>& color, Mode mode) const {
	//	SDL_Surface* srfc = nullptr;

	//	SDL_Color fg;
	//	SDL_Color bg;

	//	Color::Copy(color[0], fg, Color::Black);
	//	Color::Copy(color[1], bg, Color::Transparent);

	//	switch (mode) {
	//		case Mode::Solid:
	//			srfc = TTF_RenderUTF8_Solid(_ttf.get(), text.c_str(), fg);
	//			break;
	//		case Mode::Shaded:
	//			srfc = TTF_RenderUTF8_Shaded(_ttf.get(), text.c_str(), fg, bg);
	//			break;
	//		case Mode::Blended:
	//			srfc = TTF_RenderUTF8_Blended(_ttf.get(), text.c_str(), fg);
	//			break;
	//	}

	//	return Surface(srfc);
	//}
}