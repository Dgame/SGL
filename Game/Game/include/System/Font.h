#pragma once

#include <string>
#include <SDL_ttf.h>
#include <Core\Types.h>
#include <Graphic\Surface.h>

namespace sgl {
	class Font {
	private:
		TTF_Font* _ttf;
		uint8 _fontSize;

	public:
		enum class Style {
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

		enum class Hint {
			/*
			Used to indicate set hinting type to normal.
			This corresponds to the default hinting algorithm, optimized for standard gray - level rendering
			*/
			Normal = TTF_HINTING_NORMAL,
			/*
			Used to indicate set hinting type to light.
			A lighter hinting algorithm for non - monochrome modes.Many generated glyphs are more fuzzy
			but better resemble its original shape.A bit like rendering on Mac OS X.
			*/
			Light = TTF_HINTING_LIGHT,
			/*
			Used to indicate set hinting type to monochrome.
			Strong hinting algorithm that should only be used for monochrome output.
			The result is probably unpleasant if the glyph is rendered in non - monochrome modes.
			*/
			Mono = TTF_HINTING_MONO,
			/*
			Used to indicate set hinting type to none.
			No hinting is used so the font may become very blurry or messy at smaller sizes.
			*/
			None = TTF_HINTING_NONE
		};

		enum class Mode : short {
			Solid,
			Shaded,
			Blended
		};

		explicit Font(const std::string& filename, uint8 fontSize = 0) {
			loadFromFile(filename, fontSize);
		}

		virtual ~Font() {
			TTF_CloseFont(_ttf);
		}

		void loadFromFile(const std::string& filename, uint8 fontSize);

		void Font::setStyle(Font::Style style) {
			TTF_SetFontStyle(_ttf, static_cast<int>(style));
		}

		Font::Style Font::getStyle() const {
			return static_cast<Style>(TTF_GetFontStyle(_ttf));
		}

		void Font::setHint(Font::Hint hint) {
			TTF_SetFontHinting(_ttf, static_cast<int>(hint));
		}

		Font::Hint Font::getHint() const {
			return static_cast<Hint>(TTF_GetFontHinting(_ttf));
		}

		Surface render(const std::string& text, Color* fg = nullptr, Color* bg = nullptr, Mode mode = Mode::Solid) const;
	};
}