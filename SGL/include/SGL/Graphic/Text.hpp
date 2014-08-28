#ifndef SGL_TEXT_HPP
#define SGL_TEXT_HPP

#include <string>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Color.hpp>
#include <SGL/System/Font.hpp>
#include <SGL/Math/Vertex.hpp>

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
		Color4b foreground = Color4b::White;
		Color4b background = Color4b::Black;
		Font::Mode mode = Font::Mode::Solid;

		explicit Text(Font&, const std::string& str = "");
		Text(const Text&);
		
		virtual ~Text() {

		}

		void operator =(const std::string&);

		const std::string& getText() const {
			return _text;
		}

		void setFont(Font&);

		Font* getFont() const {
			return _font;
		}
	};
}

#endif