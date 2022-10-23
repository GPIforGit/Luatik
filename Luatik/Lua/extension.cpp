

#include <string.h>
#include <Windows.h>
#include <string>

extern "C" {

#define LUA_LIB
#include "lprefix.h"

#include "lua.h"
#include "lapi.h"
#include "lauxlib.h"
}

#include "extension.hpp"


/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static


//#define EXT_CPATH "cpath"
//#define EXT_LIB L"libs\\WIN64\\"
//#define EXT_LIBSCPATH EXT_LIB L"?.dll"
//#define EXT_LIBSDLL EXT_LIB L"*.dll"

#define EXT_PATH "path"
#define EXT_MODULE L"libs\\"
#define EXT_MODULEPATH EXT_MODULE L"?.lua"
#define EXT_MODULELUA EXT_MODULE L"*.lua"


LUALIB_API std::string luaEXT_convertutf8(lua_State* L, const wchar_t* str);

extern "C" LUALIB_API void luaEXT_reopenSTD(lua_State * L) {

		// std::cout, std::clog, std::cerr, std::cin
		FILE* fDummy;
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		fflush(stdout);
		clearerr(stdout);
		fflush(stderr);
		clearerr(stderr);
		fflush(stdin);
		clearerr(stdin);
}


extern "C" LUALIB_API void luaEXT_stackDump(lua_State * L) { //Forward printing stack information 1, 2, 3, 4, 5, 6,...
	int i;
	printf("DUMP\n");

	int top = lua_gettop(L);

	for (i = 1; i <= top; i++) {
		int t = lua_type(L, i);

		switch (t) {
		case LUA_TSTRING:
			printf("  key:%d,value:'%s'\r\n", i, lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:
			printf("  key:%d,value:%s\r\n", i, lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:
			printf("  key:%d,value:%g\r\n", i, lua_tonumber(L, i));
			break;

		default:
			printf("  key:%d,value:%s\r\n", i, lua_typename(L, t));
			break;
		}
	}

	printf("\n");
}

extern "C" LUALIB_API bool luaEXT_pushwstring(lua_State * L, const wchar_t* str) {
	int len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, 0);

	void* ud;
	lua_Alloc allocf = lua_getallocf(L, &ud);
	size_t size = sizeof(char) * len;
	char* buf = (char*)allocf(ud, NULL, 0, size);

	if (buf == NULL) {
		lua_pushnil(L);
		return false;
	}

	WideCharToMultiByte(CP_UTF8, 0, str, -1, buf, len, NULL, 0);

	lua_pushstring(L, buf);

	allocf(ud, buf, size, 0);
	return true;
}

extern "C" LUALIB_API int luaEXT_msghandler(lua_State * L) {
	const char* msg = lua_tostring(L, 1);

	if (msg == NULL) {  /* is error object not a string? */
		if (luaL_callmeta(L, 1, "__tostring") &&  /* does it have a metamethod */
			lua_type(L, -1) == LUA_TSTRING)  /* that produces a string? */
			return 1;  /* that is the message */
		else
			msg = lua_pushfstring(L, "(error object is a %s value)",
				luaL_typename(L, 1));
	}

	luaL_traceback(L, L, msg, 1);  /* append a standard traceback */

	const char* completemsg = lua_tostring(L, -1);
	printf(completemsg);
	MessageBoxA(NULL, completemsg, "Luatik", MB_OK);

	return 1;  /* return the traceback */
}



extern "C" static void load_libs(lua_State * L, const wchar_t* path, const char* packagepath, const wchar_t* libscpath, const wchar_t* libsdll) {




	// copy path and add "\"

	std::wstring str(path);

	str += L"\\";

	// search for dlls
	WIN32_FIND_DATAW ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFileW((str + libsdll).c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind) {
		return;
	}

	// Set path for cpath

	lua_getglobal(L, "package");

	if (!lua_istable(L, -1)) {
		luaL_error(L, "'package' is not a table");
	}

	// get old path and save it
	lua_pushstring(L, packagepath);
	lua_gettable(L, -2);
	// set new path
	lua_pushstring(L, packagepath);
	luaEXT_pushwstring(L, (str + libscpath).c_str());
	lua_settable(L, -4);

	do {
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			// exclude extension .dll
			std::wstring file(ffd.cFileName);

			size_t found = file.find_last_of(L".");
			file = file.substr(0, found);

			/* cFileName = 'require(cFileName)' */
			lua_pushcfunction(L, luaEXT_msghandler);
			lua_getglobal(L, "require");
			luaEXT_pushwstring(L, file.c_str());

			if (lua_pcall(L, 1, 1, -3) == LUA_OK) {
				std::string key = luaEXT_convertutf8(L, file.c_str());

				lua_setglobal(L, key.c_str());
				lua_pop(L, 1);

			}
			else {
				lua_pop(L, 2);
			}

		}
	} while (FindNextFileW(hFind, &ffd) != 0);

	FindClose(hFind);

	//reset package cpath
	lua_pushstring(L, packagepath);
	lua_insert(L, -2); // set key to position -2 - on -1 is now the old value!
	lua_settable(L, -3);
	lua_pop(L, 1); // remove table

}

