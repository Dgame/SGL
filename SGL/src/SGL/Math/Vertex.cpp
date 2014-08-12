#include <SGL/Math/Vertex.hpp>

namespace sgl {
	Vertex::Vertex(float x, float y, float z) {
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	Vertex::Vertex(const vec3f& pos, const vec3f& texc, const Color4b& col) : position(pos), texcoord(texc) {
		this->setColor(col);
	}
}