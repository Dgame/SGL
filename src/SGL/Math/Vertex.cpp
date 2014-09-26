#include <SGL/Math/Vertex.hpp>

namespace sgl {
    Vertex::Vertex(float x, float y) : position(x, y) {

    }

    Vertex::Vertex(const vec2f& pos, const vec2f& texcoord, const Color4b& col) : position(pos), texCoord(texcoord) {
        this->setColor(col);
    }
}
