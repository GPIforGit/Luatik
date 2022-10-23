#pragma once


#define ROOTLIB "SDL"

#define SDLWARP_VERSION "0.2"
#define SDL_LICENSE "(C) Sam Lantinga"

#include "../lua/lua.hpp"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static


#define SDL_MAIN_HANDLED
#include "../sdl2/SDL.h"
#include "../sdl2/SDL_syswm.h"

inline lua_Integer checkroundnumber(lua_State* L, int index) {
	return (lua_Integer)luaL_checknumber(L, index);
}

inline lua_Integer getKeyIndexInteger(lua_State* L, int table, const char* key, int index) {
	lua_Integer ret;
	if (lua_getfield(L, table, key) == LUA_TNIL) {
		lua_pop(L, 1);
		lua_geti(L, table, index);
	}
	ret = (lua_Integer)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return ret;
}
inline lua_Number getKeyIndexNumber(lua_State* L, int table, const char* key, int index) {
	lua_Number ret;
	if (lua_getfield(L, table, key) == LUA_TNIL) {
		lua_pop(L, 1);
		lua_geti(L, table, index);
	}
	ret = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return ret;
}

