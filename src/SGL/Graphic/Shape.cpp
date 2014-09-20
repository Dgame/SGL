#include <SGL/Graphic/Shape.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
    void Shape::draw(const Window* wnd) const {
        wnd->draw(this->geometry, this->getMatrix(), _vertices, _texture);
    }

    Shape::Shape(Geometry geo) : geometry(geo) {

    }

    void Shape::append(const Vertex& vertex) {
        _vertices.push_back(vertex);
    }

    void Shape::setTexture(Texture* texture, const FloatRect* texRect) {
        _texture = texture;

        if (texture) {
            if (texRect)
                this->setTextureRect(*texRect);
            else
                this->setTextureRect(FloatRect(0, 0, texture->width(), texture->height()));
        }
    }

    void Shape::setTextureRect(const FloatRect& texRect) {
        const FloatRect bounds = this->getBoundingRect();
        for (Vertex& v : _vertices) {
            const float xratio = bounds.width > 0 ? (v.position.x - bounds.x) / bounds.width : 0;
            const float yratio = bounds.height > 0 ? (v.position.y - bounds.y) / bounds.height : 0;

            v.texCoord.x = (texRect.x + texRect.width * xratio) / _texture->width();
            v.texCoord.y = (texRect.y + texRect.height * yratio) / _texture->height();
        }
    }

    FloatRect Shape::getBoundingRect() const {
        float left = _vertices[0].position.x;
        float top = _vertices[0].position.y;
        float right = _vertices[0].position.x;
        float bottom = _vertices[0].position.y;

        for (const Vertex& v : _vertices) {
            // Update left and right
            if (v.position.x < left)
                left = v.position.x;
            else if (v.position.x > right)
                right = v.position.x;
            // Update top and bottom
            if (v.position.y < top)
                top = v.position.y;
            else if (v.position.y > bottom)
                bottom = v.position.y;
        }

        return FloatRect(left, top, right - left, bottom - top);
    }

    void Shape::setColor(const Color4b& col) {
        for (Vertex& v : _vertices) {
            v.setColor(col);
        }
    }

    void Shape::move(float x, float y) {
        for (Vertex& v : _vertices) {
            v.position.x += x;
            v.position.y += y;
        }

        Transformable::transformed();
    }

    void Shape::move(const vec2f& offset) {
        this->move(offset.x, offset.y);
    }
}
