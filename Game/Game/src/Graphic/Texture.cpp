#include <Graphic\Texture.h>

Texture::Texture() {
	glGenTextures(1, &_gl_id);
}

Texture::Texture(const Surface& srfc) : Texture() {
	this->loadFrom(srfc);
}

void Texture::loadFrom(const Surface& srfc) {
	Format fmt = srfc.depth() == 32 ? Format::RGBA : Format::RGB;

	this->loadFromMemory(srfc.pixels(), srfc.width(), srfc.height(), fmt);
}

void Texture::loadFromMemory(void* pixels, uint16 width, uint16 height, Format fmt) {
	if (fmt == Format::None)
		_format = Format::RGB;
	else
		_format = fmt;

	this->bind();

	GLenum gl_fmt = static_cast<GLenum>(_format);

	glTexImage2D(GL_TEXTURE_2D, 0, gl_fmt,
		width, height, 0, gl_fmt, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		_repeat ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		_repeat ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		_smooth ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		_smooth ? GL_LINEAR : GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D); // We want MipMaps

	_width = width;
	_height = height;
}

void Texture::copy(Texture& tex, const ShortRect& rect) const {
	std::unique_ptr<uint32> pixel = tex.pixels();

	update(rect, pixel.get());
}

void Texture::update(const ShortRect& rect, void* pixels) const {
	uint16 width = rect.width;
	uint16 height = rect.height;

	uint16 x = rect.x;
	uint16 y = rect.y;

	this->bind();

	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height,
		static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, pixels);
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

	std::unique_ptr<uint32> ptr = std::unique_ptr<uint32>(new uint32[msize]);

	glGetTexImage(GL_TEXTURE_2D, 0, static_cast<GLenum>(_format), GL_UNSIGNED_BYTE, ptr.get());

	return std::move(ptr);
}
