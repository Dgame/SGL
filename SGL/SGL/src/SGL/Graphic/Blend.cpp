#include <SGL\Graphic\Blend.hpp>

namespace sgl {
	Blend::Blend(Factor psrc, Factor pdst) : src(psrc), dst(pdst) {

	}

	Blend::Blend(Factor psrc, Factor pdst, const Color& col) : src(psrc), dst(pdst), color(col) {

	}

	void Blend::apply() const {
		glBlendFunc(static_cast<GLenum>(this->src), static_cast<GLenum>(this->dst));

		//const std::array<float, 4> glcol = Color::InGLMode(this->color);
		//glColor4f(glcol[0], glcol[1], glcol[2], glcol[3]);
	}

	void Blend::Enable() {
		glEnable(GL_BLEND);
	}

	void Blend::Disable() {
		glDisable(GL_BLEND);
	}

	bool operator ==(const Blend& lhs, const Blend& rhs) {
		return lhs.src == rhs.src && lhs.dst == rhs.dst && lhs.color == rhs.color;
	}

	bool operator !=(const Blend& lhs, const Blend& rhs) {
		return !(lhs == rhs);
	}
}