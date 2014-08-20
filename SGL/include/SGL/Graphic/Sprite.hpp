#ifndef SGL_SPRITE_HPP
#define SGL_SPRITE_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Math/vec2.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	class Texture;
	
	class Sprite : public Drawable, public Transformable {
	protected:
		Texture* _texture;
		FloatRect _boundingBox;

		virtual void draw(const Window*) const override;

	public:
		explicit Sprite(Texture&);

		void setTexture(Texture&);

		const Texture* getTexture() const {
			return _texture;
		}

		void setBoundingBox(const FloatRect& bounds) {
			_boundingBox = bounds;
		}

		const FloatRect& getBoundingBox() const {
			return _boundingBox;
		}

		bool collideWith(const FloatRect&) const;
		bool collideWith(const Sprite&) const;

		void setPosition(float x, float y) override;
		void setPosition(const vec2f&) override;

		void move(float x, float y);
		void move(const vec2f&);
	};
}

#endif