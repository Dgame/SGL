#ifndef SGL_TRANSFORMABLE_HPP
#define SGL_TRANSFORMABLE_HPP

#include <SGL/Math/mat4.hpp>

namespace sgl {
	class Transformable {
	protected:
		vec2f _center;
		vec2f _position;

		float _scale = 1.f;
		float _rotation = 0.f;

	protected:
		void _updateTransform() {
			_update = true;
		}

	private:
		mutable mat4x4 _matrix;
		mutable bool _update = true;

	public:
		const mat4x4& getMatrix() const;
		
		void setPosition(float x, float y);
		void setPosition(const vec2f&);

		const vec2f& getPosition() const {
			return _position;
		}

		void setCenter(float x, float y);
		void setCenter(const vec2f&);

		const vec2f& getCenter() const {
			return _center;
		}

		void setScale(float scale);
		void scale(float scale);

		float getScale() const {
			return _scale;
		}

		void setRotation(float rotation);
		void rotate(float rotation);

		float getRotation() const {
			return _rotation;
		}
	};
}

#endif