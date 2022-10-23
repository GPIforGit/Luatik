#pragma once


static int l_Surface_GetPixelFormat(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	pushPixelFormat(L, sf->format);
	return 1;
}

static int l_Surface_GetSize(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	lua_pushinteger(L, sf->w);
	lua_pushinteger(L, sf->h);
	lua_pushinteger(L, sf->pitch);
	return 3;
}

static int l_Surface_GetPixels(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	pushVoid(L, sf->pixels);
	return 1;
}

static int l_Surface_CreateRGB(lua_State* L) {
	int w = (int)checkroundnumber(L, 1);
	int h = (int)checkroundnumber(L, 2);
	SDL_Surface* sf = NULL;
	if (lua_isstring(L, 3)) {
		Uint32 format = checkPixelFormatEnum(L, 3);
		sf = SDL_CreateRGBSurfaceWithFormat(0, w, h, SDL_BITSPERPIXEL(format), format);
	}
	else {
		SDL_PixelFormat* pf = checkPixelFormat(L, 3);
		sf = SDL_CreateRGBSurfaceWithFormat(0, w, h, pf->BitsPerPixel, pf->format);
	}
	pushSurface(L, sf);
	debugoutput(L, "[Create]", ID_Surface, sf);
	return 1;
}

static int l_Surface_Free(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_FreeSurface(sf);
	luaEXT_setudata(L, 1, NULL);
	debugoutput(L, "[Delete]", ID_Surface, sf);
	return 0;
}

static int l_Surface_Lock(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	lua_pushboolean(L, SDL_LockSurface(sf) == 0);
	return 1;
}

static int l_Surface_Unlock(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_UnlockSurface(sf);
	return 0;
}

static int l_Surface_LoadBMP(lua_State* L) {
	SDL_Surface* sf;
	if (lua_isstring(L, 1)) {
		const char* file = luaL_checkstring(L, 1);
		sf = SDL_LoadBMP(file);
	} else {
		SDL_RWops* rw = checkRWops(L, 1);
		sf = SDL_LoadBMP_RW(rw, 0);
	}
	pushSurface(L, sf);
	debugoutput(L, "[Create]", ID_Surface, sf);
	return 1;
}

static int l_Surface_SaveBMP(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	if (lua_isstring(L, 2)) {
		const char* file = luaL_checkstring(L, 2);
		lua_pushboolean(L, SDL_SaveBMP(sf, file) == 0);
	}
	else {
		SDL_RWops* rw = checkRWops(L, 2);
		lua_pushboolean(L, SDL_SaveBMP_RW(sf, rw, 0) == 0);
	}
	return 1;
}

static int l_Surface_SetRLE(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	int flag = (int)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_SetSurfaceRLE(sf, flag) == 0);
	return 1;
}

static int l_Surface_HasRLE(lua_State* L) {
	SDL_Surface* sf = checkSurfaceOrNil(L, 1);
	lua_pushboolean(L, SDL_HasSurfaceRLE(sf));
	return 1;
}

static int l_Surface_SetColorKey(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	int flag = (int)luaL_checkinteger(L, 2);
	Uint32 key = (Uint32)luaL_checkinteger(L, 3);
	lua_pushboolean(L, SDL_SetColorKey(sf, flag, key) == 0);
	return 1;
}

