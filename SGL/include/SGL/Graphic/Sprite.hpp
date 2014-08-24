#ifndef SGL_SPRITE_HPP
#define SGL_SPRITE_HPP

#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Math/vec2.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
	class Texture;
	
	class Sprite : public Drawable, public Transformable {
	protected:
		Texture* _texture;

		virtual void draw(const Window*) const override;

	public:
		FloatRect clipRect;

		explicit Sprite(Texture&);

		void setTexture(Texture&);

		const Texture* getTexture() const {
			return _texture;
		}

		FloatRect getBoundingRect() const;

		void move(float x, float y) override;
		void move(const vec2f&) override;
	};
}

#endif