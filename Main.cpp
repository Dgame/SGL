#include <iostream>
#include <string>
#include <SGL/Window/Window.hpp>
#include <SGL/Math/vec2.hpp>
#include <SGL/Math/mat4.hpp>

int main() {
	sgl::Window wnd(400, 600, "Hallo Welt");
	sgl::vec2f v(42, 23);
	// sgl::mat4x4 m;

	std::cout << v.x << ':' << v.y << std::endl;

	return 0;
}