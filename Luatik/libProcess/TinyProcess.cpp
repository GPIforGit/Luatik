// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include <Windows.h>

#include "../lua/lua.hpp"
/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static


#include "process.hpp"



#define ID_Process "TinyProcess"//

inline TinyProcessLib::Process* checkProcess(lua_State* L, int index) {
	return (TinyProcessLib::Process*)luaEXT_checkudata(L, index, ID_Process);
}
inline TinyProcessLib::Process* checkProcessOrNil(lua_State* L, int index) {
	return (TinyProcessLib::Process*)luaEXT_checkudataornil(L, index, ID_Process);
}
inline void pushProcess(lua_State* L, TinyProcessLib::Process* p) {
	luaEXT_pushudata(L, (void*)p, ID_Process);
}
//TinyProcessLib::Process* process = NULL;



static int l_open(lua_State* L) {
	TinyProcessLib::Process* process;
	std::wstring cmd = luaEXT_checkwstring(L, 1);
	std::wstring path = luaEXT_checkwstring(L, 2);


	bool background = luaL_opt(L,lua_toboolean, 3, false);

	TinyProcessLib::Config c;
	if (background) {
		c.show_window = TinyProcessLib::Config::ShowWindow::show_min_no_active;
	}

	process =  new TinyProcessLib::Process(cmd, path, nullptr, true, c);

	pushProcess(L, process);

	return 1;
}

static int l_write(lua_State* L) {
	TinyProcessLib::Process* process = checkProcess(L, 1);
	size_t size;
	const char* str = luaL_checklstring(L, 2, &size);
	process->write(str, size);
	lua_pushboolean(L, true);
	return 1;
}

static int l_isrunning(lua_State* L) {
	TinyProcessLib::Process* process = checkProcess(L, 1);
	int exitstatus=0;
	lua_pushboolean(L, process->try_get_exit_status(exitstatus) == false);
	lua_pushinteger(L, exitstatus);
	return 2;
}

static int l_kill(lua_State* L) {
	TinyProcessLib::Process* process = checkProcess(L, 1);
	process->kill(true);
	return 0;
}

static int l_close(lua_State* L) {
	TinyProcessLib::Process* process = checkProcessOrNil(L, 1);
	if (process != NULL) {
		delete process;
		process = NULL;
	}
	return 0;
}

static int l_read(lua_State* L) {
	TinyProcessLib::Process* process = checkProcess(L, 1);
	lua_pushstring(L, process->read_stdout().c_str());
	return 1;
}

static int l_readerr(lua_State* L) {
	TinyProcessLib::Process* process = checkProcess(L, 1);
	lua_pushstring(L, process->read_stderr().c_str());
	return 1;
}


static int l_wait(lua_State* L) {
	TinyProcessLib::Process* process = checkProcess(L, 1);
	lua_pushinteger(L, process->get_exit_status());
	return 1;	
}

#define PicoRemote_VERSION "0.1"
const struct luaL_Reg array_funcs[] = {
	{"Open", l_open},
};

const struct luaL_Reg array_metafuncs[] = {
	{"Write", l_write},
	{"IsRunning", l_isrunning},
	{"Kill", l_kill},
	{"Close", l_close},
	{"Read",l_read},
	{"ReadError",l_readerr},
	{"Wait",l_wait},
	//{"__gc",l_close},
	{NULL,NULL}
};


LUAMOD_API int luaopen_TinyProcess(lua_State * L) {
	luaL_newmetatable(L, ID_Process);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, array_metafuncs, 0);


	lua_newtable(L);
	luaL_setfuncs(L, array_funcs, 0);	
	lua_pushfstring(L, "%s by GPI, Tiny Process library by Ole Christian Eidheim", PicoRemote_VERSION);
	lua_setfield(L, -2, "_license");
	return 1;
}
