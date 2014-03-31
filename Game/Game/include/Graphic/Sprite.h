#pragma once


#include <Graphic\Drawable.h>
#include <Graphic\Texture.h>
#include <Math\Vector2.h>
#include <Math\Rect.h>
#include <Window\Window.h>

namespace sgl {
	class Sprite : public Drawable {
	protected:
		virtual void draw(const Window& wnd) const override;

	public:
		Texture& texture;
		Vector2f position;

		explicit Sprite(Texture& tex);

		virtual uint16 width() const {
			return this->texture.width();
		}

		virtual uint16 height() const {
			return this->texture.height();
		}

		ShortRect getClipRect() const {
			int16 vx = static_cast<int16>(position.x);
			int16 vy = static_cast<int16>(position.y);

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