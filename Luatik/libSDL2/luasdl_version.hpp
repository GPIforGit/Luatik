#pragma once

static int l_Version_Get(lua_State* L) {
	SDL_version ver;
	SDL_GetVersion(&ver);
	lua_pushinteger(L,ver.major);
	lua_pushinteger(L,ver.minor);
	lua_pushinteger(L,ver.patch);
	lua_pushinteger(L,SDL_VERSIONNUM((lua_Integer)ver.major, (lua_Integer)ver.minor, (lua_Integer)ver.patch));
	return 4;
}

static int l_Version_AtLeast(lua_State* L) {
	SDL_version ver;
	SDL_GetVersion(&ver);
	lua_pushboolean(
		L,
		SDL_VERSIONNUM((lua_Integer)ver.major, (lua_Integer)ver.minor, (lua_Integer)ver.patch)
		>=
		SDL_VERSIONNUM(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2), luaL_checkinteger(L, 3))
	);
	return 1;
}


