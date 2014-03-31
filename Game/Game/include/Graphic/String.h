#pragma once

#include <string>
#include <memory>
#include <Graphic\Drawable.h>
#include <Graphic\Color.h>
#include <Graphic\Texture.h>
#include <System\Font.h>
#include <Math\Vector2.h>
#include <Window\Window.h>

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

		void update() {
			_changed = true;
		}

	protected:
		void _update() const;
		virtual void draw(const Window& wnd) const;
	};
}