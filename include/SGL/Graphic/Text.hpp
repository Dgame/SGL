#ifndef SGL_TEXT_HPP
#define SGL_TEXT_HPP

#include <string>
#include <sstream>
#include <SGL/Core/Config.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Color.hpp>
#include <SGL/System/Font.hpp>
#include <SGL/Math/Vertex.hpp>

namespace {
    template <typename T>
    inline std::string to_string(const T& data) {
        std::ostringstream os;
        os << data;

        return os.str();
    }
}

namespace sgl {
    class Window;

    class Text : public Drawable, public Transformable {
    private:
        mutable bool _redraw = true;
        mutable Texture _texture;
        mutable Vertex _vertices[4];
        Font* _font;
        std::string _text;

    protected:
        virtual void draw(const Window*) const override;
        void _init();

    public:
        Color4b foreground = Color4b::Black;
        Color4b background = Color4b::White;
        Font::Mode mode = Font::Mode::Solid;

        explicit Text(Font&, const std::string& str = "");
        Text(const Text&);

        virtual ~Text() {

        }

        void operator =(const Text&);
        void operator =(const std::string&);

        template <typename T>
        void setData(const T&);

        const std::string& getText() const {
            return _text;
        }

        void setFont(Font&);

        const Font* getFont() const {
            return _font;
        }
    };

    template <typename T>
    void Text::setData(const T& data) {
        _text = to_string(data);
        _redraw = true;
    }
}

#endif
