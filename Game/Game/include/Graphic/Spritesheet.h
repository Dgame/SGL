#pragma once

#include <Graphic\Sprite.h>
#include <Math\Rect.h>
#include <System\Clock.h>

namespace sgl {
	class Spritesheet : public Sprite {
	protected:
		int16 _loopCount;
		uint16 _passedLoops;
		uint32 _lastTick;

		virtual void draw(const Window& wnd) const override;

	public:
		/**
		* The Grid
		*/
		enum Grid : uint8 {
			None = 0, /// No Grid is used
			Row = 1,  /// Only Rows are used
			Column = 2, /// Only Columns are used
			Both = Row | Column /// Both, Columns <b>and</b> Rows are used
		};

		ShortRect view;
		uint16 tickOffset;
		uint8 row;

		explicit Spritesheet(Texture& tex, int16 loopCount = -1);

		void setLoopCount(int16 loopCount) {
			_loopCount = loopCount;
			_passedLoops = 0;
		}

		virtual uint16 width() const override {
			return this->view.width;
		}

		virtual uint16 height() const override {
			return this->view.height;
		}

		virtual bool slide(Grid grid = Grid::Both);

		virtual bool collideWith(const ShortRect& rect) const override {
			return view.intersects(rect);
		}

		virtual bool collideWith(const Sprite& other) const override {
			return collideWith(other.getClipRect());
		}

		virtual bool collideWith(const Spritesheet& other) const {
			return collideWith(other.view);
		}
	};
}