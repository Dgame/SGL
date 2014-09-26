#ifndef SGL_VERTEX_HPP
#define SGL_VERTEX_HPP

#include <SGL/Math/vec2.hpp>
#include <SGL/Graphic/Color.hpp>

namespace sgl {
    struct Vertex {
        vec2f position;
        vec2f texCoord;
        Color4f color = Color4f::Black;

        Vertex() = default;
        explicit Vertex(float x, float y);
        explicit Vertex(const vec2f&, const vec2f&, const Color4b&);

        void setColor(const Color4b& col) {
            this->color = Color4f(col);
        }
    };
}

#endif
