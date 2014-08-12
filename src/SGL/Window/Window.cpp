#include <SGL/Window/Window.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Surface.hpp>
#include <SGL/Graphic/Geometry.hpp>

namespace {
	void initSDL() {
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
		}
	}

	void quitSDL(sgl::uint8 count) {
		if (count == 0)
			SDL_Quit();
	}

	void initGL() {
		glDisable(GL_DITHER);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_ALPHA_TEST),

		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glCullFace(GL_FRONT);
		glShadeModel(GL_FLAT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// Hints
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		const GLenum err = glewInit();
		if (err != GLEW_OK) {
			std::cerr << "Couldn't initialize GLEW" << std::endl;

			exit(1);
		}
	}
}

namespace sgl {
	uint8 Window::_count = 0;

	Window::Window(uint16 width, uint16 height, const std::string& title, Flags flags)
		: Window(ShortRect(0, 0, width, height), title, flags)
	{
		
	}

	Window::Window(const ShortRect& rect, const std::string& title, Flags flags) {
		initSDL();

		// Create an application window with the following settings:
		_window = SDL_CreateWindow(
			title.c_str(),
			rect.x,
			rect.y,
			rect.width,
			rect.height,
			flags | SDL_WINDOW_OPENGL
		);

		if (!_window) {
			std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
			exit(1);
		}

		_context = SDL_GL_CreateContext(_window);
		if (!_context) {
			std::cerr << "Could not create GL Context: " << SDL_GetError() << std::endl;
			exit(1);
		}
#if 1
		const uint8* GL_version = glGetString(GL_VERSION);
		const uint8* GL_vendor = glGetString(GL_VENDOR);
		const uint8* GL_renderer = glGetString(GL_RENDERER);

		printf("Version: %s - %s - %s\n", GL_version, GL_vendor, GL_renderer);
#endif
		initGL();

		// _projection.ortho(rect, 1, -1);
		// this->loadProjection();

		// this->setSwapInterval(Interval::Synchronize);
		// this->setClearColor(Color4b::White);

		_count++;
	}

	// Window::~Window() {
	// 	// this->close();
	// }
/*
	void Window::close() {
		SDL_DestroyWindow(_window);
		SDL_GL_DeleteContext(_context);

		_window = nullptr;
		_count--;

		quitSDL(_count);
	}

	// void Window::loadProjection() const {
	// 	glMatrixMode(GL_PROJECTION);
	// 	glLoadMatrixf(_projection.values);
	// }

	void Window::setClearColor(const Color4b& col) const {
		const Color4f gl_col = col;
		glClearColor(gl_col.red, gl_col.green, gl_col.blue, gl_col.alpha);
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::setVisible(bool visible) const {
		if (visible)
			SDL_HideWindow(_window);
		else
			SDL_ShowWindow(_window);
	}

	void Window::setScreenSaver(bool enable) const {
		if (enable)
			SDL_EnableScreenSaver();
		else
			SDL_DisableScreenSaver();
	}

	// void Window::setIcon(const Surface&) const {

	// }

	// void Window::setBorder(bool enable) const {

	// }

	// void Window::setSwapInterval(Interval interval) const {

	// }

	// Window::Interval Window::getSwapInterval() const {
	// 	return Interval::Immediate;
	// }

	// bool Window::hasScreenSaver() const {
	// 	return SDL_IsScreenSaverEnabled();
	// }

	void Window::maximize() const {
		SDL_MaximizeWindow(_window);
	}

	void Window::minimize() const {
		SDL_MinimizeWindow(_window);
	}

	void Window::restore() const {
		SDL_RestoreWindow(_window);
	}

	void Window::raise() const {
		SDL_RaiseWindow(_window);
	}

	void Window::toggle(Flags flags) const {
		if (flags == Flags::Fullscreen || 
			flags == Flags::Desktop || 
			flags == Flags::Windowed)
		{
			SDL_SetWindowFullscreen(_window, flags);
		}
	}

	void Window::setPosition(const vec2s& pos) const {
		SDL_SetWindowPosition(_window, pos.x, pos.y);
	}

	void Window::setSize(uint16 width, uint16 height) const {
		SDL_SetWindowSize(_window, width, height);
	}

	void Window::setRect(const ShortRect& rect) const {
		SDL_SetWindowPosition(_window, rect.x, rect.y);
		SDL_SetWindowSize(_window, rect.width, rect.height);
	}

	vec2s Window::getPosition() const {
		int x, y;
		SDL_GetWindowPosition(_window, &x, &y);

		return vec2s(x, y);
	}

	ShortRect Window::getRect() const {
		int x, y;
		SDL_GetWindowPosition(_window, &x, &y);
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);

		return ShortRect(x, y, w, h);
	}

	void Window::setTitle(const std::string& title) const {
		SDL_SetWindowTitle(_window, title.c_str());
	}

	std::string Window::getTitle() const {
		const char* str = SDL_GetWindowTitle(_window);

		return std::string(str);
	}

	void Window::draw(const Drawable& d) const {
		d.draw(this);
	}

	void Window::draw(Geometry geo, const mat4x4& mat, const std::vector<Vertex>& vertices, const Texture* texture) const {
		if (texture) {
			glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].texcoord.x);
			texture->bind();
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glColorPointer(4, GL_FLOAT, sizeof(Vertex), &vertices[0].color.red);
		glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].position.x);

		glDrawArrays(static_cast<GLenum>(geo), 0, 8);
		// glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(mat.values);

		if (texture)
			texture->unbind();
	}

	void Window::draw(Geometry geo, const mat4x4& mat, const Texture& texture, const FloatRect& rect) const {
		const float texCoords[8] = {
			rect.x / texture.width(),
			rect.y / texture.height(),
			rect.width / texture.width(),
			rect.height / texture.height()
		};

		static const float vertices[8] = {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		};

		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		texture.bind();
		glVertexPointer(2, GL_FLOAT, 0, vertices);

		glDrawArrays(static_cast<GLenum>(geo), 0, 8);
		// glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(mat.values);

		texture.unbind();
	}

	void Window::display() const {
		SDL_GL_SwapWindow(_window);
	}
	*/
}