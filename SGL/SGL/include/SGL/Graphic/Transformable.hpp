#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <SGL\Core\OpenGL.hpp>
#include <SGL\Math\Vector2.hpp>

namespace sgl {
	class Transformable {
	protected:
		float _rotation = 0;

		static float EnsureRotationRange(float rotation);

	public:
		virtual ~Transformable() {

		}

		virtual void setRotation(float rotation) = 0;
		virtual void rotate(float angle) = 0;

		float getRotation() const {
			return _rotation;
		}
	};

	class Transform : public Transformable {
	protected:
		void _applyTransformation(float cx, float cy, float z = 1) const;

	public:
		virtual ~Transform() {

		}

		void setRotation(float rotation) override {
			_rotation = EnsureRotationRange(rotation);
		}

		void rotate(float angle) override {
			_rotation += angle;
			_rotation = EnsureRotationRange(_rotation);
		}
	};
}

#endif