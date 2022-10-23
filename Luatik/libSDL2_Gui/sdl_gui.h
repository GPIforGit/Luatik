#pragma once

#include <windows.h>
//#include <windowsx.h>
//#include <commctrl.h>
//#include <commdlg.h>
//#include <Shlobj.h>


#define SDL_MAIN_HANDLED
#include "../sdl2/SDL.h"
#include "../sdl2/SDL_syswm.h"
//#include "../sdl2/SDL_system.h"
//#include "../sdl2/SDL_ttf.h"

#include <string>
//#include <iostream>
//#include <algorithm>

#define SDLGUI_VERSION "0.1"

#include "../lua/lua.hpp"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static

/*
inline lua_Integer checkroundnumber(lua_State* L, int index) {
	return (lua_Integer)luaL_checknumber(L, index);
}
inline lua_Integer optroundnumber(lua_State* L, int index, lua_Integer opt) {
	return (lua_Integer)luaL_optnumber(L, index,(lua_Number)opt);
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

*/
