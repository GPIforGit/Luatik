#pragma once

static int l_RW_Open(lua_State* L) {
	const char* file = luaL_checkstring(L, 1);
	const char* mode = checkRWMode(L, 2);
	pushRWops(L,SDL_RWFromFile(file, mode));
	return 1;
}

static int l_RW_Size(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	size_t ret = SDL_RWsize(rw);
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_RW_Seek(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Sint64 size = (Sint64)luaL_checkinteger(L, 2);
	int whence = checkRWSeek(L, 3);
	size_t ret = SDL_RWseek(rw, size, whence);
	if (ret >= 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_RW_Tell(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, SDL_RWtell(rw));
	return 1;
}

static int l_RW_ReadString(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	size_t size = (size_t)luaL_checkinteger(L, 2);
	void* buf = SDL_calloc(size, 1);
	size_t readed = SDL_RWread(rw, buf, 1, size);
	lua_pushlstring(L, (const char*)buf, readed);	
	SDL_free(buf);
	return 1;
}

static int l_RW_WriteString(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	size_t size;
	const void* data = (const void*)luaL_checklstring(L, 2, &size);
	lua_pushinteger(L, SDL_RWwrite(rw, data, 1, size));
	return 1;
}

static int l_RW_Close(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushboolean(L, SDL_RWclose(rw) == 0);
	luaEXT_setudata(L, 1, NULL);
	return 1;
}

static int l_RW_Load(lua_State* L) {
	const char* file = luaL_checkstring(L, 1);
	size_t size;
	void* buf = SDL_LoadFile(file, &size);
	lua_pushlstring(L, file, size);
	SDL_free(buf);
	return 1;
}
		
static int l_RW_Save(lua_State* L) {
	const char* file = luaL_checkstring(L, 1);
	size_t size;
	void* data = (void*)luaL_checklstring(L, 2, &size);
	SDL_RWops* rw = SDL_RWFromFile(file, "WB");
	if (rw == NULL) {
		lua_pushnil(L);
	}
	else {
		lua_pushinteger(L, SDL_RWwrite(rw, data, 1, size));
		SDL_RWclose(rw);
	}
	return 1;
}

static int l_RW_ReadU8(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, SDL_ReadU8(rw));
	return 1;
}

static int l_RW_ReadLEU16(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, SDL_ReadLE16(rw));
	return 1;
}

static int l_RW_ReadBEU16(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, SDL_ReadBE16(rw));
	return 1;
}

static int l_RW_ReadLEU32(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, SDL_ReadLE32(rw));
	return 1;
}

static int l_RW_ReadBEU32(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, SDL_ReadBE32(rw));
	return 1;
}

static int l_RW_ReadS8(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, (Sint8)SDL_ReadU8(rw));
	return 1;
}

static int l_RW_ReadLES16(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L,(Sint16) SDL_ReadLE16(rw));
	return 1;
}

static int l_RW_ReadBES16(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, (Sint16)SDL_ReadBE16(rw));
	return 1;
}

static int l_RW_ReadLES32(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, (Sint32)SDL_ReadLE32(rw));
	return 1;
}

static int l_RW_ReadBES32(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, (Sint32)SDL_ReadBE32(rw));
	return 1;
}


static int l_RW_ReadLES64(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, (Sint64)SDL_ReadLE64(rw));
	return 1;
}

static int l_RW_ReadBES64(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	lua_pushinteger(L, (Sint64)SDL_ReadBE64(rw));
	return 1;
}

static int l_RW_ReadLEFloat(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		float f;
		Uint32 ui32;
	} swapper;
	swapper.ui32 = SDL_ReadLE32(rw);
	lua_pushnumber(L, swapper.f);
	return 1;
}

static int l_RW_ReadBEFloat(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		float f;
		Uint32 ui32;
	} swapper;
	swapper.ui32 = SDL_ReadBE32(rw);
	lua_pushnumber(L, swapper.f);
	return 1;
}

static int l_RW_ReadLEDouble(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		double d;
		Uint64 ui64;
	} swapper;
	swapper.ui64 = SDL_ReadLE64(rw);
	lua_pushnumber(L, swapper.d);
	return 1;
}

static int l_RW_ReadBEDouble(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		double d;
		Uint64 ui64;
	} swapper;
	swapper.ui64 = SDL_ReadBE64(rw);
	lua_pushnumber(L, swapper.d);
	return 1;
}

static int l_RW_Write8(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint8 value = (Uint8)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteU8(rw, value) != 0);
	return 1;
}

static int l_RW_WriteLE16(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint16 value = (Uint16)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteLE16(rw, value) != 0);
	return 1;
}

static int l_RW_WriteBE16(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint16 value = (Uint16)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteBE16(rw, value) != 0);
	return 1;
}

static int l_RW_WriteLE32(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint32 value = (Uint32)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteLE32(rw, value) != 0);
	return 1;
}

static int l_RW_WriteBE32(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint32 value = (Uint32)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteBE32(rw, value) != 0);
	return 1;
}

static int l_RW_WriteLE64(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint32 value = (Uint32)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteLE64(rw, value) != 0);
	return 1;
}

static int l_RW_WriteBE64(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	Uint32 value = (Uint32)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_WriteBE64(rw, value) != 0);
	return 1;
}

static int l_RW_WriteLEFloat(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		float f;
		Uint32 ui32;
	}swapper;
	swapper.f = (float) luaL_checknumber(L, 2);
	lua_pushboolean(L, SDL_WriteLE32(rw, swapper.ui32) != 0);
	return 1;
}

static int l_RW_WriteBEFloat(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		float f;
		Uint32 ui32;
	}swapper;
	swapper.f = (float)luaL_checknumber(L, 2);
	lua_pushboolean(L, SDL_WriteBE32(rw, swapper.ui32) != 0);
	return 1;
}

static int l_RW_WriteLEDouble(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		double d;
		Uint64 ui64;
	}swapper;
	swapper.d = luaL_checknumber(L, 2);
	lua_pushboolean(L, SDL_WriteLE64(rw, swapper.ui64) != 0);
	return 1;
}

static int l_RW_WriteBEDouble(lua_State* L) {
	SDL_RWops* rw = checkRWops(L, 1);
	union {
		double d;
		Uint64 ui64;
	}swapper;
	swapper.d = luaL_checknumber(L, 2);
	lua_pushboolean(L, SDL_WriteBE64(rw, swapper.ui64) != 0);
	return 1;
}

