#include <iostream>
#include <SGL/Graphic.hpp>
#include <SGL/System.hpp>
#include <SGL/Audio.hpp>
#include <SGL/Window.hpp>

int main() {
	sgl::Window wnd(640, 480, "Test");
	//wnd.setClearColor(sgl::Color::Blue);
	wnd.setVerticalSync(sgl::Window::Sync::Disable);
	//wnd.framerateLimit = 30;

	uint32 pixels[256] = {
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
		0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
		0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
		0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
		0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
		0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
		0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
		0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
		0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
		0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
		0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
		0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
		0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
		0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
		0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
		0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
		0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
		0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
		0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
		0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
		0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
		0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
		0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
	};

	sgl::Surface icon(pixels, 16, 16, 32);

	wnd.setIcon(icon);

	sgl::Surface wiki("samples/Images/wiki.png");
	sgl::Texture wiki_tex(wiki);
	sgl::Sprite wiki_sprite(wiki_tex);
	wiki_sprite.position.set(200, 200);
	wiki_sprite.rotate(25);

	sgl::Surface wiki2(wiki.pixels(), wiki.width(), wiki.height(), 24);
	wiki2.saveToFile("samples/Images/Wiki2.png");
	sgl::Texture wiki2_tex(wiki2);
	sgl::Sprite wiki_sprite2(wiki2_tex);
	wiki_sprite2.position.set(100, 100);

	sgl::Texture icon_tex(icon);
	sgl::Sprite icon_sprite(icon_tex);

	sgl::Shape s(sgl::Shape::Type::Quad);
	s.addVertices({275, 15, 475, 15, 475, 215, 275, 215});
	s.updateTextureCoordinates({0, 0, 1, 0, 1, 1, 0, 1});
	s.setColor(sgl::Color::Blue);
	s.texture = &wiki_tex;
	//s.fill = true;

	sgl::Shape test(sgl::Shape::Type::Quad);
	test.addVertices({50, 150, 100, 150, 100, 200, 50, 200});

	sgl::Font fnt("samples/Font/arial.ttf", 32);
	sgl::String str(fnt, "Ein Test");
	str.position = sgl::Vector2f(100, 25);
	str.mode = sgl::Font::Mode::Shaded;

	sgl::Surface explo("samples/Images/test_3.png");
	sgl::Texture explo_tex(explo);

	sgl::Spritesheet animation(explo_tex);
	animation.tickOffset = 150;
	animation.view = sgl::ShortRect(0, 0, 43, 59);
	animation.position = sgl::Vector2f(360, 300);

	sgl::Sound sound1("samples/Audio/expl.wav");
	sgl::Sound sound2("samples/Audio/orchestral.ogg");

	//sgl::Mouse::SetCursor(sgl::Mouse::Cursor::SizeNS);
	sgl::Mouse::SetCursor(icon);

	std::cout << (sgl::System::Platform() == sgl::System::OS::Windows ? "Du bist auf Windows" : "Unbekanntes OS")
		<< ". RAM = " << sgl::System::RAM() << " Cores = " << sgl::System::CountGPU() << std::endl;

	sgl::Shape box(sgl::Shape::Type::Quad);
	box.addVertices(sgl::ShortRect(20, 200, 50, 50));
	box.calculateCenter();

	sgl::Font fnt2("samples/Font/arial.ttf", 16);
	sgl::String str2(fnt2);
	str2.bg = sgl::Color::Red;
	str2.mode = sgl::Font::Mode::Shaded;
	str2 = "Ein Test mit roten Background";
	str2.position.set(200, 400);

	sgl::Clock clock;

	sgl::Event event;
	while (wnd.isOpen()) {
		while (sgl::Event::Poll(event)) {
			switch (event.type) {
				case sgl::Event::Type::Quit:
					wnd.close();
					break;
				case sgl::Event::Type::KeyDown:
					if (event.keyboard.key == sgl::Keyboard::Code::Escape)
						sgl::Event::Push(sgl::Event::Type::Quit);
					else {
						switch (event.keyboard.key) {
							case sgl::Keyboard::Code::Up:
								s.move(0, -10);
								break;
							case sgl::Keyboard::Code::Down:
								s.move(0, 10);
								break;
							case sgl::Keyboard::Code::Left:
								s.move(-10, 0);
								break;
							case sgl::Keyboard::Code::Right:
								s.move(10, 0);
								break;
							case sgl::Keyboard::Code::Num1:
								sound1.play();
								break;
							case sgl::Keyboard::Code::Num2:
								sound2.play();
								break;
							case sgl::Keyboard::Code::Space:
								box.rotate(15);
								box.move(8, 0);
								break;
							default:
								str = "You pressed a Key";
						}
					}
					break;
				default: break;
			}

			//printf("Event Loop\n");
		}

		//printf("Frame\n");
		//printf("Frames: %d\n", clock.getCurrentFps());
		str.format("Framerate is %d", clock.getCurrentFps());

		wnd.clear();

		wnd.draw(str2);

		wnd.draw(icon_sprite);
		wnd.draw(wiki_sprite);
		wnd.draw(wiki_sprite2);
		wnd.draw(box);
		wnd.draw(s);
		wnd.draw(str);

		animation.row = 1;
		animation.slide(sgl::Spritesheet::Grid::Row);
		wnd.draw(animation);

		//icon_sprite.position.y += 1;
		//icon_sprite.position.x += 1;

		wnd.display();
	}

	//Color black = Color::Black;
	//Color gl = Color::GL(0.8f, 0.8f, 0.8f);

	//std::cout << "end of main " << Window::Count() << std::endl;

	return 0;
}