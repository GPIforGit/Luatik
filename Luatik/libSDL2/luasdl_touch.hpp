#pragma once

static int l_touch_GetNum(lua_State* L) {
	lua_pushinteger(L, SDL_GetNumTouchDevices());
	return 1;
}

static int l_touch_Open(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	pushTouchID(L, SDL_GetTouchDevice(index));
	return 1;
}

static int l_touch_Close(lua_State* L) {
	SDL_TouchID id = checkTouchID(L, 1);
	removeTouchID(L, id);
	luaEXT_setudata(L, 1, NULL);
	return 1;
}

static int l_touch_GetType(lua_State* L) {
	SDL_TouchID id = checkTouchID(L, 1);
	pushTouchDeviceType(L, SDL_GetTouchDeviceType(id));
	return 1;
}

static int l_touch_GetNumFingers(lua_State* L) {
	SDL_TouchID id = checkTouchID(L, 1);
	lua_pushinteger(L, SDL_GetNumTouchFingers(id));
	return 1;
}

static int l_touch_GetFinger(lua_State* L) {
	SDL_TouchID id = checkTouchID(L, 1);
	int index = (int)luaL_checkinteger(L, 2);
	SDL_Finger* f = SDL_GetTouchFinger(id, index);
	if (f != NULL) {
		lua_pushnumber(L, f->x);
		lua_pushnumber(L, f->y);
		lua_pushnumber(L, f->pressure);
		lua_pushinteger(L, f->id);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 3;
}

