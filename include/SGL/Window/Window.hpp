#ifndef SGL_WINDOW_HPP
#define SGL_WINDOW_HPP

#include <iostream>
#include <string>
#include <SGL/Core/Config.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/Math/vec2.hpp>
#include <SGL/Math/Vertex.hpp>
#include <SGL/Math/mat4.hpp>

namespace {
	void initSDL();
	void quitSDL(sgl::uint8 count);
	void initGL();
}

namespace sgl {
	class Texture;
	class Drawable;
	class Surface;
	enum class Geometry;

	class Window {
	public:
		enum Flags {
			Fullscreen = SDL_WINDOW_FULLSCREEN,
			Desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
			Hidden = SDL_WINDOW_HIDDEN,
			Borderless = SDL_WINDOW_BORDERLESS,
			Resizeable = SDL_WINDOW_RESIZABLE,
			Minimized = SDL_WINDOW_MINIMIZED,
			Maximized = SDL_WINDOW_MAXIMIZED,
			Focus = SDL_WINDOW_INPUT_GRABBED,
			HighDPI = SDL_WINDOW_ALLOW_HIGHDPI,

			Windowed = ~(Fullscreen | Desktop),

			Default = Focus | HighDPI
		};

		enum Interval {
			Immediate = 0,
			Synchronize = 1,
			LateSwapTearing = -1
		};

	private:
		static uint8 _count;

		// mat4x4 _projection;

		SDL_Window* _window = nullptr;
		SDL_GLContext _context;

	public:
		Window() = default;
		explicit Window(uint16 width, uint16 height, const std::string&, Flags flags = Flags::Default);
		explicit Window(const ShortRect&, const std::string&, Flags flags = Flags::Default);

		Window(const Window&) = delete;

		// virtual ~Window();

		// void close();

		// bool isOpen() const {
		// 	return _window != nullptr;
		// }

		// mat4x4& getProjection() {
		// 	return _projection;
		// }

		// void loadProjection() const;

		// void setClearColor(const Color4b&) const;
		// void clear() const;

		// void setVisible(bool visible) const;
		// void setScreenSaver(bool enable) const;
		// bool hasScreenSaver() const;
		// // void setIcon(const Surface&) const;
		// // void setBorder(bool enable) const;
		// // void setSwapInterval(Interval interval) const;
		// // Interval getSwapInterval() const;

		// void maximize() const;
		// void minimize() const;
		// void restore() const;
		// void raise() const;

		// void toggle(Flags flag) const;

		// void setPosition(const vec2s&) const;
		// void setSize(uint16 width, uint16 height) const;
		// void setRect(const ShortRect&) const;

		// vec2s getPosition() const;
		// ShortRect getRect() const;

		// void setTitle(const std::string&) const;
		// std::string getTitle() const;

		// void draw(const Drawable&) const;
		// void draw(Geometry geo, const mat4x4& mat, const std::vector<Vertex>& vertices, const Texture* texture) const;
		// void draw(Geometry geo, const mat4x4& mat, const Texture& texture, const FloatRect& rect) const;
		// void display() const;
	};
}

#endif