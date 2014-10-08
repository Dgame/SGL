#include <SGL/Graphic/Transformable.hpp>
#include <SGL/Core/Config.hpp>

namespace sgl {
    const mat4x4& Transformable::getMatrix() const {
        if (_wasTransformed()) {
            const vec2f global_center = _position + _local_center;
            _matrix.loadIdentity().rotate(_rotation, global_center).scale(_scale, global_center).translate(_position);
            _was_transformed = false;
#if SGL_DEBUG
            printf("Update Transform Matrix\n");
#endif
        }

        return _matrix;
    }

    void Transformable::setPosition(float x, float y) {
        _position.x = x;
        _position.y = y;

        _notifyTransform();
    }

    void Transformable::setPosition(const vec2f& pos) {
        _position = pos;

        _notifyTransform();
    }

    void Transformable::setCenter(const vec2f& center) {
        _local_center = center;

        _notifyTransform();
    }

    void Transformable::setCenter(float x, float y) {
        _local_center.x = x;
        _local_center.y = y;

        _notifyTransform();
    }

    void Transformable::setScale(float the_scale) {
        _scale = the_scale;

        _notifyTransform();
    }

    void Transformable::scale(float the_scale) {
        _scale += the_scale;

        _notifyTransform();
    }

    void Transformable::setRotation(float rotation) {
        _rotation = rotation;
        if (_rotation < 0 || _rotation > 360)
            _rotation = 0;

        _notifyTransform();
    }

    void Transformable::rotate(float rotation) {
        _rotation += rotation;
        if (_rotation < 0 || _rotation > 360)
            _rotation = 0;

        _notifyTransform();
    }
}
