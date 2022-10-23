#pragma once

static int l_PixelFormat_Alloc(lua_State* L) {
	Uint32 const_pf = checkPixelFormatEnum(L, 1);
	SDL_PixelFormat* ret = SDL_AllocFormat(const_pf);
	pushPixelFormat(L, ret);
	return 1;
}

static int l_PixelFormat_Free(lua_State* L) {
	SDL_PixelFormat* pf = checkPixelFormat(L, 1);
	SDL_FreeFormat(pf);
	luaEXT_setudata(L, 1, NULL);
	return 0;
}

static int l_PixelFormat_MapRGB(lua_State* L) {
	SDL_PixelFormat* pf = checkPixelFormat(L,1);
	Uint8 r = (Uint8)checkroundnumber(L, 2);
	Uint8 g = (Uint8)checkroundnumber(L, 3);
	Uint8 b = (Uint8)checkroundnumber(L, 4);
	lua_pushinteger(L, SDL_MapRGB(pf, r, g, b));
	return 1;
}

static int l_PixelFormat_MapRGBA(lua_State* L) {
	SDL_PixelFormat* pf = checkPixelFormat(L,1);
	Uint8 r = (Uint8)checkroundnumber(L, 2);
	Uint8 g = (Uint8)checkroundnumber(L, 3);
	Uint8 b = (Uint8)checkroundnumber(L, 4);
	Uint8 a = (Uint8)checkroundnumber(L, 5);
	lua_pushinteger(L, SDL_MapRGBA(pf, r, g, b, a));
	return 1;
}

static int l_PixelFormat_GetRGB(lua_State* L) {	
	SDL_PixelFormat* pf = checkPixelFormat(L,1);
	Uint32 pixel = (Uint32)luaL_checkinteger(L, 2);
	
	Uint8 r, g, b;
	SDL_GetRGB(pixel, pf, &r, &g, &b);
	lua_pushinteger(L, r);
	lua_pushinteger(L, g);
	lua_pushinteger(L, b);
	return 3;
}

static int l_PixelFormat_GetRGBA(lua_State* L) {
	SDL_PixelFormat* pf = checkPixelFormat(L, 1);
	Uint32 pixel = (Uint32)luaL_checkinteger(L, 2);
		
	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, pf, &r, &g, &b, &a);
	lua_pushinteger(L, r);
	lua_pushinteger(L, g);
	lua_pushinteger(L, b);
	lua_pushinteger(L, a);
	return 4;
}



