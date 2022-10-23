#ifndef EXTENSION_HPP_
#define EXTENSION_HPP_


#include <stddef.h>
#include <string>



extern "C" {

#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lapi.h"	

	typedef struct luaEXT_constpair {
		const char* name;
		lua_Integer flag;
	} luaEXT_constpair;

	typedef struct luaEXT_stringpair {
		const char* name;
		const char* flag;
	} luaEXT_stringpair;

	typedef struct luaEXT_libs {
		const char* libname;
		const struct luaL_Reg* libfunc;
	} luaEXT_libs;

	typedef struct luaEXT_udata {
		void* pointer;
	} luaEXT_udata;

}

extern "C" LUALIB_API void luaEXT_reopenSTD(lua_State * L);

/**
* push a wstring on lua-stack
*/
extern "C" LUALIB_API bool luaEXT_pushwstring(lua_State* L, const wchar_t* str);

/**
* load all libraries in libs\
*/
extern "C" LUALIB_API void luaEXT_loadlibraries(lua_State* L);

/**
* debug dump stack content
*/
extern "C" LUALIB_API void luaEXT_stackDump(lua_State* L);

/**
* default msghandler - output on MessageBox
*/
extern "C" LUALIB_API int luaEXT_msghandler(lua_State* L);

/**
* return or-ed flags from table
*/
extern "C" LUALIB_API std::uint64_t luaEXT_checkflags(lua_State* L, int index, const luaEXT_constpair* table);

/**
* push flags as string from table
*/
extern "C" LUALIB_API void luaEXT_pushflags(lua_State* L, lua_Integer value, const luaEXT_constpair* table, bool exact);

/**
* convert strings to flag
*/
extern "C" LUALIB_API uint64_t luaEXT_checkflag(lua_State* L, int index, const luaEXT_constpair* table);

/**
* convert string to string-flag
*/
extern "C" LUALIB_API const char* luaEXT_checksflag(lua_State* L, int index, const luaEXT_stringpair* table);

/**
* convert strings/integer to flags
*/
extern "C" LUALIB_API uint64_t luaEXT_checkflagorinteger(lua_State* L, int index, const luaEXT_constpair* table);

/**
* convert flag to string (if possible) and push it
*/
extern "C" LUALIB_API bool luaEXT_pushflagorinteger(lua_State * L, uint64_t value, const luaEXT_constpair * table);

/**
* convert flag to string and push it
*/
extern "C" LUALIB_API bool luaEXT_pushflag(lua_State* L, uint64_t value, const luaEXT_constpair* table);

/**
* register a lib with subtables
*/
extern "C" LUALIB_API void luaEXT_newlibtable(lua_State* L, const luaEXT_libs* libs, const char* libname = NULL);

/**
* return a wstring from index
*/
LUALIB_API std::wstring luaEXT_towstring(lua_State* L, int index);

/**
* check if a wstring is on index
*/
LUALIB_API std::wstring luaEXT_checkwstring(lua_State* L, int index);

/**
* return a string from a wchar_t string
*/
LUALIB_API std::string luaEXT_convertutf8(lua_State* L, const wchar_t* str);


inline void* luaEXT_checkudata(lua_State* L, int index, const char* tname) {
	void* ret = *((void**)luaL_checkudata(L, index, tname));
	if (ret == NULL) {
		luaL_error(L, "bad argument #%d ('%s' is nil/NULL)", index, tname);
		return 0;
	}
	return ret;
}

inline lua_Integer luaEXT_checkuinteger(lua_State* L, int index, const char* tname) {
	lua_Integer ret = *((lua_Integer*)luaL_checkudata(L, index, tname));
	return ret;
}

inline lua_Integer luaEXT_checkuintegerornil(lua_State* L, int index, const char* tname) {
	if (lua_isnil(L, index)) {
		return 0;
	}
	lua_Integer ret = *((lua_Integer*)luaL_checkudata(L, index, tname));
	return ret;
}


