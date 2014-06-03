#include <SGL/Graphic/Primitive.hpp>

namespace sgl {
	Primitive::Primitive(const float* vp, const float* cp, GLenum ty, uint16 vc) : vertices(vp), color(cp), type(ty), vcount(vc) {

	}
}