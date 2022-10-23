
#define lua_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <signal.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>

#include <io.h>

#include <shlwapi.h>
#include <list>
#include <iostream>

#include "lua/lua.hpp"

#if !defined(LUA_PROGNAME)
#define LUA_PROGNAME		"luatik"
#endif

#if !defined(LUA_INIT_VAR)
#define LUA_INIT_VAR		"LUA_INIT"
#endif

#define LUA_INITVARVERSION	LUA_INIT_VAR LUA_VERSUFFIX

static lua_State* globalL = NULL;
static bool globalOwnConsole = false;


static const char* progname = LUA_PROGNAME;
static const char* autoexec = "autoexec.lua";


inline bool fileexist(const char* file) {
	unsigned long attrib = GetFileAttributesA(file);
	return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}

typedef struct sversionlist {
	std::string package;
	std::string license;
} sversionlist;

static  void print_package_version(lua_State* L) {
	std::list < sversionlist > list;

	lua_getglobal(L, "package");
	lua_getfield(L, -1, "loaded");

	lua_pushnil(L);
	size_t len = 0;

	while (lua_next(L, -2) != 0) {

		if (lua_type(L, -1) != LUA_TTABLE) {
			lua_pushstring(L, "-");
		}
		else {
			lua_getfield(L, -1, "_license");
		}

		const char* package = lua_tostring(L, -3);
		const char* license = lua_isstring(L, -1) ? lua_tostring(L, -1) : "-";

		size_t plen = strlen(package);
		if (plen > len) {
			len = plen;
		}

		if (strcmp("_G", package) == 0) {
			package = "core";
		}

		list.push_back({ package, license });

		lua_pop(L, 2);
	}

	list.sort([](const sversionlist& a, const sversionlist& b) { return a.package < b.package; });

	lua_getglobal(L, "print");
	lua_pushvalue(L, -1);
	lua_pushstring(L, "Loaded libraries:");
	lua_call(L, 1, 0);

	for (sversionlist x : list) {
		size_t width = len - x.package.length();
		x.package.replace(x.package.length(), width, width, ' ');
		lua_pushvalue(L, -1);
		lua_pushfstring(L, "  %s (%s)", x.package, x.license.c_str());
		lua_call(L, 1, 0);
	}

	lua_pop(L, 3);
};

static void print_version(void) {
	lua_writestring(LUA_COPYRIGHT, strlen(LUA_COPYRIGHT));
	lua_writeline();
}


static int report(lua_State* L, int status) {
	if (status != LUA_OK) {
		const char* msg = lua_tostring(L, -1);
		lua_writestringerror("%s: ", progname);
		lua_writestringerror("%s\n", msg);
		lua_pop(L, 1);  /* remove message */
	}

	return status;
}

static void createargtable(lua_State* L, wchar_t** argv, int argc) {
	int i, narg;
	narg = argc > 2 ? argc - 2 : 0;  /* number of positive indices */
	lua_createtable(L, narg, 2);

	for (i = 0; i < argc; i++) {
		luaEXT_pushwstring(L, argv[i]);
		lua_rawseti(L, -2, ((lua_Integer)i) - 1);
	}

	lua_setglobal(L, "arg");
}

static int msghandler(lua_State* L) {
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
	return 1;  /* return the traceback */
}


static void sig_break(int i);
static void sig_nothing(int i);


static void EnterInteractive(lua_State* L, bool breakable) {
	if (breakable) {
		signal(SIGINT, sig_break);  /* set C-signal handler */
	}

	printf("Type 'cont' for continue\n");

	lua_pushcfunction(L, msghandler);
	lua_getglobal(L, "debug"); // table
	lua_getfield(L, -1, "debug"); // function
	lua_remove(L, -2); // remove table
	lua_pcall(L, 0, 0, -2);
	lua_pop(L, 1); // remove msghandler	

	if (breakable) {
		signal(SIGINT, SIG_DFL); /* reset C-signal handler */
	}
}

static void do_break(lua_State* L, lua_Debug* ar) {
	(void)ar;  /* unused arg. */
	lua_getinfo(L, "S", ar);
	printf("break in \"%s\" line %d\n", ar->short_src, ar->currentline);

	lua_sethook(L, NULL, 0, 0);

	signal(SIGINT, sig_nothing);

	EnterInteractive(L, false);

	signal(SIGINT, sig_break);
}

static void sig_break(int i) {
	int flag = LUA_MASKLINE;
	lua_sethook(globalL, do_break, flag, 1);
}
static void sig_nothing(int i) {
}




