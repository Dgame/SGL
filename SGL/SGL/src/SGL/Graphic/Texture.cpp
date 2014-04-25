#include <SGL/Graphic\Texture.hpp>
#include <SGL/Core\OpenGL.hpp>

namespace sgl {
	uint8 fmtToBytes(Texture::Format fmt) {
		switch (fmt) {
			default:
			case Texture::Format::None:
				return 0;
			case Texture::Format::BGR:
			case Texture::Format::RGB:
				return 3;
			case Texture::Format::RGBA:
			case Texture::Format::BGRA:
				return 4;
			case Texture::Format::RGBA16:
				return 2;
			case Texture::Format::RGBA8:
				return 1;
			case Texture::Format::Alpha:
				return 4;
		}
	}

	Texture::Texture() {
		glGenTextures(1, &_texId);
	}

	Texture::Texture(const Surface& srfc, Format format) : Texture() {
		this->loadFrom(srfc, format);
	}

	void Texture::loadFrom(const Surface& srfc, Format format) {
		if (format == Format::None) {
			if (srfc.isMask(Surface::Mask::Red, 0xff000000))
				format = srfc.bits() == 32 ? Format::BGRA : Format::BGR;
			else
				format = srfc.bits() == 32 ? Format::RGBA : Format::RGB;
		}
		
		this->loadFromMemory(srfc.pixels(), srfc.width(), srfc.height(), format);
	}

	void Texture::loadFromMemory(const void* pixels, uint16 width, uint16 height, Format fmt) {
		_format = fmt == Format::None ? Format::RGB : fmt;

		this->bind();

		glCheck(glBindTexture(GL_TEXTURE_2D, _texId));
		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, fmtToBytes(_format), width, height, 0, static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, pixels));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->repeat ? GL_REPEAT : GL_CLAMP));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->repeat ? GL_REPEAT : GL_CLAMP));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->smooth ? GL_LINEAR : GL_NEAREST));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->smooth ? GL_LINEAR : GL_NEAREST));

		_width = width;
		_height = height;

		this->unbind();
	}

	void Texture::copy(Texture& tex, const ShortRect& rect) const {
		std::unique_ptr<uint32> pixel = tex.pixels();
		update(rect, pixel.get());
	}

	void Texture::update(const ShortRect& rect, const void* pixels) const {
		const uint16 width = rect.width;
		const uint16 height = rect.height;
		const uint16 x = rect.x;
		const uint16 y = rect.y;

		this->bind();

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height,
						static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, pixels);

		this->unbind();
	}

	std::unique_ptr<uint32> Texture::pixels() const {
		uint8 depth = 0;
		if (_format == Format::RGBA || _format == Format::BGRA)
			depth = 32;
		else
			depth = 24;

		const uint32 msize = _width * _height * (depth / 8);
		if (msize == 0)
			return nullptr;

		this->bind();

		uint32* ptr = new uint32[msize];
		glGetTexImage(GL_TEXTURE_2D, 0, static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, ptr);

		this->unbind();

		return std::unique_ptr<uint32>(ptr);
	}
}