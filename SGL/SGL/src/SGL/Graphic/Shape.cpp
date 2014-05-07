#include <SGL/Graphic/Shape.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Shape::Shape(Type _type) : type(_type) {

	}

	void Shape::addVertices(const ShortRect& rect) {
		this->vertices.reserve(4);

		this->vertices.emplace_back(Vertex(rect.x, rect.y));
		this->vertices.emplace_back(Vertex(rect.x + rect.width, rect.y));
		this->vertices.emplace_back(Vertex(rect.x + rect.width, rect.y + rect.height));
		this->vertices.emplace_back(Vertex(rect.x, rect.y + rect.height));
	}

	void Shape::addVertices(const Range<float> range) {
		if (range.length == 0)
			return;

		for (uint16 i = 0, j = 0; i < range.length / 2; i++, j += 2) {
			this->vertices.emplace_back(Vertex(range[j], range[j + 1]));
		}
	}

	void Shape::updateVertices(const Range<float> range, uint16 offset) {
		uint32 count = std::min(range.length, this->vertices.size());
		if (count == 0)
			return this->addVertices(std::move(range));

		count += offset;

		for (uint32 i = offset, j = 0; i < count; i++, j += 2) {
			this->vertices[i].x = range[j];
			this->vertices[i].y = range[j + 1];
		}
	}

	void Shape::updateVertices(const ShortRect& rect, uint16 offset) {
		uint32 count = std::min(static_cast<std::size_t>(4), this->vertices.size());
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
	}

	void Shape::updateTextureCoordinates(const Range<float> range, uint16 offset) {
		uint32 count = std::min(range.length, this->vertices.size());
		if (count == 0)
			return;

		count += offset;

		for (uint32 i = offset, j = 0; i < count; i++, j += 2) {
			this->vertices[i].tx = range[j];
			this->vertices[i].ty = range[j + 1];
		}
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

		GLMatrixScope mat;
		GraphTransform::_applyTransformation();

		const Type shape_type = this->texture == nullptr && !this->fill ? Type::LineLoop : this->type;

		const Vertex* vptr = &this->vertices[0];

		Primitive p(&vptr->x, &vptr->r, static_cast<GLenum>(shape_type), this->vertices.size());
		p.offset = sizeof(Vertex);

		wnd.draw(p, &vptr->tx, this->texture);
	}

	void Shape::calculateCenter() {
		const Vertex& v0 = this->vertices[0];

		float maxx = v0.x, minx = v0.x;
		float maxy = v0.y, miny = v0.y;

		for (uint32 i = 1; i < this->vertices.size(); i++) {
			const Vertex& vi = this->vertices[i];

			maxx = std::max(maxx, vi.x);
			minx = std::min(minx, vi.x);
			maxy = std::max(maxy, vi.y);
			miny = std::min(miny, vi.y);
		}

		GraphTransform::center.set((maxx - minx) / 2 + minx,
								   (maxy - miny) / 2 + miny);
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

		GraphTransform::center.move(x, y);
	}
}