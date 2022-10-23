#pragma once

static int l_hint_Set(lua_State* L) {
	const char* name = checkHint(L, 1);
	const char* value = luaL_checkstring(L, 2);
	if (lua_isstring(L, 3)) {
		SDL_HintPriority prio = checkHintPriority(L, 1);
		lua_pushboolean(L, SDL_SetHintWithPriority(name, value, prio));
	}
	else {
		lua_pushboolean(L, SDL_SetHint(name, value));
	}
	return 1;
}

static int l_hint_Get(lua_State* L) {
	const char* name = checkHint(L, 1);
	lua_pushstring(L, SDL_GetHint(name));
	return 1;
}

static int l_hint_Clear(lua_State* L) {
	SDL_ClearHints();
	return 0;
}

static int l_hint_Reset(lua_State* L) {
	const char* name = checkHint(L, 1);
	lua_pushboolean(L, SDL_ResetHint(name));
	return 1;
}

