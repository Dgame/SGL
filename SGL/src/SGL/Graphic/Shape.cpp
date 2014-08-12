#include <SGL/Graphic/Shape.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	void Shape::_update(Update which) {
		if (which != Update::Position)
			Transformable::_update(which);
	}

	void Shape::draw(const Window* wnd) const {
		wnd->draw(this->geometry, this->getMatrix(), this->vertices, this->texture);
	}

	Shape::Shape(Geometry geo) : geometry(geo) {

	}

	void Shape::setColor(const Color4b& col) {
		for (Vertex& v : this->vertices) {
			v.setColor(col);
		}
	}

	void Shape::move(float x, float y) {
		for (Vertex& v : this->vertices) {
			v.position.x += x;
			v.position.y += y;
		}

		Transformable::move(x, y);
	}

	void Shape::move(const vec2f& offset) {
		this->move(offset.x, offset.y);
	}
}