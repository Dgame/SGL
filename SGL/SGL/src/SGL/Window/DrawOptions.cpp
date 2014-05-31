#include <SGL/Window/DrawOptions.hpp>

namespace sgl {
	DrawOptions::DrawOptions(const Blend* bp) : blend(bp) {

	}
	
	DrawOptions::DrawOptions(const ShaderProgram* sp) : blend(nullptr), shader(sp) {

	}

	DrawOptions::DrawOptions(const Blend* bp, const ShaderProgram* sp) : blend(bp), shader(sp) {

	}
}