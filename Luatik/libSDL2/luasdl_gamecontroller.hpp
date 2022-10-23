#pragma once

static int l_GameController_AddMappingFromFile(lua_State* L) {
	int ret;
	if (lua_isstring(L, 1)) {
		const char* file = luaL_checkstring(L, 1);
		ret = SDL_GameControllerAddMappingsFromFile(file);
	}
	else {
		SDL_RWops* rw = checkRWops(L, 1);
		ret = SDL_GameControllerAddMappingsFromRW(rw,0);
	}


	if (ret < 0) {
		lua_pushnil(L);
	}
	else {
		lua_pushinteger(L, ret);
	}
	return 1;
}

static int l_GameController_AddMapping(lua_State* L) {
	const char* map = luaL_checkstring(L, 1);
	lua_pushboolean(L, SDL_GameControllerAddMapping(map) >= 0);
	return 1;
}

static int l_GameController_GetNumMappings(lua_State* L) {
	lua_pushinteger(L, SDL_GameControllerNumMappings());
	return 1;
}

static int l_GameController_GetMappingFromIndex(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	const char* ret = SDL_GameControllerMappingForIndex(index);
	lua_pushstring(L, ret);
	SDL_free((void*)ret);
	return 1;
}

static int l_GameController_GetMapping(lua_State* L) {
	const char* ret;
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		ret = SDL_GameControllerMappingForDeviceIndex(index);
	}
	else if (lua_isstring(L, 1)) {
		SDL_JoystickGUID guid = checkJoystickGUID(L, 1);
		ret = SDL_GameControllerMappingForGUID(guid);
	}
	else {
		SDL_GameController* con = checkGameController(L, 1);
		ret = SDL_GameControllerMapping(con);
	}
	lua_pushstring(L, ret);
	SDL_free((void*)ret);
	return 1;
}

static int l_GameController_Is(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	lua_pushboolean(L, SDL_IsGameController(index));
	return 1;
}

static int l_GameController_Open(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	pushGameController(L, SDL_GameControllerOpen(index));
	return 1;
}

static int l_GameControllerFromPlayerIndex(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	pushGameController(L, SDL_GameControllerFromPlayerIndex(index));
	return 1;
}

static int l_GameController_GetName(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushstring(L, SDL_GameControllerName(con));
	return 1;
}

static int l_GameController_GetType(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		pushGameControllerType(L, SDL_GameControllerTypeForIndex(index));
	}
	else {
		SDL_GameController* con = checkGameController(L, 1);
		pushGameControllerType(L, SDL_GameControllerGetType(con));
	}
	return 1;
}

static int l_GameController_GetPlayerIndex(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushinteger(L, SDL_GameControllerGetPlayerIndex(con));
	return 1;
}

static int l_GameController_SetPlayerIndex(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	int index = (int)luaL_checkinteger(L, 2);
	SDL_GameControllerSetPlayerIndex(con, index);
	return 0;
}

static int l_GameController_GetVendor(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushinteger(L, SDL_GameControllerGetVendor(con));
	return 1;
}

static int l_GameController_GetProduct(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushinteger(L, SDL_GameControllerGetProduct(con));
	return 1;
}

static int l_GameController_GetProductVersion(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushinteger(L, SDL_GameControllerGetProductVersion(con));
	return 1;
}

static int l_GameController_GetSerial(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushstring(L, SDL_GameControllerGetSerial(con));
	return 1;
}

static int l_GameController_GetAttached(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushboolean(L, SDL_GameControllerGetAttached(con));
	return 1;
}

static int l_GameController_GetJoystick(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	pushJoystick(L, SDL_GameControllerGetJoystick(con));
	return 1;
}

static int l_GameController_EventState(lua_State* L) {
	int state = checkEventState(L, 1);
	pushEventState(L, SDL_GameControllerEventState(state));
	return 1;
}

static int l_GameController_Update(lua_State* L) {
	SDL_GameControllerUpdate();
	return 0;
}

static int l_GameController_HasAxis(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_GameControllerAxis axis = checkGameControllerAxis(L, 2);
	lua_pushboolean(L, SDL_GameControllerHasAxis(con, axis));
	return 1;
}

static int l_GameController_GetAxis(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_GameControllerAxis axis = checkGameControllerAxis(L, 2);
	Sint16 value = SDL_GameControllerGetAxis(con, axis);
	double norm = value / (value >= 0 ? 32767.0 : 32768.0);
	lua_pushnumber(L, norm);
	return 1;
}

static int l_GameController_HasButton(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_GameControllerButton button = checkGameControllerButton(L, 2);
	lua_pushboolean(L, SDL_GameControllerHasButton(con, button));
	return 1;
}

