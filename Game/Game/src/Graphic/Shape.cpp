#include <Graphic\Shape.h>

Shape::Shape(Type _type) : type(_type), lineWidth(1), fill(false) {

}

void Shape::draw(const Window& wnd) const {
	if (this->vertices.size() == 0)
		return;

	glPushAttrib(GL_ENABLE_BIT);

	if (_texture == nullptr)
		glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	if (this->lineWidth > 1)
		glLineWidth(this->lineWidth);

	glEnableClientState(GL_COLOR_ARRAY);

	const Vertex* vptr = &this->vertices[0];

	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &vptr->x);
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), &vptr->r);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vptr->tx);

	const Type shape_type = _texture == nullptr && !this->fill ? Type::LineLoop : this->type;

	if (_texture != nullptr)
		_texture->bind();

	glDrawArrays(static_cast<GLenum>(shape_type), 0, this->vertices.size());

	glDisableClientState(GL_COLOR_ARRAY);

	glPopAttrib();
}

void Shape::setColor(const Color& col) {
	for (Vertex& v : this->vertices) {
		v.setColor(col);
	}
}

void Shape::bindTexture(Texture* tex) {
	if (tex == nullptr)
		_texture.reset();
	else
		_texture = std::make_shared<Texture>(*tex);
}

void Shape::move(float x, float y) {
	for (Vertex& v : this->vertices) {
		v.x += x;
		v.y += y;
	}
}