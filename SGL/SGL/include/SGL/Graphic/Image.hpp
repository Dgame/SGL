#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SGL/Graphic/Texture.hpp>
#include <SGL/Graphic/Surface.hpp>

namespace sgl {
	class Image : public Texture {
	public:
		Image();
		explicit Image(const std::string& filename);
		explicit Image(const Surface& srfc, Texture::Format format = Texture::Format::None);
		explicit Image(const void* pixels, uint16 width, uint16 height, Texture::Format format = Texture::Format::None);
		Image(const Image& img);

		void loadFromSurface(const Surface& srfc, Texture::Format format = Texture::Format::None);
		void loadFromFile(const std::string& filename);
		void saveToFile(const std::string& filename) const;
	};
}

#endif