#pragma once

#include <memory>
#include <Graphic\Drawable.h>
#include <Graphic\Texture.h>
#include <Math\Vector2.h>
#include <Math\Rect.h>

class Sprite : public Drawable {
private:
	std::shared_ptr<const Texture> _texture;

protected:
	virtual void draw(const Window& wnd) const override;

public:
	Vector2f position;

	explicit Sprite(const Texture& tex) : position(0, 0) {
		setTexture(tex);
	}

	void setTexture(const Texture& tex) {
		_texture = std::make_shared<const Texture>(tex);
	}

	const Texture* getTexture() const {
		return _texture.get();
	}

	ShortRect getClipRect() const {
		int16 vx = static_cast<int16>(position.x);
		int16 vy = static_cast<int16>(position.y);

		return ShortRect(vx, vy, _texture->width(), _texture->height());
	}

	virtual bool collideWith(const ShortRect& rect) const {
		return getClipRect().intersects(rect);
	}

	virtual bool collideWith(const Sprite& other) const {
		return collideWith(other.getClipRect());
	}
};