#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>
#include <SGL/Core/OpenGL.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	class Texture {
	public:
		/**
		* Supported Texture Format
		*/
		enum class Format : uint16 {
			None = 0,	/// Take this if you want to declare that you give no Format.
			RGB = GL_RGB,	/// Alias for GL_RGB
			RGBA = GL_RGBA,	/// Alias for GL_RGBA
			BGR = GL_BGR_EXT,	/// Alias for GL_BGR
			BGRA = GL_BGRA_EXT,	/// Alias for GL_BGRA 
			RGBA16 = GL_RGBA16,	/// 16 Bit RGBA Format
			RGBA8 = GL_RGBA8,	/// 8 Bit RGBA Format
			Alpha = GL_ALPHA,	/// Alias for GL_ALPHA
		};

	private:
		uint32 _glTexId = 0;
		uint16 _width = 0;
		uint16 _height = 0;

		bool _repeat = true;
		bool _smooth = false;

		Format _format;

	public:
		Texture();
		explicit Texture(const void* pixels, uint16 width, uint16 height, Format format = Format::None);
		Texture(const Texture& tex);

		virtual ~Texture();

		Texture& operator =(const Texture& tex);

		void create(uint16 width, uint16 height, Format format = Format::None) {
			this->loadFromMemory(nullptr, width, height, format);
		}

		void setRepeat(bool repeat);
		void setSmooth(bool smooth);

		bool isRepeated() const {
			return _repeat;
		}

		bool isSmooth() const {
			return _smooth;
		}

		void loadFromMemory(const void* pixels, uint16 width, uint16 height, Format format = Format::None);

		uint16 width() const {
			return _width;
		}

		uint16 height() const {
			return _height;
		}

		Format format() const {
			return _format;
		}

		uint32 id() const {
			return _glTexId;
		}

		/**
		* Binds this Texture.
		* Means this Texture is now activated.
		*/
		void bind() const {
			glBindTexture(GL_TEXTURE_2D, _glTexId);
		}

		/**
		* Binds this Texture.
		* Means this Texture is now deactivated.
		*/
		void unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void copy(const Texture& tex, const ShortRect& rect) const;
		void update(const ShortRect& rect, const void* pixels) const;
		void update(const void* pixels) const;
		std::unique_ptr<uint32> pixels() const;
	};

	uint8 fmtToBytes(Texture::Format fmt);
}

#endif