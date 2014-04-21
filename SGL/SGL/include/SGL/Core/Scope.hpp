#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <SGL\Core\OpenGL.hpp>

namespace sgl {
	struct glMatrixScope {
		explicit glMatrixScope() {
			glPushMatrix();
		}

		virtual ~glMatrixScope() {
			glPopMatrix();
		}
	};

	struct glAttribScope {
		explicit glAttribScope(GLbitfield mask) {
			glPushAttrib(mask);
		}

		virtual ~glAttribScope() {
			glPopAttrib();
		}
	};
}

#endif