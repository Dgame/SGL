#ifndef SGL_FONT_HPP
#define SGL_FONT_HPP

#include <string>
#include <SDL_ttf.h>
#include <SGL/Core/Types.hpp>
#include <SGL/Graphic/Color.hpp>

namespace sgl {
	class Surface;

	class Font {
	private:
		TTF_Font* _ttf;
		uint8 _fontSize;

	public:
		enum Style {
			/*
			* Used to indicate regular, normal, plain rendering style.
			*/
			Normal = TTF_STYLE_NORMAL,
			/*
			* Used to indicate bold rendering style.This is used in a bitmask along with other styles.
			*/
			Bold = TTF_STYLE_BOLD,
			/*
			* Used to indicate italicized rendering style.This is used in a bitmask along with other styles.
			*/
			Italic = TTF_STYLE_ITALIC,
			/*
			* Used to indicate underlined rendering style.This is used in a bitmask along with other styles.
			*/
			Underline = TTF_STYLE_UNDERLINE,
			/*
			* Used to indicate strikethrough rendering style.This is used in a bitmask along with other styles.
			*/
			StrikeThrough = TTF_STYLE_STRIKETHROUGH
		};

		enum Mode {
			Solid,
			Shaded,
			Blended
		};

		explicit Font(const std::string&, uint8 fontSize);
		Font(const Font&) = delete;
		virtual ~Font();

		void loadFromFile(const std::string&, uint8 fontSize);

		void setStyle(Style style);
		Style getStyle() const;

		Surface render(const std::string&, const Color4b& fg, const Color4b& bg, Mode mode = Mode::Solid) const;
	};
}

#endif
