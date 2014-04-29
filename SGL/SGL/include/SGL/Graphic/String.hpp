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
		mutable bool _changed = false;
		const Color* _fg = nullptr;
		const Color* _bg = nullptr;

		Font* _font = nullptr;

		std::string _text;
		std::unique_ptr<Texture> _texture;

	protected:
		void _update() const;
		virtual void draw(const Window& wnd) const override;

	public:
		Font::Mode mode;
		Vector2f position;

		explicit String();
		explicit String(Font& fnt);

		void setFont(Font& fnt) {
			_font = &fnt;
			_changed = true;
		}

		const Font* getFont() const {
			return _font;
		}

		const std::string& getText() const {
			return _text;
		}

		void operator =(const std::string& str);
		void operator =(const String& txt);

		void format(const char* fmt, ...);

		void setColor(const Color* fg, const Color* bg = nullptr) {
			_fg = fg;
			_bg = bg;
			_changed = true;
		}
	};

	bool operator ==(const String& lhs, const String& rhs);
	bool operator !=(const String& lhs, const String& rhs);
}

#endif