#include <cmath>
#include <limits>
#include <SGL/Math/mat4.hpp>

namespace {
    inline bool feq(float a, float b) {
        return std::fabs(a - b) > std::numeric_limits<float>::epsilon();
    }
}

namespace sgl {
	const mat4x4 mat4x4::Identity;

	mat4x4::mat4x4() {
		this->loadIdentity();
	}

	mat4x4::mat4x4(float a00, float a01, float a02,
				   float a10, float a11, float a12,
				   float a20, float a21, float a22) {
		this->values[0] = a00; this->values[4] = a01; this->values[8] = 0.f; this->values[12] = a02;
		this->values[1] = a10; this->values[5] = a11; this->values[9] = 0.f; this->values[13] = a12;
		this->values[2] = 0.f; this->values[6] = 0.f; this->values[10] = 1.f; this->values[14] = 0.f;
		this->values[3] = a20; this->values[7] = a21; this->values[11] = 0.f; this->values[15] = a22;
	}

	mat4x4 mat4x4::getInverse() const {
		const float det = this->det();

		if (det > 0.0f) {
			return mat4x4((this->values[15] * this->values[5] - this->values[7] * this->values[13]) / det,
						  -(this->values[15] * this->values[4] - this->values[7] * this->values[12]) / det,
						  (this->values[13] * this->values[4] - this->values[5] * this->values[12]) / det,
						  -(this->values[15] * this->values[1] - this->values[3] * this->values[13]) / det,
						  (this->values[15] * this->values[0] - this->values[3] * this->values[12]) / det,
						  -(this->values[13] * this->values[0] - this->values[1] * this->values[12]) / det,
						  (this->values[7] * this->values[1] - this->values[3] * this->values[5]) / det,
						  -(this->values[7] * this->values[0] - this->values[3] * this->values[4]) / det,
						  (this->values[5] * this->values[0] - this->values[1] * this->values[4]) / det);
		}

		return Identity;
	}

	mat4x4& mat4x4::translate(const vec2f& vec) {
		mat4x4 translation(1, 0, vec.x,
						   0, 1, vec.y,
						   0, 0, 1);

		return Merge(*this, translation);
	}

	mat4x4& mat4x4::rotate(float angle) {
		const float rad = static_cast<float>(angle * M_PI / 180.f);
		const float cos = std::cos(rad);
		const float sin = std::sin(rad);

		mat4x4 rotation(cos, -sin, 0,
						sin, cos, 0,
						0, 0, 1);

		return Merge(*this, rotation);
	}

	mat4x4& mat4x4::rotate(float angle, const vec2f& center) {
		const float rad = static_cast<float>(angle * M_PI / 180.f);
		const float cos = std::cos(rad);
		const float sin = std::sin(rad);

		mat4x4 rotation(cos, -sin, center.x * (1 - cos) + center.y * sin, +
						sin, cos, center.y * (1 - cos) - center.x * sin,
						0, 0, 1);

		return Merge(*this, rotation);
	}

	mat4x4& mat4x4::scale(float scale) {
		mat4x4 scaling(scale, 0, 0,
					   0, scale, 0,
					   0, 0, 1);

		return Merge(*this, scaling);
	}

	mat4x4& mat4x4::scale(float scale, const vec2f& center) {
		mat4x4 scaling(scale, 0, center.x * (1 - scale),
					   0, scale, center.y * (1 - scale),
					   0, 0, 1);

		return Merge(*this, scaling);
	}

