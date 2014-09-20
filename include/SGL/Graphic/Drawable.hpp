#ifndef SGL_DRAWABLE_HPP
#define SGL_DRAWABLE_HPP

namespace sgl {
    class Window;

    class Drawable {
    public:
        virtual ~Drawable() { }

    protected:
        friend class Window;

        virtual void draw(const Window*) const = 0;
    };
}

#endif
