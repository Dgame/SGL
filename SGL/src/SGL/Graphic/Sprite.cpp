#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Sprite::Sprite(Texture& tex) : _texture(&tex), view(0, 0, tex.width(), tex.height()) {

	}

	void Sprite::draw(const Window* wnd) const {
		wnd->draw(Geometry::Quad, this->getMatrix(), *_texture, this->view);
	}

	void Sprite::setTexture(Texture& tex) {
		_texture = &tex;
		this->view = FloatRect(0, 0, tex.width(), tex.height());
	}

	FloatRect Sprite::getBoundingBox() const {
		return FloatRect(_position.x, _position.y, _texture->width(), _texture->height());
	}
	
	bool Sprite::collideWith(const FloatRect& rect) const {
		return this->getBoundingBox().intersects(rect);
	}

	bool Sprite::collideWith(const Sprite& other) const {
		return this->collideWith(other.getBoundingBox());
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