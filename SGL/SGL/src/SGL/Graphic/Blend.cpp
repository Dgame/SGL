#include <SGL/Graphic/Blend.hpp>

namespace sgl {
	Blend::Blend(Factor psrc, Factor pdst, Equation peq) : src(psrc), dst(pdst), eq(peq) {

	}

	void Blend::apply() const {
		const GLColor gl_col = Color::InGLMode(this->color);
		glColor4f(gl_col.red, gl_col.green, gl_col.blue, gl_col.alpha);

		glBlendFunc(static_cast<GLenum>(this->src), static_cast<GLenum>(this->dst));
		glBlendEquation(static_cast<GLenum>(this->eq));
	}

	void Blend::Enable() {
		glEnable(GL_BLEND);
	}

	void Blend::Disable() {
		glDisable(GL_BLEND);
	}

	bool operator ==(const Blend& lhs, const Blend& rhs) {
		return lhs.src == rhs.src && lhs.dst == rhs.dst;
	}

	bool operator !=(const Blend& lhs, const Blend& rhs) {
		return !(lhs == rhs);
	}
}