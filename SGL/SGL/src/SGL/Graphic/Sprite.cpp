#include <SGL/Graphic\Sprite.hpp>

namespace sgl {
	Sprite::Sprite(Texture& tex) : position(0, 0), texture(tex) {

	}

	void Sprite::draw(const Window& wnd) const {
		float dx = this->position.x, dy = this->position.y;
		float dw = this->width();
		float dh = this->height();

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

		wnd.draw(vertices, texCoords, this->texture);
	}
}