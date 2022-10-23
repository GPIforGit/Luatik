#pragma once

static int l_gesture_Record(lua_State* L) {
	SDL_TouchID id = checkTouchID(L, 1);
	lua_pushboolean(L, SDL_RecordGesture(id));
	return 1;
}

static int l_gesture_SaveAllTemplates(lua_State* L) {
	SDL_RWops* rw;
	bool doclose;
	if (lua_isstring(L, 1)) {
		const char* file = luaL_checkstring(L, 1);
		rw = SDL_RWFromFile(file, "wb+");
		doclose = true;
	}
	else {
		rw = checkRWops(L, 1);
		doclose = false;
	}
	lua_pushinteger(L, SDL_SaveAllDollarTemplates(rw));
	if (doclose) {
		SDL_RWclose(rw);
	}
	return 1;
}

static int l_gesture_SaveTemplate(lua_State* L) {
	int id = (int)luaL_checkinteger(L, 1);

	SDL_RWops* rw;
	bool doclose;
	if (lua_isstring(L, 2)) {
		const char* file = luaL_checkstring(L, 2);
		rw = SDL_RWFromFile(file, "wb+");
		doclose = true;
	}
	else {
		rw = checkRWops(L, 2);
		doclose = false;
	}
	lua_pushinteger(L, SDL_SaveDollarTemplate(id,rw));
	if (doclose) {
		SDL_RWclose(rw);
	}
	return 1;
}

static int l_gesture_LoadTemplates(lua_State* L) {
	SDL_TouchID id = checkTouchID(L, 1);

	SDL_RWops* rw;
	bool doclose;
	if (lua_isstring(L, 2)) {
		const char* file = luaL_checkstring(L, 2);
		rw = SDL_RWFromFile(file, "wb+");
		doclose = true;
	}
	else {
		rw = checkRWops(L, 2);
		doclose = false;
	}
	lua_pushinteger(L, SDL_LoadDollarTemplates(id, rw));
	if (doclose) {
		SDL_RWclose(rw);
	}
	return 1;
}

