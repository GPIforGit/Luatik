#pragma once


static int l_error_get(lua_State* L) {
	const char* ret = SDL_GetError();
	lua_pushstring(L, ret);
	return 1;
}

static int l_error_clear(lua_State* L) {
	SDL_ClearError();
	return 0;
}

static int l_error_set(lua_State* L) {
	const char* msg = luaL_checkstring(L, 1);
	SDL_SetError(msg);
	return 0;
}





