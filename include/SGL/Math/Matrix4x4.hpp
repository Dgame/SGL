#ifndef SGL_MATRIX_HPP
#define SGL_MATRIX_HPP

#include <SGL/Math/Rect.hpp>
#include <SGL/Math/Vector2.hpp>
#include <SGL/Math/Vector3.hpp>

namespace sgl {
	struct Matrix4x4 {
		static const Matrix4x4 Identity;

		float values[16];

		Matrix4x4();
		Matrix4x4(float a00, float a01, float a02,
				  float a10, float a11, float a12,
				  float a20, float a21, float a22);
		Matrix4x4(const float values[16]);

		Matrix4x4 getInverse() const;

		void loadIdentity();

		float det() const;

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