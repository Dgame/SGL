#include <SGL/Graphic/Sprite.hpp>

namespace sgl {
	Sprite::Sprite(Texture& tex) : _texture(&tex), _boundingBox(0, 0, tex.width(), tex.height()) {

	}

	void Sprite::setTexture(Texture& tex) {
		_texture = &tex;

		_boundingBox = FloatRect(_position.x, _position.y, tex.width(), tex.height());
	}
	
	bool Sprite::collideWith(const FloatRect& bounds) const {
		return _boundingBox.intersects(bounds);
	}

	bool Sprite::collideWith(const Sprite& other) const {
		return this->collideWith(other.getBoundingBox());
	}

	void Sprite::move(float x, float y) {
		_position.x += x;
		_position.y += y;

		_boundingBox.move(x, y);

		_update(Update::Position);
	}

	void Sprite::move(const vec2f& vec) {
		_position += vec;

		_boundingBox.move(vec);

		_update(Update::Position);
	}
}