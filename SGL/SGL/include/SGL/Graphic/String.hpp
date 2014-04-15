#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <stdarg.h>
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
		mutable bool _changed;
		std::string _text;
		Texture* _texture;

	public:
		Font::Mode mode;
		Vector2f position;
		Font& font;
		Color* fg;
		Color* bg;

		explicit String(Font& fnt, const std::string& str = "");

		virtual ~String() {
			delete _texture;
		}

		void operator =(const std::string& str);
		void operator =(const String& txt);

		void format(const char* fmt, ...);

		void update() {
			_changed = true;
		}

		void clear() {
			_text.clear();
		}

	protected:
		void _update() const;
		virtual void draw(const Window& wnd) const;
	};
}

#endif