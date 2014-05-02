#include <SGL/System\Mouse.hpp>

namespace sgl {
	void Mouse::SetCursor(Cursor cursor) {
		SDL_Cursor* cursor_ptr = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor));
		internal::CurrentCursor = internal::Cursor(cursor_ptr);
	}

	void Mouse::SetCursor(const Surface& srfc) {
		SDL_Cursor* cursor_ptr = SDL_CreateColorCursor(srfc.ptr(), 0, 0);
		internal::CurrentCursor = internal::Cursor(cursor_ptr);
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