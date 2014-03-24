#pragma once

#if _DEBUG
#include <Core\Output.h>
#endif
#include <memory>
#include <vector>
#include <array>
#include <Core\OpenGL.h>
#include <Core\Types.h>
#include <Math\Vertex.h>
#include <Graphic\Drawable.h>
#include <Graphic\Texture.h>

class Shape : public Drawable {
protected:
	virtual void draw(const Window& wnd) const override;

private:
	std::shared_ptr<Texture> _texture;

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
	Type type;
	uint8 lineWidth;
	bool fill;

	explicit Shape(Type type);

	template <uint16 n>
	void addVertices(std::array<float, n>& arr);

	template <uint16 n>
	void setVertices(std::array<float, n>& arr);

	template <uint16 n>
	void setTextureCoordinates(std::array<float, n>& arr);

	void setColor(const Color& col);
	virtual void bindTexture(Texture* tex);

	void move(float x, float y);

	void move(const Vector2f& vec) {
		move(vec.x, vec.y);
	}
};

template <uint16 n>
void Shape::addVertices(std::array<float, n>& arr) {
	for (uint16 i = 0, j = 0; i < n / 2;  i++, j += 2) {
		this->vertices.emplace_back(Vertex(arr[j], arr[j + 1]));
	}
}

template <uint16 n>
void Shape::setVertices(std::array<float, n>& arr) {
	uint32 count = min(n, this->vertices.size());

	for (uint32 i = 0, j = 0; i < count; i++, j += 2) {
		this->vertices[i].x = arr[j];
		this->vertices[i].y = arr[j + 1];
	}
}

template <uint16 n>
void Shape::setTextureCoordinates(std::array<float, n>& arr) {
	uint32 count = min(n, this->vertices.size());

	for (uint32 i = 0, j = 0; i < count; i++, j += 2) {
		this->vertices[i].tx = arr[j];
		this->vertices[i].ty = arr[j + 1];
	}
}