	void mat4x4::lookAt(const vec3f& eye, const vec3f& look, const vec3f& up) {
		const vec3f dir = Normalize(look - eye);
		const vec3f right = Normalize(Cross(dir, up));
		const vec3f up2 = Normalize(Cross(right, dir));

		mat4x4 mat;
		mat.values[0] = right.x;
		mat.values[4] = right.y;
		mat.values[8] = right.z;
		mat.values[12] = -Dot(right, eye);

		mat.values[1] = up2.x;
		mat.values[5] = up2.y;
		mat.values[9] = up2.z;
		mat.values[13] = -Dot(up2, eye);

		mat.values[2] = -dir.x;
		mat.values[6] = -dir.y;
		mat.values[10] = -dir.z;
		mat.values[14] = Dot(dir, eye);

		mat.values[3] = 0;
		mat.values[7] = 0;
		mat.values[11] = 0;
		mat.values[15] = 1;

		Merge(*this, mat);
	}

	void mat4x4::perspective(float fov, float ratio, float nearp, float farp) {
		const float f = static_cast<float>(1.0f / std::tan(fov * (M_PI / 360)));

		mat4x4 mat;
		mat.values[0] = f / ratio;
		mat.values[5] = f;
		mat.values[10] = (farp + nearp) / (nearp - farp);
		mat.values[11] = -1;
		mat.values[14] = (2 * farp*nearp) / (nearp - farp);
		mat.values[15] = 0;

		Merge(*this, mat);
	}

	bool mat4x4::ortho(const ShortRect& rect, float zNear, float zFar) {
		if (!rect.isEmpty()) {
			mat4x4 mat;
			const float inv_z = 1.0f / (zFar - zNear);
			const float inv_y = 1.0f / (rect.x - rect.height);
			const float inv_x = 1.0f / (rect.width - rect.y);
			// first column
			mat[0] = 2.0f * inv_x;
			// second
			mat[5] = 2.0f * inv_y;
			// third
			mat[10] = -2.0f * inv_z;
			// fourth
			mat[12] = -(rect.width + rect.y) * inv_x;
			mat[13] = -(rect.x + rect.height) * inv_y;
			mat[14] = -(zFar + zNear) * inv_z;

			Merge(*this, mat);

			return true;
		}

		return false;
	}

	float& mat4x4::operator [](uint8 index) {
		return this->values[index];
	}

	bool operator ==(const mat4x4& lhs, const mat4x4& rhs) {
		for (uint8 i = 0; i < 16; i++) {
            if (!feq(lhs.at(i), rhs.at(i)))
                return false;
		}

		return true;
	}

	bool operator !=(const mat4x4& lhs, const mat4x4& rhs) {
		return !(lhs == rhs);
	}

	mat4x4& Merge(mat4x4& lhs, const mat4x4& rhs) {
		lhs = mat4x4(
			lhs.at(0) * rhs.at(0) + lhs.at(4) * rhs.at(1) + lhs.at(12) * rhs.at(3),
			lhs.at(0) * rhs.at(4) + lhs.at(4) * rhs.at(5) + lhs.at(12) * rhs.at(7),
			lhs.at(0) * rhs.at(12) + lhs.at(4) * rhs.at(13) + lhs.at(12) * rhs.at(15),
			lhs.at(1) * rhs.at(0) + lhs.at(5) * rhs.at(1) + lhs.at(13) * rhs.at(3),
			lhs.at(1) * rhs.at(4) + lhs.at(5) * rhs.at(5) + lhs.at(13) * rhs.at(7),
			lhs.at(1) * rhs.at(12) + lhs.at(5) * rhs.at(13) + lhs.at(13) * rhs.at(15),
			lhs.at(3) * rhs.at(0) + lhs.at(7) * rhs.at(1) + lhs.at(15) * rhs.at(3),
			lhs.at(3) * rhs.at(4) + lhs.at(7) * rhs.at(5) + lhs.at(15) * rhs.at(7),
			lhs.at(3) * rhs.at(12) + lhs.at(7) * rhs.at(13) + lhs.at(15) * rhs.at(15));

		return lhs;
	}

	mat4x4 operator *(const mat4x4& left, const mat4x4& right) {
		mat4x4 cpy(left);
		Merge(cpy, right);

		return cpy;
	}

	mat4x4& operator *=(mat4x4& left, const mat4x4& right) {
		return Merge(left, right);
	}
}
