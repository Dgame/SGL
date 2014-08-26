#include <iostream>
#include <vector>
#include <SGL/all.hpp>

int main() {
	sgl::Window wnd(400, 600, "Hallo Welt");
	
	sgl::Shape shape(sgl::Geometry::Quad);
	shape.append(sgl::Vertex(10,  10));
	shape.append(sgl::Vertex(110, 10));
	shape.append(sgl::Vertex(110, 110));
	shape.append(sgl::Vertex(10,  110));
	shape.setCenter(60, 60);
	shape.setColor(sgl::Color4b::White);

	sgl::Surface wood("holz.jpg");
	sgl::Texture wood_tex(wood);

	shape.setTexture(&wood_tex);
	shape.setTextureRect(sgl::FloatRect(50, 50, 80, 80));
	
	sgl::Surface wiki("wiki.png");
	sgl::Texture wiki_tex(wiki);

	sgl::Sprite sprite(wiki_tex);
	sprite.setPosition(100, 200);
	sprite.setCenter(170, 270);

	sgl::Surface qs("quinn.png");
	sgl::Texture quinn_tex(qs);

	sgl::Shape box(sgl::Geometry::Quad);
	box.append(sgl::Vertex(100, 100));
	box.append(sgl::Vertex(200, 100));
	box.append(sgl::Vertex(200, 200));
	box.append(sgl::Vertex(100, 200));
	box.setCenter(150, 150);
	box.setColor(sgl::Color4b::White);
	box.setTexture(&quinn_tex);

	//sgl::Surface copy = qs;

	sgl::StopWatch sw;
	//sgl::Battery bat = sgl::RemainingBattery();
	//std::cout << bat.seconds << std::endl;

	sgl::Event event;
	while (wnd.isOpen()) {
		wnd.clear();

		//std::cout << sw.getFPS() << std::endl;
		//sgl::Time t = sw.getElapsedTime();
		//printf("Passed time: %d hours, %d minutes, %d seconds and %d msecs.\n", t.hours, t.minutes, t.seconds, t.msecs);

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
						sprite.move(25, 25);
					}
				break;

				case sgl::Event::Mouse::Button::Down:
					shape.rotate(5);
					sprite.rotate(-5);
					printf("Mouse down @ %d:%d -> Button = %d\n",
							event.mouse.button.x, event.mouse.button.y,
							static_cast<int>(event.mouse.button.button));
				break;

				case sgl::Event::Mouse::Wheel:
					shape.scale(0.2f * event.mouse.wheel.delta.x);
					printf("Mouse delta: %d, %d\n",
						   event.mouse.wheel.delta.x, event.mouse.wheel.delta.y);
				break;
			}

			wnd.draw(sprite);
			wnd.draw(shape);
			wnd.draw(box);

			wnd.display();
		}
	}
}