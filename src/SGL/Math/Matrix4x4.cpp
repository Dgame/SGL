#include <cmath>
#include <SGL/Math/Matrix4x4.hpp>

namespace sgl {
	const Matrix4x4 Matrix4x4::Identity;

	Matrix4x4::Matrix4x4() {
		this->loadIdentity();
	}

	Matrix4x4::Matrix4x4(float a00, float a01, float a02,
						 float a10, float a11, float a12,
						 float a20, float a21, float a22)
	{
		this->values[0] = a00; this->values[4] = a01; this->values[8] = 0.f; this->values[12] = a02;
		this->values[1] = a10; this->values[5] = a11; this->values[9] = 0.f; this->values[13] = a12;
		this->values[2] = 0.f; this->values[6] = 0.f; this->values[10] = 1.f; this->values[14] = 0.f;
		this->values[3] = a20; this->values[7] = a21; this->values[11] = 0.f; this->values[15] = a22;
	}

	Matrix4x4 Matrix4x4::getInverse() const {
		const float det = this->det();

		if (det != 0.f) {
			return Matrix4x4((this->values[15] * this->values[5] - this->values[7] * this->values[13]) / det,
							 -(this->values[15] * this->values[4] - this->values[7] * this->values[12]) / det,
							 (this->values[13] * this->values[4] - this->values[5] * this->values[12]) / det,
							 -(this->values[15] * this->values[1] - this->values[3] * this->values[13]) / det,
							 (this->values[15] * this->values[0] - this->values[3] * this->values[12]) / det,
							 -(this->values[13] * this->values[0] - this->values[1] * this->values[12]) / det,
							 (this->values[7] * this->values[1] - this->values[3] * this->values[5]) / det,
							 -(this->values[7] * this->values[0] - this->values[3] * this->values[4]) / det,
							 (this->values[5] * this->values[0] - this->values[1] * this->values[4]) / det);
		} else
			return Identity;
	}

	void Matrix4x4::loadIdentity() {
		this->values[0] = 1.f; this->values[4] = 0.f; this->values[8] = 0.f; this->values[12] = 0.f;
		this->values[1] = 0.f; this->values[5] = 1.f; this->values[9] = 0.f; this->values[13] = 0.f;
		this->values[2] = 0.f; this->values[6] = 0.f; this->values[10] = 1.f; this->values[14] = 0.f;
		this->values[3] = 0.f; this->values[7] = 0.f; this->values[11] = 0.f; this->values[15] = 1.f;
	}

	float Matrix4x4::det() const {
		return this->values[0] * (this->values[15] * this->values[5] - this->values[7] * this->values[13]) -
			this->values[1] * (this->values[15] * this->values[4] - this->values[7] * this->values[12]) +
			this->values[3] * (this->values[13] * this->values[4] - this->values[5] * this->values[12]);
	}

