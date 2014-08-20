#ifndef SGL_TRANSFORMABLE_HPP
#define SGL_TRANSFORMABLE_HPP

#include <SGL/Math/mat4.hpp>

namespace sgl {
	class Transformable {
	protected:
		enum Update : char {
			None = 0,
			Position = 1,
			Center = 2,
			Rotation = 4,
			Scale = 8
		};

		virtual void _update(Update which);

		vec2f _center;
		vec2f _position;

		float _scale = 1;
		float _rotation = 0;

	private:
		mutable mat4x4 _matrix;
		mutable Update _updateMode = Update::None;

	public:
		const mat4x4& getMatrix() const;
		
		virtual void setPosition(float x, float y);
		virtual void setPosition(const vec2f&);

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