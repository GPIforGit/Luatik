#pragma once

static int l_gui_init(lua_State* L) {
	// init Cache
	lua_pushboolean(L, true);
	return 1;
}

static int l_gui_quit(lua_State* L) {
	return 0;
}
