#include <SGL/Graphic/Shape.hpp>
#include <SGL/Window/Window.hpp>
#include <SGL/Graphic/Texture.hpp>

namespace sgl {
	Shape::Shape(Type _type) : type(_type) {

	}

	void Shape::_update() {
		const Vertex* vlt = &this->vertices[0];
		const Vertex* vrb = &this->vertices[1];

		for (uint32 i = 2; i < this->vertices.size(); i++) {
			const Vertex& vi = this->vertices[i];

			if (vlt->x >= vi.x && vlt->y > vi.y)
				vlt = &vi;
			else if (vrb->x <= vi.x && vrb->y < vi.y)
				vrb = &vi;
		}

		Transformable::setViewport(vlt->x, vlt->y, vrb->x - vlt->x, vrb->y - vlt->y);
	}

	void Shape::addVertices(const ShortRect& rect) {
		this->vertices.reserve(4);

		this->vertices.emplace_back(Vertex(rect.x, rect.y));
		this->vertices.emplace_back(Vertex(rect.x + rect.width, rect.y));
		this->vertices.emplace_back(Vertex(rect.x + rect.width, rect.y + rect.height));
		this->vertices.emplace_back(Vertex(rect.x, rect.y + rect.height));

		_update();
	}

	void Shape::addVertices(const Range<float> range) {
		if (range.length() == 0)
			return;

		for (uint16 i = 0, j = 0; i < range.length() / 2; i++, j += 2) {
			this->vertices.emplace_back(Vertex(range[j], range[j + 1]));
		}

		_update();
	}

	void Shape::updateVertices(const Range<float> range, uint16 offset) {
		uint32 count = std::min(range.length(), this->vertices.size());
		if (count == 0)
			return this->addVertices(std::move(range));

		count += offset;

		for (uint32 i = offset, j = 0; i < count; i++, j += 2) {
			this->vertices[i].x = range[j];
			this->vertices[i].y = range[j + 1];
		}

		_update();
	}

	void Shape::updateVertices(const ShortRect& rect, uint16 offset) {
		const std::size_t min = 4;
		const uint32 count = std::min(min, this->vertices.size());
		if (count == 0)
			return this->addVertices(rect);

		this->vertices[offset].x = rect.x;
		this->vertices[offset].y = rect.y;

		this->vertices[offset + 1].x = rect.x + rect.width;
		this->vertices[offset + 1].y = rect.y;

		this->vertices[offset + 2].x = rect.x + rect.width;
		this->vertices[offset + 2].y = rect.y + rect.height;

		this->vertices[offset + 3].x = rect.x;
		this->vertices[offset + 3].y = rect.y + rect.height;

		_update();
	}

	void Shape::updateTextureCoordinates(const Range<float> range, uint16 offset) {
		uint32 count = std::min(range.length(), this->vertices.size());
		if (count == 0)
			return;

		count += offset;

		for (uint32 i = offset, j = 0; i < count; i++, j += 2) {
			this->vertices[i].tx = range[j];
			this->vertices[i].ty = range[j + 1];
		}

		_update();
	}

	void Shape::draw(const Window& wnd) const {
		if (this->vertices.size() == 0)
			return;

		GLAttribScope attr(GL_ENABLE_BIT);

		if (this->smooth.target != Smooth::Target::None) {
			switch (this->smooth.target) {
				case Smooth::Target::Line:
					glEnable(GL_LINE_SMOOTH);
					break;
				case Smooth::Target::Point:
					glEnable(GL_POINT_SMOOTH);
					break;
				case Smooth::Target::Polygon:
					glEnable(GL_POLYGON_SMOOTH);
					break;
			}

			glHint(static_cast<GLenum>(this->smooth.target), static_cast<GLenum>(this->smooth.mode));
		}

		if (this->lineWidth > 1)
			glLineWidth(this->lineWidth);

		Transformable::applyTransformation();

		const Type shape_type = this->texture == nullptr && !this->fill ? Type::LineLoop : this->type;
		const Vertex* vptr = &this->vertices[0];

		Primitive p(&vptr->x, &vptr->r, static_cast<GLenum>(shape_type), this->vertices.size());
		p.offset = sizeof(Vertex);

		wnd.draw(p, &vptr->tx, this->texture);
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

		Transformable::move(x, y);
	}
}