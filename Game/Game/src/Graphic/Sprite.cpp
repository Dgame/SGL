#include <Graphic\Sprite.h>

void Sprite::draw(const Window& wnd) const {
	if (_texture != nullptr) {
		float dx = position.x, dy = position.y;
		float dw = _texture->width();
		float dh = _texture->height();

		const float vertices[] = {
			dx, dy,
			dx + dw, dy,
			dx + dw, dy + dh,
			dx, dy + dh
		};

		static const float texCoords[] = {0, 0, 1, 0, 1, 1, 0, 1};

		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		_texture->bind();

		glDrawArrays(GL_QUADS, 0, 8);
	}
}