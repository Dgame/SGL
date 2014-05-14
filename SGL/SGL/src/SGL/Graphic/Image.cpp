#include <SGL/Graphic/Image.hpp>

namespace sgl {
	Image::Image() : Texture() {

	}

	Image::Image(const std::string& filename) : Image() {
		this->loadFromFile(filename);
	}

	Image::Image(const Surface& srfc, Texture::Format format) {
		this->loadFromSurface(srfc, format);
	}

	Image::Image(const void* pixels, uint16 width, uint16 height, Texture::Format format) : Texture(pixels, width, height, format) {

	}

	Image::Image(const Image& img) : Texture(img) {

	}

	void Image::loadFromSurface(const Surface& srfc, Texture::Format format) {
		if (format == Texture::Format::None) {
			if (!srfc.isMask(Surface::Mask::Red, 255))
				format = srfc.bits() == 32 ? Texture::Format::BGRA : Texture::Format::BGR;
			else
				format = srfc.bits() == 32 ? Texture::Format::RGBA : Texture::Format::RGB;
		}

		Texture::loadFromMemory(srfc.pixels(), srfc.width(), srfc.height(), format);
	}

	void Image::loadFromFile(const std::string& filename) {
		Surface srfc(filename);

		this->loadFromSurface(srfc);
	}

	void Image::saveToFile(const std::string& filename) const {
		const std::unique_ptr<uint32> pixels = Texture::pixels();

		Surface srfc(pixels.get(), Texture::width(), Texture::height(), fmtToBytes(Texture::format()) * 8);
		srfc.saveToFile(filename);
	}
}