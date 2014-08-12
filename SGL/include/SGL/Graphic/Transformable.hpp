#ifndef SGL_TRANSFORMABLE_HPP
#define SGL_TRANSFORMABLE_HPP

#include <SGL/Math/mat4.hpp>

namespace sgl {
	class Transformable {
	protected:
		enum class Update : char {
			Position,
			Center,
			Rotation,
			Scale
		};

		virtual void _update(Update which);

		vec2f _center;
		vec2f _position;

		float _scale = 1;
		float _rotation = 0;

	private:
		mutable mat4x4 _matrix;
		mutable bool _needUpdate = false;

	public:
		const mat4x4& getMatrix() const;

		void setPosition(const vec2f&);
		void setPosition(float x, float y);

		void move(float x, float y);
		void move(const vec2f&);

		const vec2f& getPosition() const {
			return _position;
		}

		void setCenter(const vec2f&);
		void setCenter(float x, float y);

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