	Matrix4x4& Matrix4x4::merge(const Matrix4x4& mat) {
		const float* a = this->values;
		const float* b = mat.values;

		*this = Matrix4x4(a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
						  a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
						  a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
						  a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
						  a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
						  a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
						  a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
						  a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
						  a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

		return *this;
	}

	Matrix4x4& Matrix4x4::translate(float x, float y) {
		Matrix4x4 translation(1, 0, x,
							  0, 1, y,
							  0, 0, 1);

		return this->merge(translation);
	}

	Matrix4x4& Matrix4x4::rotate(float angle) {
		const float rad = angle * 3.141592654f / 180.f;
		const float cos = std::cos(rad);
		const float sin = std::sin(rad);

		Matrix4x4 rotation(cos, -sin, 0,
						   sin, cos, 0,
						   0, 0, 1);

		return this->merge(rotation);
	}

	Matrix4x4& Matrix4x4::rotate(float angle, float centerX, float centerY) {
		const float rad = angle * 3.141592654f / 180.f;
		const float cos = std::cos(rad);
		const float sin = std::sin(rad);

		Matrix4x4 rotation(cos, -sin,
						   centerX * (1 - cos) + centerY * sin,
						   sin, cos,
						   centerY * (1 - cos) - centerX * sin,
						   0, 0, 1);

		return this->merge(rotation);
	}

	Matrix4x4& Matrix4x4::scale(float scaleX, float scaleY) {
		Matrix4x4 scaling(scaleX, 0, 0,
						  0, scaleY, 0,
						  0, 0, 1);

		return this->merge(scaling);
	}

	Matrix4x4& Matrix4x4::scale(float scaleX, float scaleY, float centerX, float centerY) {
		Matrix4x4 scaling(scaleX, 0,
						  centerX * (1 - scaleX),
						  0, scaleY,
						  centerY * (1 - scaleY),
						  0, 0, 1);

		return this->merge(scaling);
	}

	void Matrix4x4::lookAt(float x, float y, float z, float xlook, float ylook, float zlook, float xup, float yup, float zup)
	{
		Vector3f eye(x, y, z);
		Vector3f up(xup, yup, zup);

		Vector3f dir;
		dir.x = (xlook - x);
		dir.y = (ylook - y);
		dir.z = (zlook - z);
		dir.normalize();

		Vector3f right = dir.cross(up);
		right.normalize();

		up = right.cross(dir);
		up.normalize();

		Matrix4x4 mat;
		mat.values[0] = right.x;
		mat.values[4] = right.y;
		mat.values[8] = right.z;
		mat.values[12] = -right.dot(eye);

		mat.values[1] = up.x;
		mat.values[5] = up.y;
		mat.values[9] = up.z;
		mat.values[13] = -up.dot(eye);

		mat.values[2] = -dir.x;
		mat.values[6] = -dir.y;
		mat.values[10] = -dir.z;
		mat.values[14] = dir.dot(eye);

		mat.values[3] = 0;
		mat.values[7] = 0;
		mat.values[11] = 0;
		mat.values[15] = 1;

		this->merge(mat);
	}

	void Matrix4x4::perspective(float fov, float ratio, float nearp, float farp) {
		const float f = 1.0f / std::tan(fov * (M_PI / 360));

		Matrix4x4 mat;
		mat.values[0] = f / ratio;
		mat.values[5] = f;
		mat.values[10] = (farp + nearp) / (nearp - farp);
		mat.values[11] = -1;
		mat.values[14] = (2 * farp*nearp) / (nearp - farp);
		mat.values[15] = 0;

		this->merge(mat);
	}

	void Matrix4x4::ortho(int16 left, int16 right, int16 bottom, int16 top, float nearp, float farp) {
		if (left != right && bottom != top && nearp != farp) {
			Matrix4x4 mat;
			mat.values[0] = 2.0f / (right - left);
			mat.values[5] = 2.0f / (top - bottom);
			mat.values[10] = -2.0f / (farp - nearp);
			mat.values[12] = static_cast<float>(-(right + left)) / (right - left);
			mat.values[13] = static_cast<float>(-(top + bottom)) / (top - bottom);
			mat.values[14] = static_cast<float>(-(farp + nearp)) / (farp - nearp);
			mat.values[15] = 1;

			this->merge(mat);
		}
	}

	float& Matrix4x4::operator [](uint8 index) {
		return this->values[index];
	}

	bool operator ==(const Matrix4x4& lhs, const Matrix4x4& rhs) {
		return lhs.values[0] == rhs.values[0] &&
			lhs.values[1] == rhs.values[1] &&
			lhs.values[2] == rhs.values[2] &&
			lhs.values[3] == rhs.values[3] &&

			lhs.values[4] == rhs.values[4] &&
			lhs.values[5] == rhs.values[5] &&
			lhs.values[6] == rhs.values[6] &&
			lhs.values[7] == rhs.values[7] &&

			lhs.values[8] == rhs.values[8] &&
			lhs.values[9] == rhs.values[9] &&
			lhs.values[10] == rhs.values[10] &&
			lhs.values[11] == rhs.values[11] &&

			lhs.values[12] == rhs.values[12] &&
			lhs.values[13] == rhs.values[13] &&
			lhs.values[14] == rhs.values[14] &&
			lhs.values[15] == rhs.values[15];
	}

	bool operator !=(const Matrix4x4& lhs, const Matrix4x4& rhs) {
		return !(lhs == rhs);
	}

	Matrix4x4 operator *(const Matrix4x4& left, const Matrix4x4& right) {
		return Matrix4x4(left).merge(right);
	}

	Matrix4x4& operator *=(Matrix4x4& left, const Matrix4x4& right) {
		return left.merge(right);
	}

	std::ostream& operator <<(std::ostream& strm, const Matrix4x4& mat) {
		strm << "Matrix4x4" << '(' << std::endl;
		for (uint8 i = 0; i < 16; i++) {
			strm << "\t" << mat.values[i];
			if (i < 15)
				strm << ',';
			if ((i + 1) % 4 == 0)
				strm << std::endl;
		}
		strm << ')';

		return strm;
	}
}