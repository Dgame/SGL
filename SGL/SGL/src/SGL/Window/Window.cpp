#include <SGL/Window/Window.hpp>
#include <SGL/Graphic/Primitive.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Blend.hpp>
#include <SGL/Graphic/Shader.hpp>

namespace sgl {
	int Window::_winCount = 0;

	Window::Window(uint16 width, uint16 height, const std::string& title, uint32 style) : Window(ShortRect(100, 100, width, height), title, style) {

	}

	Window::Window(const ShortRect& rect, const std::string& title, uint32 style) {
		if (_winCount == 0)
			internal::initSDL();

		_winCount++;

		_window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.width, rect.height, static_cast<int>(style));
		if (_window == nullptr) {
			error("Error by creating a SDL2 window: ", SDL_GetError());

			return;
		}

		if (style & Style::OpenGL) {
			_glContext = SDL_GL_CreateContext(_window);
			if (_glContext == nullptr) {
				error("Error while creating gl context: ", SDL_GetError());

				return;
			}
#if SGL_DEBUG
			const uint8* GL_version = glGetString(GL_VERSION);
			const uint8* GL_vendor = glGetString(GL_VENDOR);
			const uint8* GL_renderer = glGetString(GL_RENDERER);

			println("Version: ", GL_version, " - ", GL_vendor, " - ", GL_renderer);
#endif
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, rect.width, rect.height, 0, 1, -1);

			this->applyViewport();

			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);

			glShadeModel(GL_FLAT);
			glDisable(GL_DITHER);
			glDisable(GL_CULL_FACE);
			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_ALPHA_TEST);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			// Hints
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

			this->setVerticalSync(Sync::Enable);
			this->setClearColor(Color::White);

			SDL_GL_MakeCurrent(_window, _glContext);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

			const GLenum err = glewInit();
			if (err != GLEW_OK)
				error("Couldn't initialize GLEW");
		}
	}

	Window::~Window() {
		SDL_GL_DeleteContext(_glContext);
		SDL_DestroyWindow(_window);

		_glContext = nullptr;
		_window = nullptr;

		_winCount--;
	}

	void Window::applyViewport() const {
		int w = 0, h = 0;
		SDL_GetWindowSize(_window, &w, &h);

		glMatrixMode(GL_MODELVIEW);
		glViewport(0, 0, w, h);
	}

	Vector2s Window::getPosition() const {
		int x = 0, y = 0;
		SDL_GetWindowPosition(_window, &x, &y);

		return Vector2s(x, y);
	}

	/**
	* Set the Syncronisation mode of this window.
	* Default Syncronisation is <code>Sync.Enable</code>.
	*
	* See: Sync enum
	*
	* Returns if the sync mode is supported.
	*/
	bool Window::setVerticalSync(Sync sync) const {
		if (sync == Sync::Enable || sync == Sync::Disable)
			return SDL_GL_SetSwapInterval(static_cast<int>(sync)) == 0;
		else
			error("Unknown sync mode. Sync mode must be one of Sync.Enable, Sync.Disable.");

		return false;
	}

	void Window::draw(const Drawable& d, const DrawOptions options) const {
		GLAttribScope attr(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);

		if (options.blend != nullptr)
			options.blend->apply();
		if (options.shader != nullptr)
			options.shader->execute();

		d.draw(*this);

		if (options.shader != nullptr)
			options.shader->use(false);
	}

	void Window::draw(const Primitive& p, const float* texCoords, const Texture* texture) const {
		if (p.vcount == 0)
			return;

		GLAttribScope attr(GL_ENABLE_BIT);

		glVertexPointer(2, GL_FLOAT, p.offset, p.vertices);

		if (texture == nullptr)
			glDisable(GL_TEXTURE_2D);
		else if (texCoords != nullptr) {
			glTexCoordPointer(2, GL_FLOAT, p.offset, texCoords);
			texture->bind();
		}

		if (p.color != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, p.offset, p.color);
		}

		glDrawArrays(p.type, p.vfirst, p.vcount);

		if (texture != nullptr)
			texture->unbind();

		if (p.color != nullptr)
			glDisableClientState(GL_COLOR_ARRAY);
	}

	/**
	* Make all changes visible on screen.
	* If the framerate limit is not 0, it waits for (1000 / framerate limit) milliseconds.
	*/
	void Window::display() const {
		if ((this->getStyle() & Style::OpenGL) == Style::OpenGL)
			SDL_GL_SwapWindow(_window);
		else
			SDL_UpdateWindowSurface(_window);

		if (this->getVerticalSync() != Sync::Enable && this->framerateLimit > 0)
			Clock::Wait(1000 / this->framerateLimit);
	}
}