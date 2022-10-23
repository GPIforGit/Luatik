#pragma once



#define ID_HWND "luatik.HWND"
inline HWND checkHWND(lua_State* L, int index) {
	return (HWND)luaEXT_checkuintegerornil(L, index, ID_HWND);
}
inline void pushHWND(lua_State* L, HWND value) {
	luaEXT_pushuinteger(L, (lua_Integer)value, ID_HWND);
}


#define ID_Window "SDL.Window"//
inline SDL_Window* checkWindow(lua_State* L, int index) {
	return (SDL_Window*)luaEXT_checkudata(L, index, ID_Window);
}
inline SDL_Window* checkWindowOrNil(lua_State* L, int index) {
	return (SDL_Window*)luaEXT_checkudataornil(L, index, ID_Window);
}
inline HWND GetHWND(SDL_Window* win) {
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	if (win && SDL_GetWindowWMInfo(win, &info)) {
		return info.info.win.window;
	}
	return 0;
}

