#ifndef SGL_SHAPE_HPP
#define SGL_SHAPE_HPP

#include <algorithm>
#include <vector>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Math/Vertex.hpp>

namespace sgl {
	class Shape : public Drawable, public Transformable {
	protected:
		virtual void _update(Update which) override;
		virtual void draw(const Window*) const override;

	public:
		Geometry geometry;
		std::vector<Vertex> vertices;
		Texture* texture = nullptr;

		explicit Shape(Geometry geo);

		void setColor(const Color4b&);

		void move(float x, float y);
		void move(const vec2f&);
	};
}

#endif