#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Core/Config.hpp>

namespace sgl {
	void Transformable::_update(Update which) {
		if (which == Update::Rotation) {
			_rotation = static_cast<float>(fmod(_rotation, 360));
			if (_rotation < 0)
				_rotation += 360;
		}

		_updateMode = which;
	}

	const mat4x4& Transformable::getMatrix() const {
		if (_updateMode != Update::None) {
			_matrix.loadIdentity();
			if (_updateMode & Update::Rotation)
				_matrix.rotate(_rotation, _center);
			if (_updateMode & Update::Scale)
				_matrix.scale(_scale, _center);
			if (_updateMode & Update::Position)
				_matrix.translate(_position);

			_updateMode = Update::None;
#if SGL_DEBUG
			printf("Update Transform Matrix\n");
#endif
		}

		return _matrix;
	}

	void Transformable::setPosition(float x, float y) {
		_position.x = x;
		_position.y = y;

		_update(Update::Position);
	}

	void Transformable::setPosition(const vec2f& pos) {
		_position = pos;

		_update(Update::Position);
	}

	void Transformable::setCenter(const vec2f& center) {
		_center = center;
		_update(Update::Center);
	}

	void Transformable::setCenter(float x, float y) {
		_center.x = x;
		_center.y = y;
		_update(Update::Center);
	}

	void Transformable::setScale(float scale) {
		_scale = scale;
		_update(Update::Scale);
	}

	void Transformable::scale(float scale) {
		_scale += scale;
		_update(Update::Scale);
	}

	void Transformable::setRotation(float rotation) {
		_rotation = rotation;
		_update(Update::Rotation);
	}

	void Transformable::rotate(float rotation) {
		_rotation += rotation;
		_update(Update::Rotation);
	}
}