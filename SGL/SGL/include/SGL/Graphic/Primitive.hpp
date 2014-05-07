#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <SGL/Core/OpenGL.hpp>
#include <SGL/Core/Types.hpp>

namespace sgl {
	struct Primitive {
		const float* vertices = nullptr;
		const float* color = nullptr;
		GLenum type = GL_QUADS;
		uint16 vcount = 0;
		uint16 vfirst = 0;
		uint16 offset = 0;

		explicit Primitive(const float* vp, const float* cp = nullptr, GLenum ty = GL_QUADS, uint16 vc = 4);
	};
}

#endif