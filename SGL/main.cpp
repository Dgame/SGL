#include <vector>
#include <SGL/all.hpp>

int main() {
	sgl::Window wnd(400, 600, "Hallo Welt");

	/*sgl::mat4x4 mat;
	std::vector<sgl::Vertex> vertices;
	vertices.push_back(sgl::Vertex(10, 10));
	vertices.push_back(sgl::Vertex(90, 10));
	vertices.push_back(sgl::Vertex(90, 90));
	vertices.push_back(sgl::Vertex(10, 90));*/

	sgl::Shape shape(sgl::Geometry::Quad);
	shape.vertices.push_back(sgl::Vertex(10,  10));
	shape.vertices.push_back(sgl::Vertex(110, 10));
	shape.vertices.push_back(sgl::Vertex(110, 110));
	shape.vertices.push_back(sgl::Vertex(10,  110));
	shape.setCenter(60, 60);

	sgl::Event event;
	while (wnd.isOpen()) {
		wnd.clear();

		while (sgl::PollEvent(&event)) {
			switch (event.type) {
				case sgl::Event::Quit:
					wnd.close();
				break;

				case sgl::Event::Key::Down:
					if (event.key.key == sgl::Keyboard::Key::Escape)
						sgl::PushEvent(sgl::Event::Quit);
					else {
						std::cout << static_cast<int>(event.key.key) << std::endl;
						shape.move(25, 25);
					}
				break;

				case sgl::Event::Mouse::Button::Down:
					shape.rotate(5);

					printf("Mouse down @ %d:%d -> Button = %d\n",
							event.mouse.button.x, event.mouse.button.y,
							static_cast<int>(event.mouse.button.button));
				break;

				case sgl::Event::Mouse::Wheel:
					shape.scale(0.2 * event.mouse.wheel.delta.x);

					printf("Mouse delta: %d, %d\n",
						   event.mouse.wheel.delta.x, event.mouse.wheel.delta.y);
				break;
			}

			wnd.draw(shape);
			wnd.display();
		}
	}
}