LUAMOD_API int (luaopen_SDL)(lua_State* L);
LUAMOD_API int (luaopen_SDLimage)(lua_State* L);
LUAMOD_API int (luaopen_SDLgui)(lua_State* L);
LUAMOD_API int (luaopen_TinyProcess)(lua_State* L);
LUAMOD_API int (luaopen_Misc)(lua_State* L);

static const luaL_Reg loadedExlibs[] = {
	{"SDL", luaopen_SDL},
	{"SDLimage", luaopen_SDLimage},
	{"SDLgui", luaopen_SDLgui},
	{"TinyProcess", luaopen_TinyProcess},
	{"Misc", luaopen_Misc},
	{NULL,NULL}
};


extern "C" LUALIB_API void luaEXT_loadlibraries(lua_State * L) {
	//stackDump(L);
	
	{
		/* "require" functions from 'loadedlibs' and set results to global table */
		const luaL_Reg* lib;
		for (lib = loadedExlibs; lib->func; lib++) {
			luaL_requiref(L, lib->name, lib->func, 1);
			lua_pop(L, 1);  /* remove lib */
		}
	}

	// Get current directory
	void* ud;
	lua_Alloc allocf = lua_getallocf(L, &ud);

	size_t len = GetCurrentDirectoryW(0, NULL); // zero termination
	size_t size = (len + 1) * sizeof(wchar_t);

	wchar_t* buf = (wchar_t*)allocf(ud, NULL, 0, size);

	if (buf == NULL) {
		luaL_error(L, "unable to get current directory");
		return;
	}

	GetCurrentDirectoryW((DWORD)len + 1, buf);
	std::wstring current(buf);
	allocf(ud, buf, size, 0);
	buf = NULL;

	// Get module name
	wchar_t buf2[MAX_PATH];
	size_t n = GetModuleFileNameW(NULL, buf2, MAX_PATH);

	if (n == 0 || n == sizeof(buf2)) {
		luaL_error(L, "unable to get ModuleFileName");
		return;
	}

	std::wstring module(buf2);

	// get path part of module name
	size_t found = module.find_last_of(L"\\/");
	module = module.substr(0, found);


	// load libs
	//load_libs(L, module.c_str(), EXT_CPATH, EXT_LIBSCPATH, EXT_LIBSDLL);
	load_libs(L, module.c_str(), EXT_PATH, EXT_MODULEPATH, EXT_MODULELUA);
	
	if (module != current) {
		//load_libs(L, current.c_str(), EXT_CPATH, EXT_LIBSCPATH, EXT_LIBSDLL);
		load_libs(L, current.c_str(), EXT_PATH, EXT_MODULEPATH, EXT_MODULELUA);
	}
}

LUALIB_API std::wstring luaEXT_towstring(lua_State* L, int index) {
	const char* str = lua_tostring(L, index);

	int wlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

	void* ud;
	lua_Alloc allocf = lua_getallocf(L, &ud);
	size_t size = sizeof(wchar_t) * wlen;
	wchar_t* buf = (wchar_t*)allocf(ud, NULL, 0, size);

	MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, wlen);

	std::wstring ret(buf);

	allocf(ud, buf, size, 0);
	return ret;
}

LUALIB_API std::wstring luaEXT_checkwstring(lua_State* L, int index) {
	const char* str = luaL_checkstring(L, index);

	int wlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

	void* ud;
	lua_Alloc allocf = lua_getallocf(L, &ud);
	size_t size = sizeof(wchar_t) * wlen;
	wchar_t* buf = (wchar_t*)allocf(ud, NULL, 0, size);
	if (buf == NULL) {
		return L"";
	}

	MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, wlen);

	std::wstring ret(buf);

	allocf(ud, buf, size, 0);
	return ret;
}

LUALIB_API std::string luaEXT_convertutf8(lua_State* L, const wchar_t* str) {
	int len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, 0);

	void* ud;
	lua_Alloc allocf = lua_getallocf(L, &ud);
	size_t size = sizeof(char) * len;
	char* buf = (char*)allocf(ud, NULL, 0, size);

	if (buf == NULL) {
		return "";
	}

	WideCharToMultiByte(CP_UTF8, 0, str, -1, buf, len, NULL, 0);

	std::string ret(buf);

	allocf(ud, buf, size, 0);
	return ret;
}

extern "C" LUALIB_API std::uint64_t luaEXT_checkflags(lua_State * L, int index, const luaEXT_constpair * table) {
	if (lua_isnil(L, index)) {
		return 0;
	}
	std::string desc(luaL_checkstring(L, index));
	uint64_t flags = 0;

	desc += " "; // add last

	size_t opos = 0;
	size_t pos = 0;
	while ((pos = desc.find_first_of(" ;|,", opos)) != std::string::npos) {

		if (pos - opos > 0) {
			std::string word = desc.substr(opos, pos - opos);

			bool ok = false;
			for (const luaEXT_constpair* tableread = table; tableread->name != NULL; tableread += 1) {
				if (word == tableread->name) {
					flags |= tableread->flag;
					ok = true;
					break;
				}
			}

			if (!ok) {
				luaL_error(L, "bad argument #%d (unknown flag '%s')", index, word.c_str());
				return 0;
			}

		}

		opos = pos + 1;
	}
	return flags;
}

