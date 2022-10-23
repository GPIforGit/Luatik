#pragma once

static int l_mouse_GetFocus(lua_State* L) {
	pushWindow(L, SDL_GetMouseFocus());
	return 1;
}

static int l_mouse_GetState(lua_State* L) {
	int x, y;
	pushMouseButton(L, SDL_GetMouseState(&x, &y));
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	return 3;
}

static int l_mouse_GetGlobalState(lua_State* L) {
	int x, y;
	pushMouseButton(L, SDL_GetMouseState(&x, &y));
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	return 3;
}

static int l_mouse_GetRelativeState(lua_State* L) {
	int x, y;
	pushMouseButton(L, SDL_GetMouseState(&x, &y));
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	return 3;
}

static int l_mouse_WarpInWindow(lua_State* L) {
	SDL_Window* win = checkWindowOrNil(L, 1);
	int x = (int)checkroundnumber(L, 2);
	int y = (int)checkroundnumber(L, 3);
	SDL_WarpMouseInWindow(win, x, y);
	return 0;
}

static int l_mouse_WarpGlobal(lua_State* L) {
	int x = (int)checkroundnumber(L, 1);
	int y = (int)checkroundnumber(L, 2);
	lua_pushboolean(L, SDL_WarpMouseGlobal(x, y) == 0);
	return 1;
}

static int l_mouse_SetRelativeMode(lua_State* L) {
	SDL_bool state =(SDL_bool)lua_toboolean(L, 1);
	lua_pushboolean(L, SDL_SetRelativeMouseMode(state) == 0);
	return 1;
}

static int l_mouse_Capture(lua_State* L) {
	SDL_bool state = (SDL_bool)lua_toboolean(L, 1);
	lua_pushboolean(L, SDL_CaptureMouse(state) == 0);
	return 1;
}

static int l_mouse_GetRelativeMode(lua_State* L) {
	lua_pushboolean(L, SDL_GetRelativeMouseMode());
	return 1;
}

static int l_cursor_Create(lua_State* L) {
	if (lua_isstring(L, 1)) {
		SDL_SystemCursor c = checkSystemCursor(L, 1);
		pushCursor(L, SDL_CreateSystemCursor(c));
	}
	else {
		SDL_Surface* sur = checkSurface(L, 1);
		int hotx = (int)luaL_checkinteger(L, 2);
		int hoty = (int)luaL_checkinteger(L, 3);
		pushCursor(L, SDL_CreateColorCursor(sur, hotx, hoty));
	}
	return 1;
}

static int l_cursor_Set(lua_State* L) {
	SDL_Cursor* c = checkCursorOrNil(L, 1);
	SDL_SetCursor(c);
	return 0;
}

static int l_cursor_Get(lua_State* L) {
	pushCursor(L, SDL_GetCursor());
	return 1;
}

static int l_cursor_GetDefault(lua_State* L) {
	pushCursor(L, SDL_GetDefaultCursor());
	return 1;
}

static int l_cursor_Free(lua_State* L) {
	SDL_Cursor* c = checkCursor(L, 1);
	SDL_FreeCursor(c);
	luaEXT_setudata(L, 1, NULL);
	return 0;
}

static int l_cursor_Show(lua_State* L) {
	int state = checkEventState(L, 1);
	pushEventState(L, SDL_ShowCursor(state));
	return 1;
}








