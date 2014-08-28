#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Sprite::Sprite(Texture& tex) : _texture(&tex), _clipRect(0, 0, tex.width(), tex.height()) {
		_updateVertices();
		this->setColor(Color4b::White);
	}

	void Sprite::_updateVertices() {
		const float tx = _clipRect.x == 0 ? 0 : _clipRect.x / _texture->width();
		const float ty = _clipRect.y == 0 ? 0 : _clipRect.y / _texture->height();
		const float tw = _clipRect.width == _texture->width() ? 1 : _clipRect.width / _texture->width();
		const float th = _clipRect.height == _texture->height() ? 1 : _clipRect.height / _texture->height();
		// #1
		_vertices[0].texCoord.x = tx;
		_vertices[0].texCoord.y = ty;
		// #2
		_vertices[1].position.x = _clipRect.width;
		_vertices[1].texCoord.x = tx + tw;
		_vertices[1].texCoord.y = ty;
		// #3
		_vertices[2].position.y = _clipRect.height;
		_vertices[2].texCoord.x = tx;
		_vertices[2].texCoord.y = ty + th;
		// #4
		_vertices[3].position.x = _clipRect.width;
		_vertices[3].position.y = _clipRect.height;
		_vertices[3].texCoord.x = tx + tw;
		_vertices[3].texCoord.y = ty + th;
	}

	void Sprite::draw(const Window* wnd) const {
		wnd->draw(Geometry::TriangleStrip, this->getMatrix(), *_texture, _vertices, 8);
	}

	void Sprite::setTexture(Texture& tex) {
		_texture = &tex;
		_clipRect.x = _clipRect.y = 0;
		_clipRect.width = tex.width();
		_clipRect.height = tex.height();

		_updateVertices();
	}

	void Sprite::setColor(const Color4b& col) {
		for (Vertex& v : _vertices) {
			v.setColor(col);
		}
	}

	void Sprite::setClipRect(const FloatRect& clipRect) {
		_clipRect = clipRect;

		_updateVertices();
	}

	void Sprite::move(float x, float y) {
		_position.x += x;
		_position.y += y;
		
		Transformable::move(x, y);
		Transformable::transformed();
	}

	void Sprite::move(const vec2f& vec) {
		_position += vec;

		Transformable::move(vec);
		Transformable::transformed();
	}
}