extern "C" LUALIB_API void luaEXT_pushflags(lua_State * L, lua_Integer value, const luaEXT_constpair * table, bool exact) {
	std::string result = "";

	bool ok = false;
	for (const luaEXT_constpair* tableread = table; tableread->name != NULL; tableread++) {
		if (tableread->flag == 0 && value == 0) {
			result = tableread->name;
			break;
		}
		else if (((value & tableread->flag) == tableread->flag && tableread->flag != 0 && exact == true) or ((value & tableread->flag) != 0 && tableread->flag != 0 && exact == false)) {
			if (ok) {
				result += " ";
			}
			result += tableread->name;
			ok = true;
		}
	}
	lua_pushstring(L, result.c_str());
}

extern "C" LUALIB_API uint64_t luaEXT_checkflag(lua_State * L, int index, const luaEXT_constpair * table) {
	std::string word = luaL_checkstring(L, index);

	for (const luaEXT_constpair* tableread = table; tableread->name != NULL; tableread += 1) {
		if (word == tableread->name) {
			return tableread->flag;
		}
	}

	luaL_error(L, "bad argument #%d (unknown flag '%s')", index, word.c_str());
	return 0;
}

extern "C" LUALIB_API const char* luaEXT_checksflag(lua_State * L, int index, const luaEXT_stringpair * table) {
	std::string word = luaL_checkstring(L, index);

	for (const luaEXT_stringpair* tableread = table; tableread->name != NULL; tableread += 1) {
		if (word == tableread->name) {
			return tableread->flag;
		}
	}

	luaL_error(L, "bad argument #%d (unknown flag '%s')", index, word.c_str());
	return 0;
}

extern "C" LUALIB_API uint64_t luaEXT_checkflagorinteger(lua_State * L, int index, const luaEXT_constpair * table) {
	if (lua_isinteger(L, index)) {
		return lua_tointeger(L, index);
	}
	else if (lua_isnumber(L, index)) {
		return (lua_Integer)lua_tonumber(L, index);
	}

	else if (lua_isnil(L, index)) {
		return 0;
	}
	return luaEXT_checkflag(L, index, table);
}

extern "C" LUALIB_API bool luaEXT_pushflag(lua_State * L, uint64_t value, const luaEXT_constpair * table) {
	for (const luaEXT_constpair* tableread = table; tableread->name != NULL; tableread += 1) {
		if (value == tableread->flag) {
			lua_pushstring(L, tableread->name);
			return true;
		}
	}
	lua_pushnil(L);
	return false;
}

extern "C" LUALIB_API bool luaEXT_pushflagorinteger(lua_State * L, uint64_t value, const luaEXT_constpair * table) {
	for (const luaEXT_constpair* tableread = table; tableread->name != NULL; tableread += 1) {
		if (value == tableread->flag) {
			lua_pushstring(L, tableread->name);
			return true;
		}
	}
	lua_pushinteger(L, value);
	return false;
}

extern "C" LUALIB_API void luaEXT_newlibtable(lua_State * L, const luaEXT_libs * libs, const char* libname) {
	bool donew = true;
	if (libname != NULL) {
		if (lua_getglobal(L, libname) == LUA_TNIL) {
			// doesn't exit - remove
			lua_pop(L, 1);
		}
		else {
			donew = false;
		}
	}

	if (donew) {
		size_t count = 0;
		for (const luaEXT_libs* clib = libs; clib->libname != NULL; clib++) {
			if (*(clib->libname) == 0) {
				for (const luaL_Reg* cfunc = clib->libfunc; cfunc->name != NULL; cfunc++) {
					count++;
				}
			}
			else {
				count++;
			}
		}

		lua_createtable(L, 0, (int)count);
		if (libname != NULL) {
			// create copy and set global
			lua_pushvalue(L, -1);
			lua_setglobal(L, libname);
		}
	}


	for (const luaEXT_libs* clib = libs; clib->libname != NULL; clib++) {
		if (*(clib->libname) == 0) {
			luaL_setfuncs(L, clib->libfunc, 0);
		}
		else {
			if (lua_getfield(L, -1, clib->libname) == LUA_TTABLE) {
				luaL_setfuncs(L, clib->libfunc, 0);
				lua_pop(L, 1);
			}
			else {
				//create new table
				lua_pop(L, 1); // remove nil
				size_t count = 0;
				for (const luaL_Reg* cfunc = clib->libfunc; cfunc->name != NULL; cfunc++) {
					count++;
				}
				lua_createtable(L, 0, (int)count);
				luaL_setfuncs(L, clib->libfunc, 0);
				lua_setfield(L, -2, clib->libname);
			}
		}
	}

}

