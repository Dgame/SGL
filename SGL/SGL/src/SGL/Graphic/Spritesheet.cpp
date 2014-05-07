#include <SGL/Graphic/Spritesheet.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	Spritesheet::Spritesheet(Texture& tex, int16 loopCount) : Sprite(tex) {
		setLoopCount(loopCount);
	}

	void Spritesheet::draw(const Window& wnd) const {
		const float dx = this->position.x;
		const float dy = this->position.y;
		const float dw = this->width();
		const float dh = this->height();

		const float vertices[] = {
			dx, dy,
			dx + dw, dy,
			dx + dw, dy + dh,
			dx, dy + dh
		};

		const Texture* tex = Sprite::getTexture();
		if (tex == nullptr)
			return;

		const float tx = (0.f + this->view.x) / tex->width();
		const float ty = (0.f + this->view.y) / tex->height();
		const float tw = (0.f + this->view.width) / tex->width();
		const float th = (0.f + this->view.height) / tex->height();

		const float texCoords[] = {
			tx, ty,
			tx + tw, ty,
			tx + tw, ty + th,
			tx, ty + th
		};

		wnd.draw(Primitive(vertices), texCoords, tex);
	}

	bool Spritesheet::slide(Grid grid) {
		if (_loopCount > 0 && _loopCount < _passedLoops)
			return false;

		if ((_lastTick + tickOffset) > Clock::GetTicks())
			return false;

		const Texture* tex = Sprite::getTexture();
		if (tex == nullptr)
			return false;

		_lastTick = Clock::GetTicks();

		if ((grid & Grid::Column) == 0) {
			// to avoid a cast...
			this->view.y = this->row;
			this->view.y *= this->view.height;
		}

		if (grid & Grid::Row) {
			if ((this->view.x + this->view.width) < tex->width())
				this->view.x += this->view.width;
			else {
				this->view.x = 0;
				if ((grid & Grid::Column) == 0)
					_passedLoops++;
			}
		}

		if (grid & Grid::Column && this->view.x == 0) {
			if ((this->view.y + this->view.height) < tex->height())
				this->view.y += this->view.height;
			else {
				this->view.y = 0;
				_passedLoops++;
			}
		}

		return true;
	}
}