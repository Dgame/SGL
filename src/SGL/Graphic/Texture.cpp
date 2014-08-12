#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	Texture::Texture(const Surface& srfc) {
		this->load(srfc);
	}

	Texture::~Texture() {
		if (_texId != 0)
			glDeleteTextures(1, &_texId);
	}

	void Texture::setRepeat(bool repeat) {
		if (repeat != _repeat) {
			_repeat = repeat;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP);
		}
	}

	void Texture::setSmooth(bool smooth) {
		if (smooth != _smooth) {
			_smooth = smooth;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
		}
	}

	void Texture::create(uint16 width, uint16 height) {
		this->loadFromMemory(nullptr, width, height);
	}

	void Texture::load(const Surface& srfc) {
		this->loadFromMemory(srfc.pixels(), srfc.width(), srfc.height());
	}

	void Texture::loadFromMemory(void* pixels, uint16 width, uint16 height) {
		if (_texId == 0)
			glGenTextures(1, &_texId);

		this->bind();
		
		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);

		_width = width;
		_height = height;

		this->unbind();
	}

	void Texture::fetchPixelData(void* pixels) const {
		if (pixels != nullptr) {
			this->bind();

			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			this->unbind();
		}
	}
}