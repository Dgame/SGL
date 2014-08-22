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

		virtual void draw(const Window*) const override;

	public:
		FloatRect view;

		explicit Sprite(Texture&);

		void setTexture(Texture&);

		const Texture* getTexture() const {
			return _texture;
		}

		FloatRect getBoundingBox() const;

		bool collideWith(const FloatRect&) const;
		bool collideWith(const Sprite&) const;

		void move(float x, float y) override;
		void move(const vec2f&) override;
	};
}

#endif