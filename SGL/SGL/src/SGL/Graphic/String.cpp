#include <SGL/Graphic/String.hpp>
#include <SGL/Window/Window.hpp>

#pragma warning (disable: 4996) /* vsprintf */

namespace sgl {
	String::String() : mode(Font::Mode::Solid), _texture(new Texture()) {

	}

	String::String(Font& fnt) : String() {
		this->setFont(fnt);
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
			const int nWritten = vsprintf(&buffer[0], fmt, marker);
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
		if (_font != nullptr && _changed && _text.length() != 0) {
			Surface srfc = _font->render(_text, _fg, _bg, mode);

			Texture::Format fmt = Texture::Format::BGR;
			if (srfc.bits() == 32)
				fmt = Texture::Format::BGRA;

			_texture->loadFrom(srfc, fmt);
			_changed = false;
		}
	}

	void String::draw(const Window& wnd) const {
		if (_changed)
			_update();

		if (_texture->width() == 0 || _texture->height() == 0)
			return;

		const float dx = this->position.x;
		const float dy = this->position.y;
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

		wnd.draw(Primitive(vertices), texCoords, _texture.get());
	}

	bool operator ==(const String& lhs, const String& rhs) {
		return lhs.getText() == rhs.getText();
	}

	bool operator !=(const String& lhs, const String& rhs) {
		return !(lhs == rhs);
	}
}