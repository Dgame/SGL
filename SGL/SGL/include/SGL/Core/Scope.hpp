#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <functional>
#include <SGL/Core/OpenGL.hpp>

using std::function;

namespace sgl {
	struct GLMatrixScope {
		explicit GLMatrixScope() {
			glPushMatrix();
		}

		~GLMatrixScope() {
			glPopMatrix();
		}
	};

	struct GLAttribScope {
		explicit GLAttribScope(GLbitfield mask) {
			glPushAttrib(mask);
		}

		~GLAttribScope() {
			glPopAttrib();
		}
	};

	struct FunctionScope {
		std::function<void(void)> func;
		bool call = true;

		explicit FunctionScope(std::function<void(void)> pfunc) : func(pfunc) {

		}

		~FunctionScope() {
			if (this->call)
				this->func();
		}
	};
}

#endif