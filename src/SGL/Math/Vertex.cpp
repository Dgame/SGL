#include <SGL/Math/Vertex.hpp>

namespace sgl {
    Vertex::Vertex(float x, float y, float z) {
        this->position.x = x;
        this->position.y = y;
        this->position.z = z;
    }

    Vertex::Vertex(const vec3f& pos, const vec3f& texcoord, const Color4b& col) : position(pos), texCoord(texcoord) {
        this->setColor(col);
    }
}
