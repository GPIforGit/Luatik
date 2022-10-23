#pragma once

static int l_Init(lua_State* L) {
	initcacheudata(L);
	Uint32 flags = checkInit(L, 1);
	int ret = SDL_Init(flags);
	lua_pushboolean(L, ret == 0);
	return 1;
};

static int l_Quit(lua_State* L) {
	initcacheudata(L);
	SDL_Quit();
	return 0;
};