inline void* luaEXT_checkudataornil(lua_State* L, int index, const char* tname) {
	if (lua_isnil(L, index)) {
		return NULL;
	}
	void* ret = *((void**)luaL_checkudata(L, index, tname));
	return ret;
}

inline void luaEXT_setudata(lua_State* L, int index, void* value) {
	*((void**)lua_touserdata(L, index)) = value;
}

inline void luaEXT_pushudata(lua_State* L, void* udata, const char* tname) {
	if (udata == NULL) {
		lua_pushnil(L);
		return;
	}
	if (tname == NULL) {
		lua_pushlightuserdata(L, udata);
	}
	else {
		void** ret = (void**)lua_newuserdatauv(L, sizeof(void*), 0);
		*ret = udata;
		luaL_getmetatable(L, tname);
		lua_setmetatable(L, -2);
	}
}

inline void luaEXT_pushuinteger(lua_State* L, lua_Integer value, const char* tname) {
	lua_Integer* ret = (lua_Integer*)lua_newuserdatauv(L, sizeof(lua_Integer), 0);
	*ret = value;
	luaL_getmetatable(L, tname);
	lua_setmetatable(L, -2);
}

#define COMPILE_TIME_ASSERT(name, x)               \
       typedef int SDL_compile_time_assert_ ## name[(x) * 2 - 1]

COMPILE_TIME_ASSERT(extudataintegervoid, sizeof(lua_Integer) == sizeof(void*));


inline void luaEXT_rawsetinteger(lua_State* L, int index, const char* key, lua_Integer value) {
	lua_pushstring(L, key);
	lua_pushinteger(L, value);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetboolean(lua_State* L, int index, const char* key, bool value) {
	lua_pushstring(L, key);
	lua_pushboolean(L, value);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetnumber(lua_State* L, int index, const char* key, lua_Number value) {
	lua_pushstring(L, key);
	lua_pushnumber(L, value);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetudata(lua_State* L, int index, const char* key, void* value, const char* tname) {
	lua_pushstring(L, key);
	luaEXT_pushudata(L, value, tname);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetuinteger(lua_State* L, int index, const char* key, lua_Integer value, const char* tname) {
	lua_pushstring(L, key);
	luaEXT_pushuinteger(L, value, tname);
	lua_rawset(L, index > 0 ? index : index - 2);
}


inline void luaEXT_rawsetflag(lua_State* L, int index, const char* key, lua_Integer value, const luaEXT_constpair* table) {
	lua_pushstring(L, key);
	luaEXT_pushflag(L, value, table);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetflagorinteger(lua_State* L, int index, const char* key, lua_Integer value, const luaEXT_constpair* table) {
	lua_pushstring(L, key);
	luaEXT_pushflagorinteger(L, value, table);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetflags(lua_State* L, int index, const char* key, lua_Integer value, const luaEXT_constpair* table, bool exact) {
	lua_pushstring(L, key);
	luaEXT_pushflags(L, value, table, exact);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline void luaEXT_rawsetstring(lua_State* L, int index, const char* key, const char* str) {
	lua_pushstring(L, key);
	lua_pushstring(L, str);
	lua_rawset(L, index > 0 ? index : index - 2);
}

inline lua_Integer luaEXT_getfieldinteger(lua_State* L, int index, const char* key, lua_Integer opt) {
	lua_getfield(L, index, key);
	lua_Integer ret = !lua_isnil(L, -1) ? lua_tointeger(L, -1) : opt;
	lua_pop(L, 1);
	return ret;
}

inline lua_Number luaEXT_getfieldnumber(lua_State* L, int index, const char* key, lua_Number opt) {
	lua_getfield(L, index, key);
	lua_Number ret = !lua_isnil(L, -1) ? lua_tonumber(L, -1) : opt;
	lua_pop(L, 1);
	return ret;
}

inline void* luaEXT_getfieldudata(lua_State* L, int index, const char* key, void* opt) {
	lua_getfield(L, index, key);
	void* ret = !lua_isnil(L, -1) ? lua_touserdata(L, -1) : opt;
	lua_pop(L, 1);
	return ret;
}



#endif