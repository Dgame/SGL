#ifndef BLEND_HPP
#define BLEND_HPP

#include <SGL/Core/OpenGL.hpp>
#include <SGL/Graphic/Color.hpp>

namespace sgl {
	struct Blend {
		enum class Factor {
			Zero = GL_ZERO, /// (0,0,0,0)
			One = GL_ONE, /// (1,1,1,1)
			SrcColor = GL_SRC_COLOR, /// (Rs/kR, Gs/kG, Bs/kB, As/kA)
			DstColor = GL_DST_COLOR, /// Rd/kR, Gd/kG, Bd/kB, Ad/kA)
			SrcAlpha = GL_SRC_ALPHA, /// (As/kA, As/kA, As/kA, As/kA)
			DstAlpha = GL_DST_ALPHA, /// (Ad/kA, Ad/kA, Ad/kA, Ad/kA)
			AlphaSaturate = GL_SRC_ALPHA_SATURATE, /// (i,i,i,1)

			OneMinus_SrcColor = GL_ONE_MINUS_SRC_COLOR, /// (1,1,1,1) - (Rs/kR, Gs/kG, Bs/kB, As/kA)
			OneMinus_DstColor = GL_ONE_MINUS_DST_COLOR, /// (1,1,1,1) - (Rd/kR, Gd/kG, Bd/kB, Ad/kA)
			OneMinus_SrcAlpha = GL_ONE_MINUS_SRC_ALPHA, /// (1,1,1,1) - (As/kA, As/kA, As/kA, As/kA)
			OneMinus_DstAlpha = GL_ONE_MINUS_DST_ALPHA, /// (1,1,1,1) - (Ad/kA, Ad/kA, Ad/kA, Ad/kA)
		};

		Factor src;
		Factor dst;

		explicit Blend(Factor src, Factor dst);

		void apply() const;

		static void Enable();
		static void Disable();
	};

	bool operator ==(const Blend& lhs, const Blend& rhs);
	bool operator !=(const Blend& lhs, const Blend& rhs);
}

#endif