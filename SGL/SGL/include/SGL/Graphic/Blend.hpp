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

			OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR, /// (1,1,1,1) - (Rs/kR, Gs/kG, Bs/kB, As/kA)
			OneMinusDstColor = GL_ONE_MINUS_DST_COLOR, /// (1,1,1,1) - (Rd/kR, Gd/kG, Bd/kB, Ad/kA)
			OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA, /// (1,1,1,1) - (As/kA, As/kA, As/kA, As/kA)
			On_MinusDstAlpha = GL_ONE_MINUS_DST_ALPHA, /// (1,1,1,1) - (Ad/kA, Ad/kA, Ad/kA, Ad/kA)
		};

		enum class Equation {
			Add = GL_FUNC_ADD,
			Subtract = GL_FUNC_SUBTRACT,
			ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
			Max = GL_MAX,
			Min = GL_MIN
		};

		Factor src;
		Factor dst;
		Equation eq = Equation::Add;
		Color color = Color::White;

		explicit Blend(Factor src, Factor dst, Equation eq = Equation::Add);

		void apply() const;

		static void Enable();
		static void Disable();
	};

	bool operator ==(const Blend& lhs, const Blend& rhs);
	bool operator !=(const Blend& lhs, const Blend& rhs);
}

#endif