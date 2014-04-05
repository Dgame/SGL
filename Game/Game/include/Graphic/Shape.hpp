#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <array>
#if _DEBUG
#include <Core\Output.hpp>
#endif
#include <Core\OpenGL.hpp>
#include <Core\Types.hpp>
#include <Core\Range.hpp>
#include <Math\Vertex.hpp>
#include <Graphic\Drawable.hpp>
#include <Graphic\Texture.hpp>

namespace sgl {
	class Shape : public Drawable {
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
		uint8 lineWidth;
		bool fill;

		explicit Shape(Type type);

		void addVertices(Range<float> range);
		void setVertices(Range<float> range);
		void setTextureCoordinates(Range<float> range);

		void setColor(const Color& col);
		void move(float x, float y);

		void move(const Vector2f& vec) {
			move(vec.x, vec.y);
		}
	};
}

#endif