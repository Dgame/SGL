#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Core/Config.hpp>

namespace sgl {
	const mat4x4& Transformable::getMatrix() const {
		if (_update) {
			_matrix.loadIdentity().rotate(_rotation, _center).scale(_scale, _center).translate(_position);
			_update = false;
#if SGL_DEBUG
			printf("Update Transform Matrix\n");
#endif
		}

		return _matrix;
	}

	void Transformable::setPosition(float x, float y) {
		_position.x = x;
		_position.y = y;

		_update = true;
		_center = _position;
	}

	void Transformable::setPosition(const vec2f& pos) {
		_position = pos;

		_update = true;
		_center = _position;
	}

	void Transformable::move(float x, float y) {
		_center.x += x;
		_center.y += y;
	}

	void Transformable::move(const vec2f& vec) {
		_center += vec;
	}

	void Transformable::setCenter(const vec2f& center) {
		_center = center;
		_update = true;
	}

	void Transformable::setCenter(float x, float y) {
		_center.x = x;
		_center.y = y;

		_update = true;
	}

	void Transformable::setScale(float scale) {
		_scale = scale;
		_update = true;
	}

	void Transformable::scale(float scale) {
		_scale += scale;
		_update = true;
	}

	void Transformable::setRotation(float rotation) {
		_rotation = rotation;
		_rotation = static_cast<float>(fmod(_rotation, 360));
		if (_rotation < 0)
			_rotation += 360;

		_update = true;
	}

	void Transformable::rotate(float rotation) {
		_rotation += rotation;
		_rotation = static_cast<float>(fmod(_rotation, 360));
		if (_rotation < 0)
			_rotation += 360;

		_update = true;
	}
}