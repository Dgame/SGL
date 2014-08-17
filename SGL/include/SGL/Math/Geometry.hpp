#ifndef SGL_GEOMETRY_HPP
#define SGL_GEOMETRY_HPP

#include <SGL/Core/GL.hpp>

namespace sgl {
	enum class Geometry {
		Quad = GL_QUADS,
		QuadStrip = GL_QUAD_STRIP,
		Line = GL_LINE,
		LineLoop = GL_LINE_STRIP,
		Triangle = GL_TRIANGLES,
		TriangleFan = GL_TRIANGLE_FAN,
		TriangleStrip = GL_TRIANGLE_STRIP,
		Polygon = GL_POLYGON
	};
};

#endif