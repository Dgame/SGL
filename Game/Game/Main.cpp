#include <iostream>
#include <Window\Event.h>
#include <Window/Window.h>
#include <Graphic\Surface.h>
#include <Graphic\Color.h>
#include <Graphic\Texture.h>
#include <Graphic\Sprite.h>
#include <System\Clock.h>
#include <Graphic\Shape.h>
#include <System\Font.h>
#include <Graphic\String.h>
#include <Graphic\Spritesheet.h>
#include <Audio/Sound.h>

int main() {
	sgl::Window wnd(640, 480, "Test");
	wnd.setVerticalSync(sgl::Window::Sync::Disable);
	wnd.framerateLimit = 30;

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

	sgl::Surface wiki("wiki.png");
	sgl::Texture wiki_tex(wiki);
	sgl::Sprite wiki_sprite(wiki_tex);
	wiki_sprite.position.set(200, 200);

	sgl::Surface wiki2(wiki.pixels(), wiki.width(), wiki.height(), 24);
	wiki2.saveToFile("Wiki2.png");
	sgl::Texture wiki2_tex(wiki2);
	sgl::Sprite wiki_sprite2(wiki2_tex);
	wiki_sprite2.position.set(100, 100);

	sgl::Texture icon_tex(icon);
	sgl::Sprite icon_sprite(icon_tex);

	sgl::Shape s(sgl::Shape::Type::Quad);
	std::array<float, 8> vs = {275, 15, 475, 15, 475, 215, 275, 215};
	std::array<float, 8> ts = {0, 0, 1, 0, 1, 1, 0, 1};

	s.addVertices(vs);
	s.setColor(sgl::Color::Blue);
	s.setTextureCoordinates(ts);
	s.texture = &wiki_tex;
	//s.fill = true;

	sgl::Font fnt("font/arial.ttf", 32);
	sgl::String str(fnt, "Ein Test");
	str.position = sgl::Vector2f(100, 25);
	str.mode = sgl::Font::Mode::Shaded;

	sgl::Surface explo("test_3.png");
	sgl::Texture explo_tex(explo);

	sgl::Spritesheet explosion(explo_tex, 1);
	explosion.tickOffset = 150;
	explosion.view = sgl::ShortRect(0, 0, 43, 59);
	explosion.position = sgl::Vector2f(360, 300);

	sgl::Sound sound1("expl.wav");
	sgl::Sound sound2("orchestral.ogg");
	
	sgl::Clock clock;

	Event event;
	while (wnd.isOpen()) {
		while (Event::Poll(event)) {
			switch (event.type) {
				case Event::Type::Quit:
					wnd.close();
					break;
				case Event::Type::KeyDown:
					if (event.keyboard.key == Keyboard::Code::Escape)
						Event::Push(Event::Type::Quit);
					else {
						switch (event.keyboard.key) {
							case Keyboard::Code::Up:
								s.move(0, -10);
								break;
							case Keyboard::Code::Down:
								s.move(0, 10);
								break;
							case Keyboard::Code::Left:
								s.move(-10, 0);
								break;
							case Keyboard::Code::Right:
								s.move(10, 0);
								break;
							case Keyboard::Code::Num1:
								sound1.play();
								break;
							case Keyboard::Code::Num2:
								sound2.play();
								break;
							default:
								str = "You pressed a Key";
						}
					}
					break;
			}

			//printf("Event Loop\n");
		}

		//printf("Frame\n");
		//printf("Frames: %d\n", clock.getCurrentFps());

		wnd.clear();

		wnd.draw(icon_sprite);
		wnd.draw(wiki_sprite);
		wnd.draw(wiki_sprite2);
		wnd.draw(s);
		wnd.draw(str);
		//wnd.draw(text_sprite);

		explosion.row = 1;
		explosion.slide(sgl::Spritesheet::Grid::Row);
		wnd.draw(explosion);

		//icon_sprite.position.y += 1;
		//icon_sprite.position.x += 1;

		wnd.display();
	}

	//Color black = Color::Black;
	//Color gl = Color::GL(0.8f, 0.8f, 0.8f);

	//std::cout << "end of main " << Window::Count() << std::endl;

	return 0;
}