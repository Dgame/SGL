#include <Math\Vertex.h>

Vertex::Vertex(float _x, float _y) : Vertex(_x, _y, 0, 0) {

}

Vertex::Vertex(float _x, float _y, float _tx, float _ty) : x(_x), y(_y), tx(_tx), ty(_ty) {
	setColor(Color::Black);
}

void Vertex::setColor(const Color& col) {
	r = col.r > 1 ? col.r / 255.f : col.r;
	g = col.g > 1 ? col.g / 255.f : col.g;
	b = col.b > 1 ? col.b / 255.f : col.b;
	a = col.alpha > 1 ? col.alpha / 255.f : col.alpha;
}
