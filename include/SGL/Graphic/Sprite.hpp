#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SGL/Core/Scope.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Primitive.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Vector2.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	class Sprite : public Drawable, public Transformable {
	private:
		const Texture* _texture = nullptr;

	protected:
		virtual void draw(const Window& wnd) const override;

	public:
		Sprite() = default;
		explicit Sprite(const Texture& tex);

		void setTexture(const Texture& tex) {
			_texture = &tex;
			_viewport.setSize(this->width(), this->height());
		}

		const Texture* getTexture() const {
			return _texture;
		}

		virtual uint16 width() const {
			if (_texture != nullptr)
				return _texture->width();
			return 0;
		}

		virtual uint16 height() const {
			if (_texture != nullptr)
				return _texture->height();
			return 0;
		}

		virtual bool collideWith(const FloatRect& rect) const {
			return getViewport().intersects(rect);
		}

		virtual bool collideWith(const Sprite& other) const {
			return collideWith(other.getViewport());
		}
	};
}

#endif