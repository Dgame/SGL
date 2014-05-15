#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <SGL/Core/OpenGL.hpp>
#include <SGL/Core/Scope.hpp>
#include <SGL/Math/Vector2.hpp>

namespace sgl {
	class Transformable {
	protected:
		float _rotation = 0;
		float _scale = 1;

		static float EnsureRotationRange(float rotation);

	public:
		virtual ~Transformable() {

		}

		virtual void setScale(float scale) {
			_scale = scale;
		}

		virtual void scale(float scale) {
			_scale += scale;
		}

		float getScale() const {
			return _scale;
		}

		virtual void setRotation(float rotation) {
			_rotation = EnsureRotationRange(rotation);
		}

		virtual void rotate(float angle) {
			_rotation += angle;
			_rotation = EnsureRotationRange(_rotation);
		}

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
	};

	class GraphTransform : public Transform {
	protected:
		void _applyTransformation() const {
			Transform::_applyTransformation(this->center.x, this->center.y);
		}

	public:
		Vector2f center;

		virtual ~GraphTransform() {

		}

		virtual void calculateCenter() {

		}
	};
}

#endif