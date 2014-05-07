#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <SGL/Graphic/Sprite.hpp>
#include <SGL/Math/Rect.hpp>
#include <SGL/System/Clock.hpp>

namespace sgl {
	class Spritesheet : public Sprite {
	protected:
		int16 _loopCount = -1;
		uint16 _passedLoops = 0;
		uint32 _lastTick = 0;

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
		uint16 tickOffset = 0;
		uint8 row = 0;

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

#endif