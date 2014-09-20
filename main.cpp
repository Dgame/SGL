#include <iostream>
#include <vector>
#include <SGL/all.hpp>

int main() {
    sgl::Window wnd(64 * 15, 64 * 15, "Hallo Welt");
    wnd.setSwapMode(sgl::SwapMode::Immediate);

    sgl::Shape shape(sgl::Geometry::Quad);
    shape.append(sgl::Vertex(10,  10));
    shape.append(sgl::Vertex(110, 10));
    shape.append(sgl::Vertex(110, 110));
    shape.append(sgl::Vertex(10,  110));
    shape.setCenter(60, 60);
    shape.setColor(sgl::Color4b::White);

    sgl::Surface wood("../../samples/Images/holz.jpg");
    sgl::Texture wood_tex(wood);

    shape.setTexture(&wood_tex);
    shape.setTextureRect(sgl::FloatRect(50, 50, 80, 80));

    sgl::Surface wiki("../../samples/Images/wiki.png");
    sgl::Texture wiki_tex(wiki);

    sgl::Sprite sprite(wiki_tex);
    sprite.setPosition(100, 200);
    sprite.setCenter(70, 70);

    sgl::Surface bug1("../../samples/Images/bug.png");
    sgl::Texture bug1_tex(bug1);
    sgl::Sprite bug_sprite(bug1_tex);
    bug_sprite.setPosition(100, 100);
    bug_sprite.setClipRect(sgl::ShortRect(0, 0, 112, 62));

    sgl::StopWatch sw;

    sgl::Font font("../../samples/Font/arial.ttf", 12);
    sgl::Text txt(font);
    txt.mode = sgl::Font::Shaded;
    txt.setPosition(250, 10);

    //sgl::Music mus("samples/Audio/orchestral.ogg");
    sgl::Sound snd("../../samples/Audio/expl.wav");

    sgl::Event event;
    while (wnd.isOpen()) {
        while (sgl::PollEvent(&event)) {
            switch (event.type) {
                case sgl::Event::Quit:
                    wnd.close();
                break;

                case sgl::Event::KeyDown:
                    if (event.key.key == sgl::Key::Escape)
                        sgl::PushEvent(sgl::Event::Quit);
                    else {
                        std::cout << static_cast<int>(event.key.key) << std::endl;
                        shape.move(25, 25);
                        sprite.move(25, 25);

                        if (event.key.key == sgl::Key::Space)
                            snd.play();
                    }
                break;

                case sgl::Event::MouseButtonDown:
                    shape.rotate(5);
                    sprite.rotate(-5);
                    printf("Mouse down @ %d:%d -> Button = %d\n",
                            event.mouse.button.x, event.mouse.button.y,
                            static_cast<int>(event.mouse.button.button));
                break;

                case sgl::Event::MouseWheel:
                    shape.scale(0.2f * event.mouse.wheel.delta.x);
                    printf("Mouse delta: %d, %d\n",
                           event.mouse.wheel.delta.x, event.mouse.wheel.delta.y);
                break;
            }
        }

        wnd.clear();

        txt.setData(sgl::GetFPS());
        //sgl::Time t = sw.getElapsedTime();
        //printf("Passed time: %d hours, %d minutes, %d seconds and %d msecs.\n", t.hours, t.minutes, t.seconds, t.msecs);

        //mus.play();

        wnd.draw(bug_sprite);
        wnd.draw(txt);
        wnd.draw(sprite);
        wnd.draw(shape);

        if (sw.getElapsedMs() >= 200) {
            if (bug_sprite.getClipRect().x == 0) {
                bug_sprite.setClipRect(sgl::ShortRect(113, 0, 117, 62));
            } else {
                bug_sprite.setClipRect(sgl::ShortRect(0, 0, 112, 62));
            }

            sw.reset();
        }

        wnd.display();
    }
}
