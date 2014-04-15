#include <SGL/Graphic\Spritesheet.hpp>

namespace sgl {
	Spritesheet::Spritesheet(Texture& tex, int16 loopCount) : Sprite(tex), _lastTick(0), tickOffset(0), row(0) {
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

		const float tx = (0.f + this->view.x) / Sprite::texture.width();
		const float ty = (0.f + this->view.y) / Sprite::texture.height();
		const float tw = (0.f + this->view.width) / Sprite::texture.width();
		const float th = (0.f + this->view.height) / Sprite::texture.height();

		const float texCoords[] = {
			tx, ty,
			tx + tw, ty,
			tx + tw, ty + th,
			tx, ty + th
		};

		wnd.draw(vertices, texCoords, Sprite::texture);
	}

	bool Spritesheet::slide(Grid grid) {
		if (_loopCount > 0 && _loopCount < _passedLoops)
			return false;

		if ((_lastTick + tickOffset) > Clock::GetTicks())
			return false;

		_lastTick = Clock::GetTicks();

		if ((grid & Grid::Column) == 0) {
			// to avoid a cast...
			this->view.y = this->row;
			this->view.y *= this->view.height;
		}

		if (grid & Grid::Row) {
			if ((this->view.x + this->view.width) < Sprite::texture.width())
				this->view.x += this->view.width;
			else {
				this->view.x = 0;
				if ((grid & Grid::Column) == 0)
					_passedLoops++;
			}
		}

		if (grid & Grid::Column && this->view.x == 0) {
			if ((this->view.y + this->view.height) < Sprite::texture.height())
				this->view.y += this->view.height;
			else {
				this->view.y = 0;
				_passedLoops++;
			}
		}

		return true;
	}
}