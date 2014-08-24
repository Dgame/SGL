#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Sprite::Sprite(Texture& tex) : _texture(&tex), clipRect(0, 0, tex.width(), tex.height()) {

	}

	void Sprite::draw(const Window* wnd) const {
		wnd->draw(Geometry::Quad, this->getMatrix(), *_texture, this->clipRect);
	}

	void Sprite::setTexture(Texture& tex) {
		_texture = &tex;
		this->clipRect = FloatRect(0, 0, tex.width(), tex.height());
	}

	FloatRect Sprite::getBoundingRect() const {
		return FloatRect(_position.x, _position.y, _texture->width(), _texture->height());
	}

	void Sprite::move(float x, float y) {
		_position.x += x;
		_position.y += y;

		Transformable::updated();
		Transformable::move(x, y);
	}

	void Sprite::move(const vec2f& vec) {
		_position += vec;

		Transformable::updated();
		Transformable::move(vec);
	}
}