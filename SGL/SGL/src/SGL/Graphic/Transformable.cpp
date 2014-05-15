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
		const bool doRotate = _rotation > 0 && _rotation < 360;
		const bool doScale = _scale > 1.f || _scale < 1.f;

		if (doRotate || doScale)
			glTranslatef(cx, cy, 0);

		FunctionScope fs([=]() {
			if (doRotate || doScale)
				glTranslatef(-cx, -cy, 0);
		});
		
		if (doRotate)
			glRotatef(_rotation, 0, 0, z);
		if (doScale)
			glScalef(_scale, _scale, 0);
	}
}