#ifndef SGL_SHAPE_HPP
#define SGL_SHAPE_HPP

#include <algorithm>
#include <vector>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Math/Vertex.hpp>
#include <SGL/Math/Geometry.hpp>

namespace sgl {
	class Texture;

	class Shape : public Drawable, public Transformable {
	private:
		Texture* _texture = nullptr;
		std::vector<Vertex> _vertices;

	protected:
		virtual void draw(const Window*) const override;

	public:
		Geometry::Type geometry;

		explicit Shape(Geometry::Type geo);

		void append(const Vertex&);
		void setTexture(Texture*, const FloatRect* texRect = nullptr);

		const Texture* getTexture() const {
			return _texture;
		}

		void setTextureRect(const FloatRect&);
		FloatRect getBoundingRect() const;

		const std::vector<Vertex>& getVertices() const {
			return _vertices;
		}

		void setColor(const Color4b&);

		void move(float x, float y) override;
		void move(const vec2f&) override;
	};
}

#endif