static int docall(lua_State* L, int narg, int nres) {
	signal(SIGINT, sig_break);  /* set C-signal handler */

	int status;
	int base = lua_gettop(L) - narg;  /* function index */
	lua_pushcfunction(L, msghandler);  /* push message handler */
	lua_insert(L, base);  /* put it under function and args */
	globalL = L;  /* to be available to 'laction' */
	status = lua_pcall(L, narg, nres, base);
	lua_remove(L, base);  /* remove message handler from the stack */

	signal(SIGINT, SIG_DFL); /* reset C-signal handler */
	return status;
}




static int l_ShowConsole(lua_State* L) {
	bool vis = lua_toboolean(L, 1);

	if (globalOwnConsole) {
		HWND win = GetConsoleWindow();
		ShowWindow(win, vis ? SW_SHOWNA : SW_HIDE);
	}

	return 0;
}

const struct luaL_Reg array_funcs[] = {
	{"ConsoleShow", l_ShowConsole},
	{NULL,NULL}
};


void SignalHandler(int signal)
{

	luaL_traceback(globalL, globalL, "MEMORY CRASH!", 1);  /* append a standard traceback */
	const char* completemsg = lua_tostring(globalL, -1);
	printf("Exception Caught: %s\n", completemsg);
	lua_pop(globalL, 1);
	EnterInteractive(globalL, true);
	//throw "!Access Violation!";
}

static int pmain(lua_State* L) {
	signal(SIGINT, SIG_DFL); /* reset C-signal handler */

	int argc = (int)lua_tointeger(L, 1);
	wchar_t** argv = (wchar_t**)lua_touserdata(L, 2);
	luaL_checkversion(L);  /* check that interpreter has correct version */


	// open standard libraries
	luaL_openlibs(L);

	// autoload libraries
	luaEXT_loadlibraries(L);

	// add commands
	lua_pushglobaltable(L);
	luaL_setfuncs(L, array_funcs, 0);
	lua_pop(L, 1);

	// create table 'arg'
	createargtable(L, argv, argc);

	// GC in generational mode 
	lua_gc(L, LUA_GCGEN, 0, 0);

	std::string file("");

	if (argc >= 2 && argv[1] != NULL) {
		file = luaEXT_convertutf8(L, argv[1]);

		// add extension if missing
		if (!fileexist(file.c_str()) && fileexist((file + ".lua").c_str())) {
			file += ".lua";
		}
	}
	else if (fileexist(autoexec)) {
		file = autoexec;
	}


	if (file != "") {
		// user add a script name
		progname = file.c_str();

		// load
		int status = luaL_loadfile(L, file.c_str());

		// run code if loaded successfully
		if (status == LUA_OK) {
			status = docall(L, 0, 0);
		}

		// report errors
		report(L, status);
		progname = LUA_PROGNAME;


	}
	else if (_isatty(_fileno(stdin))) {
		// running in interactive mode
		print_version();
		print_package_version(L);
		EnterInteractive(L, true);

	}
	else {
		// execute std_in as file
		int status = luaL_loadfile(L, NULL);
		if (status == LUA_OK) {
			status = docall(L, 0, 0);
		}
		report(L, status);
	}

	// execute a "main"-function in lua
	progname = "main()";

	if (lua_getglobal(L, "main") == LUA_TFUNCTION) {
		int status = docall(L, 0, 0);
		report(L, status);
		if (status != LUA_OK) {
			EnterInteractive(L, true);
		}
	}


	lua_pushboolean(L, 1);  /* signal no errors */
	return 1;
}



int main(int argc, char** argv) {
	int status, result;

	setlocale(LC_COLLATE, ".utf8");
	setlocale(LC_CTYPE, ".utf8");
	

	lua_State* L = luaL_newstate();  // create state

	if (L == NULL) {
		lua_writestringerror("%s: ", progname);
		lua_writestringerror("%s\n", "cannot create state: not enough memory");
		return EXIT_FAILURE;
	}

	globalL = L;

	auto previousHandler  = signal(SIGSEGV, SignalHandler);

	luaEXT_reopenSTD(L); // reattach std in/output

	int numargs;
	wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &numargs);

	lua_pushcfunction(L, &pmain);  /* to call 'pmain' in protected mode */
	lua_pushinteger(L, numargs);  /* 1st argument */
	lua_pushlightuserdata(L, wargv); /* 2nd argument */
	status = lua_pcall(L, 2, 1, 0);  /* do the call */

	result = lua_toboolean(L, -1);  /* get result */
	report(L, status);

	signal(SIGSEGV, previousHandler);

	lua_close(L);

	return (result && status == LUA_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
		AllocConsole();
		SetConsoleTitleA("Luatik debug");

		globalOwnConsole = true;

		HWND win = GetConsoleWindow();

		HMENU hMenu = ::GetSystemMenu(win, FALSE);
		if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

		ShowWindow(win, SW_HIDE);

		// std::cout, std::clog, std::cerr, std::cin
	}
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

	
	int ret = main(NULL, NULL);

	FreeConsole();
	return ret;


}