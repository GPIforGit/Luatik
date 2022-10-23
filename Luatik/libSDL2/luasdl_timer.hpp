#pragma once

static int l_Time_GetTicks(lua_State* L) {
	lua_pushinteger(L, (lua_Integer)SDL_GetTicks64());
	return 1;
}

static int l_Time_GetPerformanceCounter(lua_State*L) {
	lua_pushinteger(L, (lua_Integer)SDL_GetPerformanceCounter());
	return 1;
}

static int l_Time_GetPerformanceFrequency(lua_State* L) {
	lua_pushinteger(L, (lua_Integer)SDL_GetPerformanceFrequency());
	return 1;
}

static int l_Time_Get(lua_State* L) {
	lua_pushnumber(L, (lua_Number)SDL_GetPerformanceCounter() / (lua_Number)SDL_GetPerformanceFrequency());
	return 1;
}

static int l_Time_Delay(lua_State* L) {
	Uint32 sec = (Uint32)checkroundnumber(L, 1);
	SDL_Delay(sec);
	return 0;
}

