#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <stdarg.h>
#include <memory>
#include <vector>
#include <SGL/Graphic\Drawable.hpp>
#include <SGL/Graphic\Color.hpp>
#include <SGL/Graphic\Texture.hpp>
#include <SGL/System\Font.hpp>
#include <SGL/Math\Vector2.hpp>
#include <SGL/Window\Window.hpp>

namespace sgl {
	class String : public Drawable {
	private:
		std::string _text;
		std::unique_ptr<Texture> _texture;

	protected:
		void _update();
		virtual void draw(const Window& wnd) const;

	public:
		Font::Mode mode;
		Vector2f position;
		Font& font;
		Color fg;
		Color bg;

		explicit String(Font& fnt, const std::string& str = "");

		virtual ~String() {

		}

		void update() {
			_update();
		}

		void operator =(const std::string& str);
		void operator =(const String& txt);

		void format(const char* fmt, ...);

		void clear() {
			_text.clear();
			_update();
		}
	};
}

#endif