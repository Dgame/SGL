#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <array>
#if _DEBUG
#include <SGL/Core\Output.hpp>
#endif
#include <SGL/Core\OpenGL.hpp>
#include <SGL/Core\Types.hpp>
#include <SGL/Core\Range.hpp>
#include <SGL/Math\Vertex.hpp>
#include <SGL/Graphic\Drawable.hpp>
#include <SGL/Graphic\Texture.hpp>

namespace sgl {
	class Shape : public Drawable {
	protected:
		virtual void draw(const Window&) const override;

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
		Texture* texture;
		Type type;
		uint8 lineWidth;
		bool fill;

		explicit Shape(Type type);

		void addVertices(const Range<float> range);
		void addVertices(const ShortRect& rect);

		void updateVertices(const Range<float> range);

		void setTextureCoordinates(const Range<float> range);

		void setColor(const Color& col);
		void move(float x, float y);

		void move(const Vector2f& vec) {
			this->move(vec.x, vec.y);
		}
	};
}

#endif