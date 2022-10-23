
#pragma warning(disable : 26812)

#include "sdl_gui.h"

#include "types.hpp"
#include "flags.hpp"

#include "lib_gui.hpp"
#include "lib_requester.hpp"


// funcs





// array

#include "func.hpp"

// LIB

static const struct luaEXT_libs array_lib[] = {
	{"Gui", array_Gui_func},
	{"Request", array_Requester_func},
	{NULL,NULL}
};



LUAMOD_API int luaopen_SDLgui(lua_State * L) {
	luaEXT_newlibtable(L, array_lib, "SDL"); // append SDL, if exist

	// dummy license-string
	lua_newtable(L);
	lua_pushfstring(L, "%s by GPI", SDLGUI_VERSION);
	lua_setfield(L, -2, "_license");


	return 1;
}