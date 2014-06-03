#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <SGL/Graphic/Color.hpp>
#include <SGL/Math/Vector2.hpp>

namespace sgl {
	struct Vertex {
		/**
		* The coordinates
		*/
		float x, y;
		/**
		* The color components
		*/
		float r, g, b, a;
		/**
		* The texcoords
		*/
		float tx, ty;

		explicit Vertex(float _x, float _y);
		explicit Vertex(float _x, float _y, float _tx, float _ty);

		void setColor(const Color& col);

		Vector2f getPosition() const {
			return Vector2f(this->x, this->y);
		}

		Vector2f getTextureCoordinates() const {
			return Vector2f(this->tx, this->ty);
		}

		Color getColor() const {
			return Color(
				static_cast<uint8>(this->r * 255),
				static_cast<uint8>(this->g * 255),
				static_cast<uint8>(this->b * 255),
				static_cast<uint8>(this->a * 255));
		}
	};
}

#endif