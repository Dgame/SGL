#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Output.hpp>
#include <SGL/Core/Scope.hpp>
#include <SGL/Graphic/Color.hpp>
#include <SGL/Graphic/Surface.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Math/Rect.hpp>
#include <SGL/Math/Vector2.hpp>
#include <SGL/System/Clock.hpp>
#include <SGL/Window/DrawOptions.hpp>

namespace sgl {
	class Texture;
	struct Primitive;

	class Window {
	public:
		/**
		* The Window syncronisation mode.
		* Default Syncronisation is <code>Sync.Enable</code>.
		*/
		enum class Sync : short {
			Enable = 1,	/** Sync is enabled */
			Disable = 0,	/** Sync is disabled */
			LateSwapTearing = -1	/** For late swap tearing */
		};

		/**
		* The specific window styles
		*/
		enum Style {
			Fullscreen = SDL_WINDOW_FULLSCREEN, /** Window is fullscreened */
			Desktop = SDL_WINDOW_FULLSCREEN_DESKTOP, /** Window has Desktop Fullscreen */
			OpenGL = SDL_WINDOW_OPENGL,	 /** OpenGL support */
			Shown = SDL_WINDOW_SHOWN,		 /** Show the Window immediately */
			Borderless = SDL_WINDOW_BORDERLESS, /** Hide the Window immediately */
			Resizeable = SDL_WINDOW_RESIZABLE,  /** Window is resizeable */
			Maximized = SDL_WINDOW_MAXIMIZED,  /** Maximize the Window immediately */
			Minimized = SDL_WINDOW_MINIMIZED,  /** Minimize the Window immediately */
			InputGrabbed = SDL_WINDOW_INPUT_GRABBED, /** Grab the input inside the window */
			InputFocus = SDL_WINDOW_INPUT_FOCUS, /** The Window has input (keyboard) focus */
			MouseFocus = SDL_WINDOW_MOUSE_FOCUS, /** The Window has mouse focus */
			HighDPI = SDL_WINDOW_ALLOW_HIGHDPI, /** Window should be created in high-DPI mode if supported (>= SDL 2.0.1) */
			Foreign = SDL_WINDOW_FOREIGN, /** The window was created by some other framework. */
			Windowed = 0, /// The windows is presented as window. It's the opposite of Fullscreen

			Default = Shown | OpenGL | HighDPI /** Default mode is Shown | OpenGL | HighDPI */
		};

	private:
		SDL_Window* _window = nullptr;
		SDL_GLContext _glContext = nullptr;

		bool _shutdown = false;

		static int _winCount;

	public:
		uint16 framerateLimit;

		explicit Window(uint16 width, uint16 height, const std::string& title, uint32 style = Style::Default);
		explicit Window(const ShortRect& rect, const std::string& title, uint32 style = Style::Default);

		Window(const Window& wnd) = delete;

		virtual ~Window();

		static int Count() {
			return _winCount;
		}

		int id() const {
			return SDL_GetWindowID(_window);
		}

		bool isOpen() const {
			return !_shutdown;
		}

		void close() {
			_shutdown = true;
		}

		void applyViewport() const;

		void maximize() const {
			SDL_MaximizeWindow(_window);
		}

		void minimize() const {
			SDL_MinimizeWindow(_window);
		}

		void show() const {
			SDL_ShowWindow(_window);
		}

		void hide() const {
			SDL_HideWindow(_window);
		}

		void restore() const {
			SDL_RestoreWindow(_window);
		}

		void raise() const {
			SDL_RaiseWindow(_window);
		}

		void setPosition(uint16 x, uint16 y) const {
			SDL_SetWindowPosition(_window, x, y);
		}

		void setPosition(const Vector2s& position) const {
			setPosition(position.x, position.y);
		}

		Vector2s getPosition() const;

		void setSize(uint16 width, uint16 height) const {
			SDL_SetWindowSize(_window, width, height);
		}

		uint16 width() const {
			int w = 0;
			SDL_GetWindowSize(_window, &w, nullptr);

			return w;
		}

		uint16 height() const {
			int h = 0;
			SDL_GetWindowSize(_window, nullptr, &h);

			return h;
		}

		void setTitle(const std::string& title) const {
			SDL_SetWindowTitle(_window, title.c_str());
		}

		std::string getTitle() const {
			return std::string(SDL_GetWindowTitle(_window));
		}

		Style getStyle() const {
			return static_cast<Style>(SDL_GetWindowFlags(_window));
		}

		void toggleFullscreen(Style style) const {
			if (style == Style::Fullscreen || style == Style::Desktop || style == Style::Windowed)
				SDL_SetWindowFullscreen(_window, static_cast<int>(style));
		}

		void setIcon(const Surface& icon) const {
			SDL_SetWindowIcon(_window, icon.ptr());
		}

		void clear(uint32 flags = GL_COLOR_BUFFER_BIT) const {
			glClear(flags);
		}

		/**
		* Set the color with which this windows clear his buffer.
		* This is also the background color of the window.
		*/
		void setClearColor(const Color& col) const {
			const GLColor gl_col = Color::InGLMode(col);
			glClearColor(gl_col.red, gl_col.green, gl_col.blue, gl_col.alpha);
		}

		bool hasMouseFocus() const {
			return SDL_GetMouseFocus() == _window;
		}

		/**
		* Returns the current syncronisation mode.
		*
		* See: Sync enum
		*/
		Sync getVerticalSync() const {
			return static_cast<Sync>(SDL_GL_GetSwapInterval());
		}

		bool setVerticalSync(Sync sync) const;

		void draw(const Drawable& d) const {
			d.draw(*this);
		}

		void draw(const Drawable& d, const DrawOptions options) const;
		void draw(const Primitive& p, const float* texCoords, const Texture* texture) const;
		void display() const;
	};
}

#endif