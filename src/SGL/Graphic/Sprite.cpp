#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Sprite::Sprite(const Texture& tex) {
		this->setTexture(tex);
	}

	void Sprite::draw(const Window& wnd) const {
		const float dx = _position.x;
		const float dy = _position.y;
		const float dw = this->width();
		const float dh = this->height();

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

		Transformable::applyTransformation();

		wnd.draw(Primitive(vertices), texCoords, _texture);
	}
}