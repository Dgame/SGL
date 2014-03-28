#include <Graphic\String.h>

namespace sgl {
	String::String(const std::string& str, Mode m) : _text(str), mode(m) {

	}

	void String::draw(const Window& wnd) const {
		//SDL_Surface* srfc = nullptr;

		//SDL_Color fg;
		//SDL_Color bg;

		//Color::Copy(color[0], fg, Color::Black);
		//Color::Copy(color[1], bg, Color::Transparent);

		//switch (mode) {
		//	case Mode::Solid:
		//		srfc = TTF_RenderUTF8_Solid(_ttf.get(), text.c_str(), fg);
		//		break;
		//	case Mode::Shaded:
		//		srfc = TTF_RenderUTF8_Shaded(_ttf.get(), text.c_str(), fg, bg);
		//		break;
		//	case Mode::Blended:
		//		srfc = TTF_RenderUTF8_Blended(_ttf.get(), text.c_str(), fg);
		//		break;
		//}

		//Surface s = Surface(srfc);
	}
}