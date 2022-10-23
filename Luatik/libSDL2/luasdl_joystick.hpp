#pragma once

static int l_joystick_GetNum(lua_State* L) {
	int ret = SDL_NumJoysticks();
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_joystick_GetName(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		lua_pushstring(L, SDL_JoystickNameForIndex(index));
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		lua_pushstring(L, SDL_JoystickName(joy));
	}
	return 1;
}

static int l_joystick_GetPlayerIndex(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		lua_pushinteger(L, SDL_JoystickGetDevicePlayerIndex(index));
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		lua_pushinteger(L, SDL_JoystickGetPlayerIndex(joy));
	}
	return 1;
}

static int l_joystick_GetGUID(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(index);
		pushJoystickGUID(L, &guid);
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		SDL_JoystickGUID guid = SDL_JoystickGetGUID(joy);
		pushJoystickGUID(L, &guid);
	}
	return 1;
}

static int l_joystick_GetVendor(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		lua_pushinteger(L, SDL_JoystickGetDeviceVendor(index));
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		lua_pushinteger(L, SDL_JoystickGetVendor(joy));
	}
	return 1;
}

static int l_joystick_GetProduct(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		lua_pushinteger(L, SDL_JoystickGetDeviceProduct(index));
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		lua_pushinteger(L, SDL_JoystickGetProduct(joy));
	}
	return 1;
}

static int l_joystick_GetProductVersion(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		lua_pushinteger(L, SDL_JoystickGetDeviceProductVersion(index));
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		lua_pushinteger(L, SDL_JoystickGetProductVersion(joy));
	}
	return 1;
}

static int l_joystick_GetType(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		pushJoystickType(L, SDL_JoystickGetDeviceType(index));
	}
	else {
		SDL_Joystick* joy = checkJoystick(L, 1);
		pushJoystickType(L, SDL_JoystickGetType(joy));
	}
	return 1;
}

static int l_joystick_Open(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	pushJoystick(L, SDL_JoystickOpen(index));
	return 1;
}

static int l_joystick_FromPlayerIndex(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	pushJoystick(L, SDL_JoystickFromPlayerIndex(index));
	return 1;
}

static int l_joystick_AttachVirtual(lua_State* L) {
	SDL_JoystickType type = checkJoystickType(L, 1);
	int axes = (int)luaL_checkinteger(L, 2);
	int buttons = (int)luaL_checkinteger(L, 3);
	int hats = (int)luaL_checkinteger(L, 4);
	int ret = SDL_JoystickAttachVirtual(type, axes, buttons, hats);
	if (ret < 0) {
		lua_pushnil(L);
	}
	else {
		lua_pushinteger(L, ret);
	}
	return 1;
}

static int l_joystick_DetachVirtual(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	lua_pushboolean(L, SDL_JoystickDetachVirtual(index) == 0);
	return 1;
}

static int l_joystick_IsVirtual(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	lua_pushboolean(L, SDL_JoystickIsVirtual(index));
	return 1;
}

static int l_joystick_SetVirtualAxis(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int axis = (int)luaL_checkinteger(L, 2);
	Sint16 value = (Sint16)checkroundnumber(L, 3);
	lua_pushboolean(L, SDL_JoystickSetVirtualAxis(joy, axis, value) == 0);
	return 1;
}

static int l_joystick_SetVirtualButton(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int button = (int)luaL_checkinteger(L, 2);
	Uint8 value = (Uint8)checkroundnumber(L, 3);
	lua_pushboolean(L, SDL_JoystickSetVirtualButton(joy, button, value) == 0);
	return 1;
}

static int l_joystick_SetVirtualHat(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int hat = (int)luaL_checkinteger(L, 2);
	Uint8 value = checkJoystickHat(L, 3);
	lua_pushboolean(L, SDL_JoystickSetVirtualHat(joy, hat, value) == 0);
	return 1;
}

static int l_joystick_SetPlayerIndex(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int index = (int)luaL_checkinteger(L, 2);
	SDL_JoystickSetPlayerIndex(joy, index);
	return 0;
}

static int l_joystick_GetSerial(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	lua_pushstring(L, SDL_JoystickGetSerial(joy));
	return 1;
}

static int l_joystick_GetAttached(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	lua_pushboolean(L, SDL_JoystickGetAttached(joy));
	return 1;
}

