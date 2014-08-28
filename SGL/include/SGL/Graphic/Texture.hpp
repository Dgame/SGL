#ifndef SGL_TEXTURE_HPP
#define SGL_TEXTURE_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/Core/Check.hpp>
#include <SGL/Core/GL.hpp>

namespace sgl {
	class Surface;

	class Texture {
	private:
		uint16 _width = 0;
		uint16 _height = 0;
		uint32 _texId = 0;

		bool _smooth = false;
		bool _repeat = false;

	public:
		enum Format {
			RGB = GL_RGB,
			RGBA = GL_RGBA,
			BGR = GL_BGR,
			BGRA = GL_BGRA
		};

		Texture() = default;
		explicit Texture(const Surface&);
		Texture(const Texture&) = delete;

		virtual ~Texture();

		void setRepeat(bool repeat);
		void setSmooth(bool smooth);

		bool isRepeated() const {
			return _repeat;
		}

		bool isSmooth() const {
			return _smooth;
		}

		uint16 width() const {
			return _width;
		}

		uint16 height() const {
			return _height;
		}

		void create(uint16 width, uint16 height);
		void load(const Surface&);
		void loadFromMemory(void*, uint16 width, uint16 height, Format fmt);

		/**
		* Binds this Texture.
		* Means this Texture is now activated.
		*/
		void bind() const {
			glCheck(glBindTexture(GL_TEXTURE_2D, _texId));
		}

		/**
		* Unbinds this Texture.
		* Means this Texture is now deactivated.
		*/
		void unbind() const {
			glCheck(glBindTexture(GL_TEXTURE_2D, 0));
		}

		void fetchPixelData(void*) const;
	};
}

#endif