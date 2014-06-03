#ifndef SMOOTH_HPP
#define SMOOTH_HPP

#include <SGL/Core/OpenGL.hpp>

namespace sgl {
	struct Smooth {
		enum class Target {
			None = 0,
			Line = GL_LINE_SMOOTH_HINT,
			Point = GL_POINT_SMOOTH_HINT,
			Polygon = GL_POLYGON_SMOOTH_HINT
		};

		enum class Mode {
			Fastest = GL_FASTEST,
			Nicest = GL_NICEST
		};

		Target target = Target::None;
		Mode mode = Mode::Fastest;

		void set(Target target, Mode mode) {
			this->target = target;
			this->mode = mode;
		}
	};

	bool operator ==(const Smooth& lhs, const Smooth& rhs);
	bool operator !=(const Smooth& lhs, const Smooth& rhs);
}

#endif