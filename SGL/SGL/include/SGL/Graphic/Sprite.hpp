#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Primitive.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Vector2.hpp>
#include <SGL/Math/Rect.hpp>
#include <SGL/Core/Scope.hpp>

namespace sgl {
	class Sprite : public Drawable, public Transform {
	private:
		Texture* _texture = nullptr;

	protected:
		virtual void draw(const Window& wnd) const override;

	public:
		Vector2f position;

		Sprite();
		explicit Sprite(Texture& tex);

		void setTexture(Texture& tex) {
			_texture = &tex;
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

		ShortRect getClipRect() const {
			const int16 vx = static_cast<int16>(position.x);
			const int16 vy = static_cast<int16>(position.y);

			return ShortRect(vx, vy, this->width(), this->height());
		}

		virtual bool collideWith(const ShortRect& rect) const {
			return getClipRect().intersects(rect);
		}

		virtual bool collideWith(const Sprite& other) const {
			return collideWith(other.getClipRect());
		}
	};
}

#endif