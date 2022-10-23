#pragma once


static int l_void_set8(lua_State* L) {
	int8_t* p = (int8_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	int8_t value = (int8_t)luaL_checkinteger(L, 3);
	p = (int8_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}
static int l_void_set16(lua_State* L) {
	int16_t* p = (int16_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	int16_t value = (int16_t)luaL_checkinteger(L, 3);
	p = (int16_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}
static int l_void_set32(lua_State* L) {
	int32_t* p = (int32_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	int32_t value = (int32_t)luaL_checkinteger(L, 3);
	p = (int32_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}
static int l_void_set64(lua_State* L) {
	int64_t* p = (int64_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	int64_t value = (int64_t)luaL_checkinteger(L, 3);
	p = (int64_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}


static int l_void_setu8(lua_State* L) {
	uint8_t* p = (uint8_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	uint8_t value = (uint8_t)luaL_checkinteger(L, 3);
	p = (uint8_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}
static int l_void_setu16(lua_State* L) {
	uint16_t* p = (uint16_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	uint16_t value = (uint16_t)luaL_checkinteger(L, 3);
	p = (uint16_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}
static int l_void_setu32(lua_State* L) {
	uint32_t* p = (uint32_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	uint32_t value = (uint32_t)luaL_checkinteger(L, 3);
	p = (uint32_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}
static int l_void_setu64(lua_State* L) {
	uint64_t* p = (uint64_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	uint64_t value = (uint64_t)luaL_checkinteger(L, 3);
	p = (uint64_t*)((int8_t*)p + pos);
	*p = value;
	return 0;
}

static int l_void_get8(lua_State* L) {
	int8_t* p = (int8_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (int8_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}
static int l_void_get16(lua_State* L) {
	int16_t* p = (int16_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (int16_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}
static int l_void_get32(lua_State* L) {
	int32_t* p = (int32_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (int32_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}
static int l_void_get64(lua_State* L) {
	int64_t* p = (int64_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (int64_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}

static int l_void_getu8(lua_State* L) {
	uint8_t* p = (uint8_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (uint8_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}
static int l_void_getu16(lua_State* L) {
	uint16_t* p = (uint16_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (uint16_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}
static int l_void_getu32(lua_State* L) {
	uint32_t* p = (uint32_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (uint32_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}
static int l_void_getu64(lua_State* L) {
	uint64_t* p = (uint64_t*)luaEXT_checkudata(L, 1, ID_Void);
	size_t pos = luaL_checkinteger(L, 2);
	p = (uint64_t*)((int8_t*)p + pos);
	lua_pushinteger(L, *p);
	return 1;
}


