#include <SGL/Window/Window.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Surface.hpp>
#include <SGL/Math/Geometry.hpp>

namespace sgl {
    int32 Window::_count = 0;

    Window::Window(uint16 width, uint16 height, const std::string& title, Style style)
        : Window(ShortRect(100, 100, width, height), title, style)
    {

    }

    Window::Window(const ShortRect& rect, const std::string& title, Style style) {
        Intern::initSDL();
        // Create an application window with the following settings:
        _window = SDL_CreateWindow(
            title.c_str(),
            rect.x, rect.y,
            rect.width, rect.height,
            style | SDL_WINDOW_OPENGL);

        if (!_window) {
            std::cerr << SDL_GetError() << std::endl;
            exit(1);
        }

        _context = SDL_GL_CreateContext(_window);
        if (!_context) {
            std::cerr << SDL_GetError() << std::endl;
            exit(1);
        }

        SDL_GL_MakeCurrent(_window, _context);
        Intern::initGL();
#if SGL_DEBUG
        const uint8* GL_version = glGetString(GL_VERSION);
        const uint8* GL_vendor = glGetString(GL_VENDOR);
        const uint8* GL_renderer = glGetString(GL_RENDERER);
        printf("Version: %s - %s - %s\n", GL_version, GL_vendor, GL_renderer);
#endif
        _projection.ortho(ShortRect(0, 0, rect.width, rect.height));
        this->loadProjection();

        this->setSwapMode(SwapMode::Synchronize);
        this->setClearColor(Color4b::White);

        _open = true;
        _count++;
    }

    Window::~Window() {
        SDL_DestroyWindow(_window);
        SDL_GL_DeleteContext(_context);

        _count--;

        Intern::quitSDL(_count);
    }

    void Window::loadProjection() const {
        glCheck(glMatrixMode(GL_PROJECTION));
        glCheck(glLoadMatrixf(_projection.values));
        glCheck(glMatrixMode(GL_MODELVIEW));
    }

    Window::Style Window::getStyle() const {
        return static_cast<Style>(SDL_GetWindowFlags(_window));
    }

    void Window::toggle(Style style) const {
        SDL_Check(SDL_SetWindowFullscreen(_window, style));
    }

    void Window::setBorder(bool enable) const {
        SDL_SetWindowBordered(_window, enable ? SDL_TRUE : SDL_FALSE);
    }

    void Window::setClearColor(const Color4b& col) const {
        const Color4f gl_col = col;
        glCheck(glClearColor(gl_col.red, gl_col.green, gl_col.blue, gl_col.alpha));
    }

    void Window::clear() const {
        glCheck(glClear(GL_COLOR_BUFFER_BIT));
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

    void Window::setIcon(const Surface& icon) const {
        SDL_SetWindowIcon(_window, icon._surface);
    }

    void Window::setSwapMode(SwapMode mode) const {
        SDL_Check(SDL_GL_SetSwapInterval(static_cast<int>(mode)));
    }

    SwapMode Window::getSwapMode() const {
        return static_cast<SwapMode>(SDL_GL_GetSwapInterval());
    }

    bool Window::hasScreenSaver() const {
        return SDL_IsScreenSaverEnabled() == SDL_TRUE;
    }

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

    void Window::setPosition(int16 x, int16 y) const {
        SDL_SetWindowPosition(_window, x, y);
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
        if (vertices.size() == 0)
            return;

        glCheck(glLoadMatrixf(mat.values));

        if (texture)
            texture->bind();
        else
            glCheck(glDisable(GL_TEXTURE_2D));

        glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].position.x));
        glCheck(glColorPointer(4, GL_FLOAT, sizeof(Vertex), &vertices[0].color.red));
        if (texture)
            glCheck(glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].texCoord.x));
        glCheck(glDrawArrays(static_cast<int>(geo), 0, vertices.size()));

        if (texture)
            texture->unbind();
    }

    void Window::draw(Geometry geo, const mat4x4& mat, const Texture& texture, const Vertex* vertices, uint16 vCount) const {
        if (!vertices || vCount == 0)
            return;

        glCheck(glLoadMatrixf(mat.values));
        texture.bind();

        glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &vertices->position.x));
        glCheck(glColorPointer(4, GL_FLOAT, sizeof(Vertex), &vertices->color.red));
        glCheck(glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), &vertices->texCoord.x));
        glCheck(glDrawArrays(static_cast<int>(geo), 0, vCount));

        texture.unbind();
    }

    void Window::display() const {
        SDL_GL_SwapWindow(_window);
    }
}
