#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Graphic/Texture.hpp>
#include <SGL/Math/Geometry.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
    Sprite::Sprite(Texture& tex) : _texture(&tex), _clipRect(0, 0, tex.width(), tex.height()) {
        _updateVertices();
        this->setColor(Color4b::White);
    }

    void Sprite::_updateVertices() {
        float tx = 0, ty = 0, tw = 1, th = 1;

        if (!_clipRect.isEmpty()) {
            const FloatRect fclip(_clipRect);

            tx = fclip.x / _texture->width();
            ty = fclip.y / _texture->height();
            tw = fclip.width / _texture->width();
            th = fclip.height / _texture->height();
        }

        const float tx_tw = tx + tw;
        const float ty_th = ty + th;

        _vertices[0].position = vec2f(0, 0);
        _vertices[0].texCoord = vec2f(tx, ty);

        _vertices[1].position = vec2f(_clipRect.width, 0);
        _vertices[1].texCoord = vec2f(tx_tw, ty);

        _vertices[2].position = vec2f(0, _clipRect.height);
        _vertices[2].texCoord = vec2f(tx, ty_th);

        _vertices[3].position = vec2f(_clipRect.width, _clipRect.height);
        _vertices[3].texCoord = vec2f(tx_tw, ty_th);
    }

    void Sprite::draw(const Window* wnd) const {
        wnd->draw(Geometry::TriangleStrip, this->getMatrix(), *_texture, _vertices, 4);
    }

    void Sprite::setTexture(Texture& tex) {
        _texture = &tex;
        _clipRect.x = _clipRect.y = 0;
        _clipRect.width = tex.width();
        _clipRect.height = tex.height();

        _updateVertices();
    }

    void Sprite::setColor(const Color4b& col) {
        for (Vertex& v : _vertices) {
            v.setColor(col);
        }
    }

    void Sprite::setClipRect(const ShortRect& clipRect) {
        _clipRect = clipRect;

        _updateVertices();
    }

    void Sprite::move(float x, float y) {
        _position.x += x;
        _position.y += y;

        _notifyTransform();
    }

    void Sprite::move(const vec2f& vec) {
        _position += vec;

        _notifyTransform();
    }
}
