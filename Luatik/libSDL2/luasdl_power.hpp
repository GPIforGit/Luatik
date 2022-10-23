#pragma once

static int l_Power_GetInfo(lua_State* L) {
	int sec;
	int pct;
	pushPowerState(L, SDL_GetPowerInfo(&sec, &pct));
	lua_pushinteger(L, sec);
	lua_pushinteger(L, pct);
	return 3;
}

