#ifndef SGL_SPRITE_HPP
#define SGL_SPRITE_HPP

#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Math/vec2.hpp>
#include <SGL/Math/Vertex.hpp>
#include <SGL/Math/Rect.hpp>

namespace sgl {
    class Texture;

    class Sprite : public Drawable, public Transformable {
    protected:
        Texture* _texture;
        ShortRect _clipRect;
        Vertex _vertices[4];

        virtual void draw(const Window*) const override;
        void _updateVertices();
        void _adjustClipRect();

    public:
        Sprite() = default;
        explicit Sprite(Texture&);
        virtual ~Sprite() { }

        void setTexture(Texture&);

        const Texture* getTexture() const {
            return _texture;
        }

        void setColor(const Color4b&);
        void setClipRect(const ShortRect&);

        const ShortRect& getClipRect() const {
            return _clipRect;
        }

        void move(float x, float y);
        void move(const vec2f&);
    };
}

#endif
