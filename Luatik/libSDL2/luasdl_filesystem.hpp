#pragma once

static int l_Filesystem_GetBasePath(lua_State* L) {
	const char* path = SDL_GetBasePath();
	lua_pushstring(L, path);
	SDL_free((void*)path);
	return 1;
}

static int l_Filesystem_GetPrefPath(lua_State* L) {
	const char* org = luaL_checkstring(L, 1);
	const char* app = luaL_checkstring(L, 2);
	const char* path = SDL_GetPrefPath(org, app);
	lua_pushstring(L, path);
	SDL_free((void*)path);
	return 1;
}
