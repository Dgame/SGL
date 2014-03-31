#include <Graphic\String.h>

namespace sgl {
	String::String(Font& fnt, const std::string& str) :
		mode(Font::Mode::Solid), _text(str), font(fnt),
		fg(nullptr), bg(nullptr), _texture(new Texture())
	{
		update();
	}

	void String::operator =(const std::string& str) {
		if (str != _text) {
			_text = str;
			_changed = true;
		}
	}

	void String::operator =(const String& txt) {
		const std::string& str = txt._text;

		if (str != _text) {
			_text = str;
			_changed = true;
		}
	}

	void String::_update() const {
		_changed = false;

		Surface srfc = font.render(_text, this->fg, this->bg, mode);
		_texture->loadFrom(srfc);
	}

	void String::draw(const Window& wnd) const {
		if (_changed)
			_update();

		float dx = position.x, dy = position.y;
		float dw = _texture->width();
		float dh = _texture->height();

		const float vertices[] = {
			dx, dy,
			dx + dw, dy,
			dx + dw, dy + dh,
			dx, dy + dh
		};

		static const float texCoords[] = {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		};

		wnd.draw(vertices, texCoords, *_texture);
	}
}