#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <SGL/Core/OpenGL.hpp>
#include <SGL/Math/Vector2.hpp>
#include <SGL/Math/Matrix4x4.hpp>

namespace sgl {
	class Transformable {
	protected:
		mutable Matrix4x4 _transform;
		mutable bool _update = false;

		FloatRect _viewport;
		Vector2f _position;

		float _rotation = 0;
		float _scale = 1;

	private:
		void _syncronizeViewport() {
			_viewport.setPosition(_position);
			_update = true;
		}

		void _syncronizePosition() {
			_position.set(_viewport.x, _viewport.y);
			_update = true;
		}

	public:
		virtual ~Transformable() {

		}

		void applyTransformation() const;

		const Matrix4x4& getMatrix() const {
			return _transform;
		}

		void move(float x, float y) {
			_position.move(x, y);
			
			_syncronizeViewport();
		}

		void move(const Vector2f& vec) {
			_position += vec;
			
			_syncronizeViewport();
		}

		void setPosition(float x, float y) {
			_position.set(x, y);
			
			_syncronizeViewport();
		}

		void setPosition(const Vector2f& vec) {
			_position = vec;

			_syncronizeViewport();
		}

		const Vector2f& getPosition() const {
			return _position;
		}

		void setViewport(const FloatRect& viewport) {
			_viewport = viewport;

			_syncronizePosition();
		}

		void setViewport(float x, float y, float w, float h);

		const FloatRect& getViewport() const {
			return _viewport;
		}

		void setScale(float scale) {
			_scale = scale;
			_update = true;
		}

		void scale(float scale) {
			_scale += scale;
			_update = true;
		}

		float getScale() const {
			return _scale;
		}

		void setRotation(float angle);

		void rotate(float angle) {
			this->setRotation(_rotation + angle);
			_update = true;
		}

		float getRotation() const {
			return _rotation;
		}
	};
}

#endif