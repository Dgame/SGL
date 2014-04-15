#include <SGL/Math\Vertex.hpp>

namespace sgl {
	Vertex::Vertex(float _x, float _y) : Vertex(_x, _y, 0, 0) {

	}

	Vertex::Vertex(float _x, float _y, float _tx, float _ty) : x(_x), y(_y), tx(_tx), ty(_ty) {
		setColor(Color::Black);
	}

	void Vertex::setColor(const Color& col) {
		this->r = col.red > 1 ? col.red / 255.f : col.red;
		this->g = col.green > 1 ? col.green / 255.f : col.green;
		this->b = col.blue > 1 ? col.blue / 255.f : col.blue;
		this->a = col.alpha > 1 ? col.alpha / 255.f : col.alpha;
	}
}