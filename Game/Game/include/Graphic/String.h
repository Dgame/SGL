#pragma once

#include <string>
#include <Graphic\Drawable.h>
#include <Graphic\Color.h>

namespace sgl {
	class String : public Drawable {
	private:
		std::string _text;

	public:
		explicit String(const std::string& str);

		void operator =(const std::string& str) {
			_text = str;
		}

		void operator =(const String& txt) {
			_text = txt._text;
		}

	protected:
		virtual void draw(const Window& wnd) const;
	};
}