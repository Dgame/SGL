#ifndef SGL_SHAPE_HPP
#define SGL_SHAPE_HPP

#include <vector>
#include <SGL/Graphic/Drawable.hpp>
#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Math/Vertex.hpp>

namespace sgl {
    class Texture;
    enum class Geometry;

    class Shape : public Drawable, public Transformable {
    private:
        Texture* _texture = nullptr;
        std::vector<Vertex> _vertices;

    protected:
        virtual void draw(const Window*) const override;

    public:
        Geometry geometry;

        explicit Shape(Geometry geo);
        virtual ~Shape() { }

        void append(const Vertex&);
        void setTexture(Texture*, const FloatRect* texRect = nullptr);

        const Texture* getTexture() const {
            return _texture;
        }

        void setTextureRect(const FloatRect&);
        FloatRect getBoundingRect() const;

        const std::vector<Vertex>& getVertices() const {
            return _vertices;
        }

        std::vector<Vertex>& getVertices() {
            return _vertices;
        }

        void setColor(const Color4b&);
    };
}

#endif
