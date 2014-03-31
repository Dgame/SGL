#include <Graphic\Shape.h>

namespace sgl {
	Shape::Shape(Type _type) : type(_type), lineWidth(1), fill(false) {

	}

	void Shape::draw(const Window& wnd) const {
		if (this->vertices.size() == 0)
			return;

		glPushAttrib(GL_ENABLE_BIT);
		if (this->texture == nullptr)
			glDisable(GL_TEXTURE_2D);

		if (this->lineWidth > 1)
			glLineWidth(this->lineWidth);

		glEnableClientState(GL_COLOR_ARRAY);

		const Vertex* vptr = &this->vertices[0];

		glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &vptr->x);
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), &vptr->r);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vptr->tx);

		const Type shape_type = this->texture == nullptr && !this->fill ? Type::LineLoop : this->type;

		if (this->texture != nullptr)
			this->texture->bind();

		glDrawArrays(static_cast<GLenum>(shape_type), 0, this->vertices.size());
		glDisableClientState(GL_COLOR_ARRAY);
		glPopAttrib();

		if (this->texture != nullptr)
			this->texture->unbind();
	}

	void Shape::setColor(const Color& col) {
		for (Vertex& v : this->vertices) {
			v.setColor(col);
		}
	}

	void Shape::move(float x, float y) {
		for (Vertex& v : this->vertices) {
			v.x += x;
			v.y += y;
		}
	}
}