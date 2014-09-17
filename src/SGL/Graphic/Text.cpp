#include <SGL/Graphic/Text.hpp>
#include <SGL/Graphic/Surface.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	void Text::draw(const Window* wnd) const {
		if (_redraw || this->wasTransformed()) {
			_redraw = false;
			_texture.load(_font->render(_text, this->foreground, this->background, this->mode));
			// Update Vertices
			const float tw = _texture.width();
			const float th = _texture.height();
			// #2
			_vertices[1].position.x = tw;
			// #3
			_vertices[2].position.y = th;
			// #4
			_vertices[3].position.x = tw;
			_vertices[3].position.y = th;
		}

		wnd->draw(Geometry::TriangleStrip, this->getMatrix(), _texture, _vertices, 8);
	}

	Text::Text(Font& font, const std::string& str) : _font(&font), _text(str) {
		_init();
	}

	Text::Text(const Text& other) :
		_font(other._font), _text(other._text),
		foreground(other.foreground), background(other.background), mode(other.mode)
	{
		_init();
	}

	void Text::_init() {
		// #2
		_vertices[1].texCoord.x = 1;
		// #3
		_vertices[2].texCoord.y = 1;
		// #4
		_vertices[3].texCoord.x = 1;
		_vertices[3].texCoord.y = 1;

		for (Vertex& v : _vertices) {
			v.setColor(Color4b::White);
		}
	}

	void Text::operator =(const Text& txt) {
	    _text = txt._text;
	    _redraw = true;
	}

	void Text::operator =(const std::string& str) {
		_text = str;
		_redraw = true;
	}

	void Text::setFont(Font& font) {
		_font = &font;
		_redraw = true;
	}
}
