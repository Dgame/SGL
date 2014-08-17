#ifndef SGL_VERTEX_HPP
#define SGL_VERTEX_HPP

#include <SGL/Math/vec3.hpp>
#include <SGL/Graphic/Color.hpp>

namespace sgl {
	struct Vertex {
		vec3f position;
		vec3f texCoord;
		Color4f color = Color4f::Black;

		explicit Vertex(float x, float y, float z = 0);
		explicit Vertex(const vec3f&, const vec3f&, const Color4b&);

		void setColor(const Color4b& col) {
			this->color = Color4f(col);
		}
	};
}

#endif