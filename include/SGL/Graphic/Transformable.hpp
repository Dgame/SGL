#ifndef SGL_TRANSFORMABLE_HPP
#define SGL_TRANSFORMABLE_HPP

#include <SGL/Math/mat4.hpp>

namespace sgl {
    class Transformable {
    protected:
        vec2f _local_center;
        vec2f _position;

        float _scale = 1.f;
        float _rotation = 0.f;

    protected:
        void _notifyTransform() {
            _was_transformed = true;
        }

        bool _wasTransformed() const {
            return _was_transformed;
        }

    private:
        mutable mat4x4 _matrix;
        mutable bool _was_transformed = true;

    public:
        virtual ~Transformable() { }

        const mat4x4& getMatrix() const;

        void setPosition(float x, float y);
        void setPosition(const vec2f&);

        const vec2f& getPosition() const {
            return _position;
        }

        void setCenter(float x, float y);
        void setCenter(const vec2f&);

        const vec2f& getCenter() const {
            return _local_center;
        }

        void setScale(float the_scale);
        void scale(float the_scale);

        float getScale() const {
            return _scale;
        }

        void setRotation(float rotation);
        void rotate(float rotation);

        float getRotation() const {
            return _rotation;
        }
    };
}

#endif
