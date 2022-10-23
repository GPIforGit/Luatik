#include <windows.h>

#include "libMisc.h"
#include "../lua/lua.hpp"
/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static


static int l_Clamp(lua_State* L) {
	// 1 < 2 -->   1 < 2 < 3   or   3 < 1 < 2    or    1 < 3 < 2
	if (lua_compare(L, 1, 2, LUA_OPLE)) {
		if (lua_compare(L, 2, 3, LUA_OPLE)) {
			lua_pushvalue(L, 2);
		}
		else if (lua_compare(L, 3, 1, LUA_OPLE)) {
			lua_pushvalue(L, 1);
		}
		else {
			lua_pushvalue(L, 3);
		}
	}
	// 2 < 1 -->   2 < 1 < 3   or    3 < 2 < 1   or   2 < 3 < 1
	else if (lua_compare(L, 1, 3, LUA_OPLE)) {
		lua_pushvalue(L, 1);
	}
	else if (lua_compare(L, 3, 2, LUA_OPLE)) {
		lua_pushvalue(L, 2);
	}
	else {
		lua_pushvalue(L, 3);
	}

	return 1;
}

static int l_Split(lua_State* L) {
	std::string List = luaL_checkstring(L, 1);
	std::string sep = luaL_optstring(L, 2, " ;|,");

	lua_newtable(L);
	int i = 1;

	List += sep;

	size_t oposList = 0;
	size_t posList = 0;
	while ((posList = List.find_first_of(sep, oposList)) != std::string::npos) {

		if (posList - oposList > 0) {
			std::string ListWord = List.substr(oposList, posList - oposList);

			lua_pushstring(L, ListWord.c_str());
			lua_rawseti(L, -2, i++);

		}

		oposList = posList + 1;
	}
	return 1;
}

static int l_HasFlag(lua_State* L) {
	// only 3 parameter!
	lua_settop(L, 3);

	// 4 splitted table list
	lua_pushcfunction(L, l_Split);
	lua_pushvalue(L, 1);
	lua_pushvalue(L, 3);
	lua_call(L, 2, 1);

	// 5 splitted table search
	lua_pushcfunction(L, l_Split);
	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);
	lua_call(L, 2, 1);

	lua_len(L, 4);
	int llist = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_len(L, 5);
	int lsearch = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	int searchCount = 0;

	for (int i = 1; i <= lsearch; i++) {
		lua_geti(L, 5, i);
		const char* searchWord = lua_tostring(L, -1);

		for (int a = 1; a <= llist; a++) {
			lua_geti(L, 4, a);
			const char* listWord = lua_tostring(L, -1);

			if (strcmp(searchWord, listWord) == 0) {
				searchCount++;
			}
			lua_pop(L, 1);
		}

		lua_pop(L, 1);

	}

	lua_pushinteger(L, searchCount);
	return 1;
}


static int l_GetCurrentDirectory(lua_State* L) {
	int wlen = GetCurrentDirectoryW(0, NULL) + 1;

	void* ud;
	lua_Alloc allocf = lua_getallocf(L, &ud);

	size_t size = sizeof(wchar_t) * wlen;
	wchar_t* buf = (wchar_t*)allocf(ud, NULL, 0, size);

	if (buf == NULL) {
		lua_pushnil(L);
		return 1;
	}

	GetCurrentDirectoryW(wlen, buf);

	luaEXT_pushwstring(L, buf);

	
	allocf(ud, buf, size, 0);

	return 1;
}

static int l_SetCurrentDirectory(lua_State* L) {
	std::wstring path = luaEXT_checkwstring(L, 1);
	lua_pushboolean(L, SetCurrentDirectoryW(path.c_str()) != 0);
	return 1;
}

const struct luaL_Reg array_funcs[] = {	
	{"SetCurrentDirectory", l_SetCurrentDirectory},
	{"GetCurrentDirectory", l_GetCurrentDirectory},
	{NULL,NULL}
};

const struct luaL_Reg array_string_funcs[] = {
	{"hasflag",l_HasFlag},
	{"split",l_Split},
	{NULL,NULL}
};

const struct luaL_Reg array_math_funcs[] = {
	{"clamp",l_Clamp},
	{NULL,NULL}
};


LUAMOD_API int  luaopen_Misc(lua_State * L) {
	lua_getglobal(L, "string");
	luaL_setfuncs(L, array_string_funcs, 0);
	lua_pop(L,1);

	lua_getglobal(L, "math");
	luaL_setfuncs(L, array_math_funcs, 0);
	lua_pop(L, 1);

	lua_pushglobaltable(L);
	luaL_setfuncs(L, array_funcs, 0);

	lua_newtable(L);
	lua_pushfstring(L, "%s by GPI", MISC_VERSION);
	lua_setfield(L, -2, "_license");
	return 1;
}
