#pragma once

static int l_sensor_GetNum(lua_State* L) {
	lua_pushinteger(L, SDL_NumSensors());
	return 1;
}

static int l_sensor_GetName(lua_State* L) {
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		lua_pushstring(L, SDL_SensorGetDeviceName(index));
	}
	else {
		SDL_Sensor* sen = checkSensor(L, 1);
		lua_pushstring(L, SDL_SensorGetName(sen));
	}
	return 1;
}

static int l_sensor_GetType(lua_State*L){
	if (lua_isinteger(L, 1)) {
		int index = (int)luaL_checkinteger(L, 1);
		pushSensorType(L, SDL_SensorGetDeviceType(index));
	}
	else {
		SDL_Sensor* sen = checkSensor(L, 1);
		pushSensorType(L, SDL_SensorGetType(sen));
	}
	return 1;
}

static int l_sensor_Open(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	pushSensor(L, SDL_SensorOpen(index));
	return 1;
}

#define MAXSENSORS 3
static int l_sensor_GetData(lua_State* L) {
	float values[MAXSENSORS] = {};
	SDL_Sensor* sen = checkSensor(L, 1);
	if (SDL_SensorGetData(sen, values, MAXSENSORS) == 0) {
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

static int l_sensor_Close(lua_State* L) {
	SDL_Sensor* sen = checkSensor(L, 1);
	removeSensor(L, sen);
	SDL_SensorClose(sen);
	luaEXT_setudata(L, 1, NULL);
	return 0;
}

static int l_sensor_Update(lua_State* l) {
	SDL_SensorUpdate();
	return 0;
}

