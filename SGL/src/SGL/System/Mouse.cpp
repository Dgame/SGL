#include <SGL/System/Mouse.hpp>
#include <SGL/Graphic/Surface.hpp>
#include <SGL/Window/Window.hpp>

namespace sgl {
	namespace internal {
		void Cursor::operator =(SDL_Cursor* cursor) {
			SDL_FreeCursor(_cursor);
			_cursor = cursor;
			SDL_SetCursor(cursor);
		}

		Cursor::~Cursor() {
			SDL_FreeCursor(_cursor);
		}
	}

	void Mouse::SetCursor(Cursor cursor) {
		internal::CurrentCursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor));
	}

	void Mouse::SetCursor(const Surface& srfc) {
		internal::CurrentCursor = SDL_CreateColorCursor(srfc.ptr(), 0, 0);
	}

	void Mouse::ShowCursor(bool show) {
		SDL_ShowCursor(show);
	}

	bool Mouse::IsCursorShown() {
		return SDL_ShowCursor(-1) != 0;
	}

	void Mouse::SetPosition(const Window& wnd, int16 x, int16 y) {
		SDL_Window* sdl_window = SDL_GetWindowFromID(wnd.id());
		SDL_WarpMouseInWindow(sdl_window, x, y);
	}

	void Mouse::SetPosition(const Window& wnd, const Vector2s& position) {
		Mouse::SetPosition(wnd, position.x, position.y);
	}

	Vector2s Mouse::GetPosition() {
		int x, y;
		SDL_GetMouseState(&x, &y);

		return Vector2s(x, y);
	}

	bool Mouse::IsButtonPressed(Button btn) {
		const uint32 mask = SDL_GetMouseState(nullptr, nullptr);
		const uint32 btn_mask = SDL_BUTTON(static_cast<int>(btn));

		return (mask & btn_mask) != 0;
	}
}