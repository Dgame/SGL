#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <Graphic\Color.h>
#include <Math\Vector2.h>

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
};

#endif