static int l_joystick_GetNumAxes(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int ret = SDL_JoystickNumAxes(joy);
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_joystick_GetNumBalls(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int ret = SDL_JoystickNumBalls(joy);
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_joystick_GetNumHats(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int ret = SDL_JoystickNumHats(joy);
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_joystick_GetNumButtons(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int ret = SDL_JoystickNumButtons(joy);
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_joystick_Update(lua_State* L) {
	SDL_JoystickUpdate();
	return 0;
}

static int l_Joystick_EventState(lua_State* L) {
	int state = checkEventState(L, 1);
	int ret = SDL_JoystickEventState(state);
	if (ret >= 0) {
		lua_pushnil(L);
	}
	else {
		pushEventState(L, ret);
	}
	return 1;
}

static int l_joystick_GetAxis(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int axis = (int)luaL_checkinteger(L, 2);
	Sint16 value = SDL_JoystickGetAxis(joy, axis);
	double norm = value / (value >= 0 ? 32767.0 : 32768.0);
	lua_pushnumber(L, norm);
	return 1;
}

static int l_joystick_GetAxisInitialState(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int axis = (int)luaL_checkinteger(L, 2);
	Sint16 value;
	if (SDL_JoystickGetAxisInitialState(joy, axis, &value)) {
		double norm = value / (value >= 0 ? 32767.0 : 32768.0);
		lua_pushnumber(L, norm);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_joystick_GetHat(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int hat = (int)luaL_checkinteger(L, 2);
	pushJoystickHat(L, SDL_JoystickGetHat(joy, hat));
	return 1;
}

static int l_joystick_GetBall(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int ball = (int)luaL_checkinteger(L, 2);
	int dx, dy;
	if (SDL_JoystickGetBall(joy, ball, &dx, &dy) == 0) {
		lua_pushinteger(L, dx);
		lua_pushinteger(L, dy);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 2;
}

static int l_joystick_GetButton(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	int button = (int)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_JoystickGetButton(joy, button));
	return 1;
}

static int l_joystick_Rumble(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	double low = luaL_checknumber(L, 2);
	double high = luaL_checknumber(L, 3);
	Uint32 ms = (Uint32)checkroundnumber(L, 4);
	low = low < 0.0 ? 0.0 : (low > 1.0 ? 1.0 : low);
	high = high < 0.0 ? 0.0 : (high > 1.0 ? 1.0 : high);
	Uint16 lowfrq = (Uint16)(0xFFFF * low);
	Uint16 highfrq = (Uint16)(0xFFFF * high);
	lua_pushboolean(L, SDL_JoystickRumble(joy, lowfrq, highfrq, ms) == 0);
	return 1;
}

static int l_joystick_RumbleTriggers(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	double left = luaL_checknumber(L, 2);
	double right = luaL_checknumber(L, 3);
	Uint32 ms = (Uint32)checkroundnumber(L, 4);
	left = left < 0.0 ? 0.0 : (left > 1.0 ? 1.0 : left);
	right = right < 0.0 ? 0.0 : (right > 1.0 ? 1.0 : right);
	Uint16 leftfrq = (Uint16)(0xFFFF * left);
	Uint16 rightfrq = (Uint16)(0xFFFF * right);
	lua_pushboolean(L, SDL_JoystickRumbleTriggers(joy, leftfrq, rightfrq, ms) == 0);
	return 1;
}

static int l_joystick_HasLED(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	lua_pushboolean(L, SDL_JoystickHasLED(joy));
	return 1;
}

static int l_joystick_HasRumble(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	lua_pushboolean(L, SDL_JoystickHasRumble(joy));
	return 1;
}

static int l_joystick_HasRumbleTriggers(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	lua_pushboolean(L, SDL_JoystickHasRumbleTriggers(joy));
	return 1;
}

static int l_joystick_SetLED(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	Uint8 r = (Uint8)checkroundnumber(L, 2);
	Uint8 g = (Uint8)checkroundnumber(L, 3);
	Uint8 b = (Uint8)checkroundnumber(L, 4);
	lua_pushboolean(L, SDL_JoystickSetLED(joy, r, g, b) == 0);
	return 1;
}

static int l_joystick_Close(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	SDL_JoystickClose(joy);
	removeJoystick(L, joy);
	luaEXT_setudata(L, 1, NULL);
	return 0;
}

static int l_joystick_GetPowerLevel(lua_State* L) {
	SDL_Joystick* joy = checkJoystick(L, 1);
	pushJoystickPowerLevel(L, SDL_JoystickCurrentPowerLevel(joy));
	return 1;
}
