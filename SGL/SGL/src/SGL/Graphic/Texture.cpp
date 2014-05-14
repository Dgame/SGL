#include <SGL/Graphic/Texture.hpp>

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
		
	}

	Texture::Texture(const void* pixels, uint16 width, uint16 height, Format format) {
		this->loadFromMemory(pixels, width, height, format);
	}

	Texture::Texture(const Texture& tex) {
		const std::unique_ptr<uint32> pixels = tex.pixels();
		this->loadFromMemory(pixels.get(), tex.width(), tex.height(), tex.format());
	}

	Texture::~Texture() {
		if (_glTexId != 0)
			glCheck(glDeleteTextures(1, &_glTexId));
	}

	Texture& Texture::operator =(const Texture& tex) {
		Texture temp(tex);

		std::swap(_width, temp._width);
		std::swap(_height, temp._height);
		std::swap(_glTexId, temp._glTexId);
		std::swap(_smooth, temp._smooth);
		std::swap(_repeat, temp._repeat);

		return *this;
	}

	void Texture::setRepeat(bool repeat) {
		if (repeat != _repeat) {
			_repeat = repeat;

			glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP));
			glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP));
		}
	}

	void Texture::setSmooth(bool smooth) {
		if (smooth != _smooth) {
			_smooth = smooth;

			glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST));
			glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST));
		}
	}

	void Texture::loadFromMemory(const void* pixels, uint16 width, uint16 height, Format fmt) {
		if (_glTexId == 0)
			glCheck(glGenTextures(1, &_glTexId));

		_format = fmt == Format::None ? Format::RGB : fmt;

		this->bind();

		glCheck(glBindTexture(GL_TEXTURE_2D, _glTexId));
		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, fmtToBytes(_format), width, height, 0, static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, pixels));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST));

		_width = width;
		_height = height;

		this->unbind();
	}

	void Texture::copy(const Texture& tex, const ShortRect& rect) const {
		const std::unique_ptr<uint32> pixels = tex.pixels();
		this->update(rect, pixels.get());
	}

	void Texture::update(const ShortRect& rect, const void* pixels) const {
		const uint16 width = rect.width;
		const uint16 height = rect.height;
		const uint16 x = rect.x;
		const uint16 y = rect.y;

		this->bind();

		glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height,
			static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, pixels));

		this->unbind();
	}

	void Texture::update(const void* pixels) const {
		this->bind();

		glCheck(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, pixels));

		this->unbind();
	}

	std::unique_ptr<uint32> Texture::pixels() const {
		const uint8 bits = fmtToBytes(_format);
		const uint32 msize = _width * _height * bits;
		if (msize == 0)
			return nullptr;

		this->bind();

		uint32* ptr = new uint32[msize];
		glGetTexImage(GL_TEXTURE_2D, 0, static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, ptr);

		this->unbind();

		return std::unique_ptr<uint32>(ptr);
	}
}