#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	Texture::Texture(const Surface& srfc) {
		this->load(srfc);
	}

	Texture::~Texture() {
		if (_texId != 0)
			glCheck(glDeleteTextures(1, &_texId));
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

	void Texture::create(uint16 width, uint16 height) {
		this->loadFromMemory(nullptr, width, height, Format::RGB);
	}

	void Texture::load(const Surface& srfc) {
		Format fmt;
		switch (srfc.bytes()) {
			case 3: // no alpha channel
				if (srfc.getMask().red == 255)
					fmt = Format::RGB;
				else
					fmt = Format::BGR;
				break;
			case 4: // contains an alpha channel
				if (srfc.getMask().red == 255)
					fmt = Format::RGBA;
				else
					fmt = Format::BGRA;
				break;
			default:
				std::cerr << "Warning: the image is not truecolor." << std::endl;
				return;
		}

		this->loadFromMemory(srfc.pixels(), srfc.width(), srfc.height(), fmt);
	}

	void Texture::loadFromMemory(void* pixels, uint16 width, uint16 height, Format fmt) {
		if (_texId == 0)
			glCheck(glGenTextures(1, &_texId));

		this->bind();
		
		glCheck(glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, pixels));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST));

		_width = width;
		_height = height;

		this->unbind();
	}

	void Texture::fetchPixelData(void* pixels) const {
		if (pixels != nullptr) {
			this->bind();

			glCheck(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels));

			this->unbind();
		}
	}
}