#include <SGL/Graphic/Transformable.hpp>

namespace sgl {
	float Transformable::EnsureRotationRange(float rotation) {
		if (rotation > 360) {
			while (rotation > 360) {
				rotation -= 360;
			}
		} else if (rotation < 0) {
			while (rotation < 0) {
				rotation += 360;
			}
		}

		return rotation;
	}

	void Transform::_applyTransformation(float cx, float cy, float z) const {
		if (_rotation > 0 && _rotation < 360) {
			glTranslatef(cx, cy, 0);
			glRotatef(_rotation, 0, 0, z);
			glTranslatef(-cx, -cy, 0);
		}
	}
}