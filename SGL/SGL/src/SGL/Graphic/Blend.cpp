#include <SGL/Graphic/Blend.hpp>

namespace sgl {
	Blend::Blend(Factor psrc, Factor pdst) : src(psrc), dst(pdst) {

	}

	void Blend::apply() const {
		glBlendFunc(static_cast<GLenum>(this->src), static_cast<GLenum>(this->dst));
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