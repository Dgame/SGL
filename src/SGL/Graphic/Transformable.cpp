#include <SGL/Graphic/Transformable.hpp>

namespace sgl {
	void Transformable::applyTransformation() const {
		if (_update) {
			const Vector2f center = _viewport.getCenterPoint();

			_transform.loadIdentity();
			_transform.rotate(_rotation, center);

			if (_scale > 1.0f || _scale < 1.0f)
				_transform.scale(_scale, _scale, center.x, center.y);

			_update = false;
#if SGL_DEBUG
			printf("Update Transform\n");
#endif
		}

		glCheck(glLoadMatrixf(_transform.values));
	}

	void Transformable::setViewport(float x, float y, float w, float h) {
		_viewport.setPosition(x, y);
		_viewport.setSize(w, h);

		_syncronizePosition();
	}

	void Transformable::setRotation(float angle) {
		_rotation = static_cast<float>(std::fmod(angle, 360));
		if (_rotation < 0)
			_rotation += 360;
		_update = true;
	}
}