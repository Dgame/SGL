#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <SGL/Core/Scope.hpp>
#include <SGL/Core/Range.hpp>
#include <SGL/Math/Vertex.hpp>
#include <SGL/Math/Rect.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Primitive.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Graphic/Smooth.hpp>

namespace sgl {
	class Texture;

	class Shape : public Drawable, public GraphTransform {
	protected:
		virtual void draw(const Window& wnd) const override;

	public:
		enum class Type {
			Quad = GL_QUADS,			/** Declare that the stored vertices are Quads. */
			QuadStrip = GL_QUAD_STRIP,	/** Declare that the stored vertices are Quad Strips*/
			Triangle = GL_TRIANGLES,	/** Declare that the stored vertices are Triangles. */
			TriangleStrip = GL_TRIANGLE_STRIP,	/** Declare that the stored vertices are Triangles Strips */
			TriangleFan = GL_TRIANGLE_FAN,		/** Declare that the stored vertices are Triangles Fans. */
			Lines = GL_LINES,			/** Declare that the stored vertices are Lines. */
			LineStrip = GL_LINE_STRIP,	/** Declare that the stored vertices are Line Strips. */
			LineLoop = GL_LINE_LOOP,	/** Declare that the stored vertices are Line Loops. */
			Polygon = GL_POLYGON,		/** Declare that the stored vertices are Polygons. */
		};

		std::vector<Vertex> vertices;
		Texture* texture = nullptr;
		Type type;
		uint8 lineWidth = 1;
		bool fill = false;
		Smooth smooth;

		explicit Shape(Type type);

		void addVertices(const Range<float> range);
		void addVertices(const ShortRect& rect);

		void updateVertices(const Range<float> range, uint16 offset = 0);
		void updateVertices(const ShortRect& rect, uint16 offset = 0);

		void updateTextureCoordinates(const Range<float> range, uint16 offset = 0);

		void calculateCenter() override;
		void setColor(const Color& col);
		void move(float x, float y);

		void move(const Vector2f& vec) {
			this->move(vec.x, vec.y);
		}
	};
}

#endif