static int l_Surface_GetColorKey(lua_State* L) {
	SDL_Surface* sf = checkSurfaceOrNil(L, 1);
	if (SDL_HasColorKey(sf)) {
		Uint32 key;
		SDL_GetColorKey(sf, &key);
		lua_pushinteger(L, key);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Surface_SetColorMod(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	Uint8 r = (Uint8)checkroundnumber(L, 2);
	Uint8 g = (Uint8)checkroundnumber(L, 3);
	Uint8 b = (Uint8)checkroundnumber(L, 4);
	lua_pushboolean(L, SDL_SetSurfaceColorMod(sf, r, g, b) == 0);
	return 1;
}

static int l_Surface_GetColorMod(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	Uint8 r, g, b;
	if (SDL_GetSurfaceColorMod(sf, &r, &g, &b) == 0) {
		lua_pushinteger(L, r);
		lua_pushinteger(L, g);
		lua_pushinteger(L, b);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 3;
}

static int l_Surface_SetAlphaMod(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	Uint8 a = (Uint8)checkroundnumber(L, 2);
	lua_pushboolean(L, SDL_SetSurfaceAlphaMod(sf, a) == 0);
	return 1;
}

static int l_Surface_GetAlphaMod(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	Uint8 a;
	if (SDL_GetSurfaceAlphaMod(sf, &a) == 0) {
		lua_pushinteger(L, a);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Surface_SetBlendMode(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_BlendMode b = checkBlendMode(L, 2);
	lua_pushboolean(L, SDL_SetSurfaceBlendMode(sf, b) == 0);
	return 1;
}

static int l_Surface_GetBlendMode(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_BlendMode b;
	if (SDL_GetSurfaceBlendMode(sf, &b) == 0) {
		pushBlendMode(L, b);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Surface_SetClip(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	if (lua_isnil(L, 2)) {
		lua_pushboolean(L, SDL_SetClipRect(sf, NULL));
	}
	else {
		SDL_Rect r;
		lua_pushboolean(L, SDL_SetClipRect(sf, toRect(L, 2, &r)));
	}
	return 1;
}

static int l_Surface_GetClip(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_Rect r;
	SDL_GetClipRect(sf, &r);
	pushRect(L, &r);
	return 1;
}

static int l_Surface_Duplicate(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_Surface* nsf = SDL_DuplicateSurface(sf);
	pushSurface(L, nsf);
	return 1;
}

static int l_Surface_Convert(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	SDL_Surface* nsf = NULL;
	if (lua_isstring(L, 2)) {
		Uint32 f =checkPixelFormatEnum(L, 2);
		nsf = SDL_ConvertSurfaceFormat(sf, f, 0);
	}
	else {
		SDL_PixelFormat* f = checkPixelFormat(L, 2);
		nsf = SDL_ConvertSurface(sf, f, 0);
	}
	pushSurface(L, nsf);
	return 1;
}

static int l_Surface_FillRect(lua_State* L) {
	SDL_Surface* sf = checkSurface(L, 1);
	Uint32 c = (Uint32)luaL_checkinteger(L, 3);
	SDL_Rect r;
	lua_pushboolean(L, SDL_FillRect(sf, toRect(L, 2, &r), c) == 0);
	return 1;
}

static int l_Surface_Blit(lua_State* L) {
	SDL_Surface* sf1 = checkSurface(L, 1);
	SDL_Rect r1;
	SDL_Surface* sf2 = checkSurface(L, 3);
	SDL_Rect r2;
	lua_pushboolean(L, SDL_BlitSurface(sf1, toRect(L, 2, &r1), sf2, toRect(L, 4, &r2)) == 0);
	return 1;
}

static int l_Surface_BlitScaled(lua_State* L) {
	SDL_Surface* sf1 = checkSurface(L, 1);
	SDL_Rect r1;
	SDL_Surface* sf2 = checkSurface(L, 3);
	SDL_Rect r2;
	lua_pushboolean(L, SDL_BlitScaled(sf1, toRect(L, 2, &r1), sf2, toRect(L, 4, &r2)) == 0);
	return 1;
}

static int l_Surface_SoftStretch(lua_State* L) {
	SDL_Surface* sf1 = checkSurface(L, 1);
	SDL_Rect r1;
	SDL_Surface* sf2 = checkSurface(L, 3);
	SDL_Rect r2;
	lua_pushboolean(L, SDL_SoftStretch(sf1, toRect(L, 2, &r1), sf2, toRect(L, 4, &r2)) == 0);
	return 1;
}

static int l_Surface_SetYUVConversionMode(lua_State* L) {
	SDL_YUV_CONVERSION_MODE m = checkYUV_CONVERSION_MODE(L, 1);
	SDL_SetYUVConversionMode(m);
	return 0;
}

static int l_Surface_GetYUVConversionMode(lua_State* L) {
	pushYUV_CONVERSION_MODE(L, SDL_GetYUVConversionMode());
	return 1;
}

static int l_Surface_GetYUVConversionModeForResolution(lua_State* L) {
	int w = (int)checkroundnumber(L, 1);
	int h = (int)checkroundnumber(L, 2);
	pushYUV_CONVERSION_MODE(L, SDL_GetYUVConversionModeForResolution(w, h));
	return 1;
}



