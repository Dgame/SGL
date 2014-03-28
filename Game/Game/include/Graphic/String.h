#pragma once

#include <string>
#include <Graphic\Drawable.h>
#include <Graphic\Color.h>

namespace sgl {
	class String : public Drawable {
	private:
		std::string _text;
		bool _changed;

	public:
		enum class Mode : short {
			Solid,
			Shaded,
			Blended
		};

		Mode mode;

		explicit String(const std::string& str, Mode m = Mode::Solid);

		void operator =(const std::string& str) {
			if (str != _text) {
				_text = str;
				_changed = true;
			}
		}

		void operator =(const String& txt) {
			const std::string& str = txt._text;

			if (str != _text) {
				_text = str;
				_changed = true;
			}
		}

	protected:
		virtual void draw(const Window& wnd) const;
	};
}