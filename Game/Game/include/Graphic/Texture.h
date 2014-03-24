#pragma once

#ifdef _DEBUG
#include <Core\Output.h>
#endif

#include <memory>
#include <Core\OpenGL.h>
#include <Core\Types.h>
#include <Math\Rect.h>
#include <Graphic\Surface.h>

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
	uint32 _gl_id;
	uint16 _width;
	uint16 _height;

	bool _repeat, _smooth;

	Format _format;

public:
	explicit Texture();
	explicit Texture(const Surface& srfc);

	//Texture(const Texture& tex) = delete;

	virtual ~Texture() {
		glDeleteTextures(1, &_gl_id);
	}

	void loadFrom(const Surface& srfc);
	void loadFromMemory(void* pixels, uint16 width, uint16 height, Format format = Format::None);

	void enableRepeat(bool repeat) {
		_repeat = repeat;
	}

	void enableSmooth(bool smooth) {
		_smooth = smooth;
	}

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
		return _gl_id;
	}

	/**
	* Binds this Texture.
	* Means this Texture is now activated.
	*/
	void bind() const {
		glBindTexture(GL_TEXTURE_2D, _gl_id);
	}

	/**
	* Binds this Texture.
	* Means this Texture is now deactivated.
	*/
	void unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void copy(Texture& tex, const ShortRect& rect) const;
	void update(const ShortRect& rect, void* pixels) const;

	std::unique_ptr<uint32> pixels() const;
};