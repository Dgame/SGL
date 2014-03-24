#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

class Window;

class Drawable {
public:
	virtual ~Drawable() {

	}

protected:
	friend class Window;

	virtual void draw(const Window& wnd) const = 0;
};

#endif