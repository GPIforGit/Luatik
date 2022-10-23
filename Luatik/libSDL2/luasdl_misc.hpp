#pragma once

static int l_OpenURL(lua_State* L) {
	const char* url = luaL_checkstring(L, 1);
	lua_pushboolean(L, SDL_OpenURL(url)==0);
	return 1;
}
