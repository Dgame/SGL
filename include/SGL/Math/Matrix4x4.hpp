#ifndef SGL_MATRIX_HPP
#define SGL_MATRIX_HPP

#include <SGL/Math/Rect.hpp>
#include <SGL/Math/Vector2.hpp>
#include <SGL/Math/Vector3.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace sgl {
	struct Matrix4x4 {
		static const Matrix4x4 Identity;

		float values[16];

		Matrix4x4();
		Matrix4x4(float a00, float a01, float a02,
				  float a10, float a11, float a12,
				  float a20, float a21, float a22);
		Matrix4x4(const float values[]);

		Matrix4x4 getInverse() const;

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

		Matrix4x4& merge(const Matrix4x4& mat);
		Matrix4x4& translate(float x, float y);

		Matrix4x4& translate(const Vector2f& offset) {
			return this->translate(offset.x, offset.y);
		}

		Matrix4x4& rotate(float angle);
		Matrix4x4& rotate(float angle, float centerX, float centerY);

		Matrix4x4& rotate(float angle, const Vector2f& center) {
			return this->rotate(angle, center.x, center.y);
		}

		Matrix4x4& scale(float scaleX, float scaleY);
		Matrix4x4& scale(float scaleX, float scaleY, float centerX, float centerY);

		Matrix4x4& scale(const Vector2f& factors) {
			return this->scale(factors.x, factors.y);
		}

		Matrix4x4& scale(const Vector2f& factors, const Vector2f& center) {
			return this->scale(factors.x, factors.y, center.x, center.y);
		}

		void lookAt(float x, float y, float z, float xlook, float ylook, float zlook, float xup, float yup, float zup);

		void lookAt(const Vector3f& vec, const Vector3f& look, const Vector3f& up) {
			this->lookAt(vec.x, vec.y, vec.z, look.x, look.y, look.z, up.x, up.y, up.z);
		}

		void perspective(float fov, float ratio, float nearp, float farp);
		void ortho(int16 left, int16 right, int16 bottom, int16 top, float nearp, float farp);

		float& operator [](uint8 index);
	};

	bool operator ==(const Matrix4x4& lhs, const Matrix4x4& rhs);
	bool operator !=(const Matrix4x4& lhs, const Matrix4x4& rhs);

	Matrix4x4 operator *(const Matrix4x4& left, const Matrix4x4& right);
	Matrix4x4& operator *=(Matrix4x4& left, const Matrix4x4& right);

	std::ostream& operator <<(std::ostream& strm, const Matrix4x4& mat);
}

#endif