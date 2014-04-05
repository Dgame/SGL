#include <Graphic\String.hpp>

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

	void String::format(const char* fmt, ...) {
		std::string retStr("");

		if (fmt != nullptr) {
			va_list marker = nullptr;
			// initialize variable arguments
			va_start(marker, fmt);
			// Get formatted string length adding one for NULL
			const int len = _vscprintf(fmt, marker) + 1;
			// Create a char vector to hold the formatted string.
			std::vector<char> buffer(len, '\0');
			const int nWritten = _vsnprintf_s(&buffer[0], buffer.size(), len, fmt, marker);
			if (nWritten > 0)
				retStr = &buffer[0];
			// Reset variable arguments
			va_end(marker);
		}

		if (retStr.length() != 0 && _text != retStr) {
			_text = retStr;
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

		const float dx = position.x;
		const float dy = position.y;
		const float dw = _texture->width();
		const float dh = _texture->height();

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