static int l_GameController_GetButton(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_GameControllerButton button = checkGameControllerButton(L, 2);
	lua_pushboolean(L, SDL_GameControllerHasButton(con, button));
	return 1;
}

static int l_GameController_GetNumTouchpads(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushinteger(L, SDL_GameControllerGetNumTouchpads(con));
	return 1;
}

static int l_GameController_GetNumTouchpadFingers(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	int index = (int)luaL_checkinteger(L, 2);
	lua_pushinteger(L, SDL_GameControllerGetNumTouchpadFingers(con, index));
	return 1;
}

static int l_GameController_GetTouchpadFinger(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	int index = (int)luaL_checkinteger(L, 2);
	int finger = (int)luaL_checkinteger(L, 3);
	Uint8 state;
	float x, y, pressure;
	if (SDL_GameControllerGetTouchpadFinger(con, index, finger, &state, &x, &y, &pressure) == 0) {
		lua_pushboolean(L, state);
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, pressure);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 4;
}

static int l_GameController_HasSensor(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_SensorType sen = checkSensorType(L, 2);
	lua_pushboolean(L, SDL_GameControllerHasSensor(con, sen));
	return 1;
}

static int l_GameController_SetSensorEnabled(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_SensorType sen = checkSensorType(L, 2);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 3);
	lua_pushboolean(L, SDL_GameControllerSetSensorEnabled(con, sen, state) == 0);
	return 1;
}

static int l_GameController_IsSensorEnabled(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_SensorType sen = checkSensorType(L, 2);
	lua_pushboolean(L, SDL_GameControllerIsSensorEnabled(con, sen));
	return 1;
}

static int l_GameController_GetSensorDataRate(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_SensorType sen = checkSensorType(L, 2);
	lua_pushnumber(L, SDL_GameControllerGetSensorDataRate(con, sen));
	return 1;
}

static int l_GameController_GetSensorData(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	SDL_SensorType sen = checkSensorType(L, 2);
	float values[MAXSENSORS] = {};

	if (SDL_GameControllerGetSensorData(con, sen, values, MAXSENSORS) == 0) {
		for (int i = 0; i < MAXSENSORS; i++) {
			lua_pushnumber(L, values[i]);
		}
	}
	else {
		for (int i = 0; i < MAXSENSORS; i++) {
			lua_pushnil(L);
		}
	}
	return MAXSENSORS;
}

static int l_GameController_Rumble(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	double low = luaL_checknumber(L, 2);
	double high = luaL_checknumber(L, 3);
	Uint32 ms = (Uint32)checkroundnumber(L, 4);
	low = low < 0.0 ? 0.0 : (low > 1.0 ? 1.0 : low);
	high = high < 0.0 ? 0.0 : (high > 1.0 ? 1.0 : high);
	Uint16 lowfrq = (Uint16)(0xFFFF * low);
	Uint16 highfrq = (Uint16)(0xFFFF * high);
	lua_pushboolean(L, SDL_GameControllerRumble(con, lowfrq, highfrq, ms) == 0);
	return 1;
}

static int l_GameController_RumbleTriggers(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	double left = luaL_checknumber(L, 2);
	double right = luaL_checknumber(L, 3);
	Uint32 ms = (Uint32)checkroundnumber(L, 4);
	left = left < 0.0 ? 0.0 : (left > 1.0 ? 1.0 : left);
	right = right < 0.0 ? 0.0 : (right > 1.0 ? 1.0 : right);
	Uint16 leftfrq = (Uint16)(0xFFFF * left);
	Uint16 rightfrq = (Uint16)(0xFFFF * right);
	lua_pushboolean(L, SDL_GameControllerRumbleTriggers(con, leftfrq, rightfrq, ms) == 0);
	return 1;
}

static int l_GameController_HasLED(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushboolean(L, SDL_GameControllerHasLED(con));
	return 1;
}

static int l_GameController_HasRumble(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushboolean(L, SDL_GameControllerHasRumble(con));
	return 1;
}

static int l_GameController_HasRumbleTriggers(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	lua_pushboolean(L, SDL_GameControllerHasRumbleTriggers(con));
	return 1;
}

static int l_GameController_SetLED(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	Uint8 r = (Uint8)checkroundnumber(L, 2);
	Uint8 g = (Uint8)checkroundnumber(L, 3);
	Uint8 b = (Uint8)checkroundnumber(L, 4);
	lua_pushboolean(L, SDL_GameControllerSetLED(con, r, g, b) == 0);
	return 1;
}

static int l_GameController_Close(lua_State* L) {
	SDL_GameController* con = checkGameController(L, 1);
	
	removeJoystick(L, SDL_GameControllerGetJoystick(con));
	removeGameController(L, con);
	
	SDL_GameControllerClose(con);
	luaEXT_setudata(L, 1, NULL);


	return 0;

}