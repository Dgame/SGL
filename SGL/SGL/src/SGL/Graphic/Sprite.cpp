#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Sprite::Sprite() : position(0, 0) {

	}

	Sprite::Sprite(Texture& tex) : Sprite() {
		this->setTexture(tex);
	}

	void Sprite::draw(const Window& wnd) const {
		const float dx = this->position.x;
		const float dy = this->position.y;
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

		GLMatrixScope mat;
		Transform::_applyTransformation(dx + (dw / 2), dy + (dh / 2));

		wnd.draw(Primitive(vertices), texCoords, _texture);
	}
}