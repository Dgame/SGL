#include <SGL/Window/Window.hpp>

void _sdl_init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());

		return _sdl_quit();
	}

	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support.\n");
		printf("IMG_Init: %s\n", IMG_GetError());

		return _sdl_quit();
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init failed: %s\n", TTF_GetError());
		
		return _sdl_quit();
	}

	flags = MIX_INIT_OGG | MIX_INIT_MP3;
	initted = Mix_Init(flags);
	if ((initted & flags) != flags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());

		return _sdl_quit();
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		
		return _sdl_quit();
	}

	const uint16 Channels = 256;

	Mix_AllocateChannels(Channels);
	const int reserved_count = Mix_ReserveChannels(Channels);
	if (reserved_count != Channels) {
		printf("reserved %d channels from default mixing.\n", reserved_count);
		printf("%d channels were not reserved!\n", Channels);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

void _sdl_quit() {
	Mix_CloseAudio();

	// force a quit
	while (Mix_Init(0)) {
		Mix_Quit();
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

namespace sgl {
	int Window::_winCount = 0;

	Window::Window(uint16 width, uint16 height, const std::string& title, Style style) : Window(ShortRect(100, 100, width, height), title, style) {

	}

	Window::Window(const ShortRect& rect, const std::string& title, Style style) {
		if (_winCount == 0)
			_sdl_init();
		_winCount++;

		_window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.width, rect.height, static_cast<int>(style));
		if (_window == nullptr) {
			printf("Error by creating a SDL2 window: %s.\n", SDL_GetError());
			exit(1);
		}

		if (style & Style::OpenGL) {
			_glContext = SDL_GL_CreateContext(_window);
			if (_glContext == nullptr) {
				printf("Error while creating gl context: %s\n", SDL_GetError());
				exit(1);
			}
#if _DEBUG
			char* GL_version = (char*) glGetString(GL_VERSION);
			char* GL_vendor = (char*) glGetString(GL_VENDOR);
			char* GL_renderer = (char*) glGetString(GL_RENDERER);

			println(GL_version, " - ", GL_vendor, " - ", GL_renderer);
#endif
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Hints
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
			glOrtho(0, rect.width, rect.height, 0, 1, -1);

			setVerticalSync(Sync::Enable);
			setClearColor(Color::White);

			SDL_GL_MakeCurrent(_window, _glContext);
		}
	}

	Window::~Window() {
		close();

		_winCount--;
		if (_winCount <= 0)
			_sdl_quit();
	}

	void Window::close() {
		SDL_GL_DeleteContext(_glContext);
		SDL_DestroyWindow(_window);

		_glContext = nullptr;
		_window = nullptr;
	}

	Vector2s Window::getPosition() const {
		int x, y;
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
		else {
			printf("Unknown sync mode. Sync mode must be one of Sync.Enable, Sync.Disable.\n");
			exit(1);
		}
	}

	void Window::draw(const float* vertices, const float* texCoords, const Texture* texture) const {
		if (texture == nullptr)
			return;

		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		texture->bind();

		glDrawArrays(GL_QUADS, 0, 8);

		texture->unbind();
	}

	void Window::draw(const Drawable& d) const {
		d.draw(*this);
	}

	/**
	* Make all changes visible on screen.
	* If the framerate limit is not 0, it waits for (1000 / framerate limit) milliseconds.
	*/
	void Window::display() const {
		const Style style = this->getStyle();

		if ((style & Style::OpenGL) == Style::OpenGL)
			SDL_GL_SwapWindow(_window);
		else
			SDL_UpdateWindowSurface(_window);

		if (framerateLimit > 0)
			Clock::Wait(1000 / framerateLimit);
	}
}