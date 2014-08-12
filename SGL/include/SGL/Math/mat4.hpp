#ifndef SGL_MATRIX_HPP
#define SGL_MATRIX_HPP

#include <algorithm>
#include <SGL/Math/vec2.hpp>
#include <SGL/Math/vec3.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	struct mat4x4 {
		static const mat4x4 Identity;

		float values[16];

		mat4x4();
		explicit mat4x4(float a00, float a01, float a02,
						float a10, float a11, float a12,
						float a20, float a21, float a22);

		mat4x4 getInverse() const;

		void loadIdentity() {
			this->values[0] = 1.f; this->values[4] = 0.f; this->values[8] = 0.f; this->values[12] = 0.f;
			this->values[1] = 0.f; this->values[5] = 1.f; this->values[9] = 0.f; this->values[13] = 0.f;
			this->values[2] = 0.f; this->values[6] = 0.f; this->values[10] = 1.f; this->values[14] = 0.f;
			this->values[3] = 0.f; this->values[7] = 0.f; this->values[11] = 0.f; this->values[15] = 1.f;
		}

		float det() const {
			return this->values[0] * (this->values[15] * this->values[5] - this->values[7] * this->values[13]) -
				this->values[1] * (this->values[15] * this->values[4] - this->values[7] * this->values[12]) +
				this->values[3] * (this->values[13] * this->values[4] - this->values[5] * this->values[12]);
		}

		mat4x4& translate(const vec2f&);

		mat4x4& rotate(float angle);
		mat4x4& rotate(float angle, const vec2f&);

		mat4x4& scale(float scale);
		mat4x4& scale(float scale, const vec2f&);

		void lookAt(const vec3f&, const vec3f&, const vec3f&);

		void perspective(float fov, float ratio, float nearp, float farp);
		bool ortho(const ShortRect&, float nearp = 1, float farp = -1);

		float& operator [](uint8 index);

		float at(uint8 index) const {
			return this->values[index];
		}
	};

	bool operator ==(const mat4x4& lhs, const mat4x4&);
	bool operator !=(const mat4x4& lhs, const mat4x4&);

	mat4x4& Merge(mat4x4&, const mat4x4&);
	mat4x4 Construct(float rotation, float scale, const vec2f&, const vec2f&);

	mat4x4 operator *(const mat4x4&, const mat4x4& right);
	mat4x4& operator *=(mat4x4&, const mat4x4& right);
}

#endif