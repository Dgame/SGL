#include <SGL/Math/Vertex.hpp>

namespace sgl {
	Vertex::Vertex(float px, float py) : Vertex(px, py, 0, 0) {

	}

	Vertex::Vertex(float px, float py, float ptx, float pty) : x(px), y(py), tx(ptx), ty(pty) {
		setColor(Color::Black);
	}

	Vertex::Vertex(const Vector2f& coord, const Vector2f& texcoord) : Vertex(coord.x, coord.y, texcoord.x, texcoord.y) {

	}

	void Vertex::setColor(const Color& col) {
		this->r = col.red > 1 ? col.red / 255.f : col.red;
		this->g = col.green > 1 ? col.green / 255.f : col.green;
		this->b = col.blue > 1 ? col.blue / 255.f : col.blue;
		this->a = col.alpha > 1 ? col.alpha / 255.f : col.alpha;
	}
}