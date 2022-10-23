#pragma once

static int l_render_RenderReadPixels(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	Uint32 format;
	if (lua_isstring(L, 2)) {
		format = checkPixelFormatEnum(L, 2);
	}
	else {
		SDL_PixelFormat* pf = checkPixelFormat(L, 2);
		format = pf->format;
	}
	int w,h;
	SDL_GetRendererOutputSize(ren, &w, &h);
	SDL_Surface* sur = SDL_CreateRGBSurfaceWithFormat(0, w, h, SDL_BITSPERPIXEL(format), format);
	if (sur != NULL) {
		if (SDL_RenderReadPixels(ren, NULL, format, sur->pixels, sur->pitch) == 0) {
			pushSurface(L, sur);
		}
		else {
			SDL_FreeSurface(sur);
			lua_pushnil(L);
		}
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_render_GetNumDrivers(lua_State* L) {
	lua_pushinteger(L, SDL_GetNumRenderDrivers());
	return 1;
}

static int l_render_GetDriverInfo(lua_State* L) {
	int index = (int)luaL_checkinteger(L, 1);
	SDL_RendererInfo ri;
	if (SDL_GetRenderDriverInfo(index, &ri) == 0) {
		pushRenderInfo(L, &ri);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_render_create(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	int index = (int)luaL_optinteger(L, 2, -1);
	Uint32 flags = checkRendererFlags(L, 3, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Renderer* ren = SDL_CreateRenderer(win, index, flags);
	pushRenderer(L, ren);

	debugoutput(L, "[Create]", ID_Renderer, ren);
	return 1;
}

static int l_render_CreateSoftware(lua_State* L) {
	SDL_Surface* s = checkSurface(L,1);
	SDL_Renderer* ren = SDL_CreateSoftwareRenderer(s);
	pushRenderer(L, ren);
	
	debugoutput(L, "[Create]", ID_Renderer, ren);
	return 1;
}

static int l_render_Get(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	pushRenderer(L, SDL_GetRenderer(win));
	return 1;
}

static int l_render_GetInfo(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_RendererInfo ri;
	if (SDL_GetRendererInfo(ren, &ri) == 0) {
		pushRenderInfo(L, &ri);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_render_GetOutputSize(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	int w, h;
	if (SDL_GetRendererOutputSize(ren, &w, &h)==0) {
		lua_pushinteger(L, w);
		lua_pushinteger(L, h);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 2;
}

static int l_render_CreateTexture(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);

	if (isType(L, 2, ID_Surface)) {
		SDL_Surface* sur = checkSurface(L, 2);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, sur);
		pushTexture(L, tex);

		debugoutput(L, "[Create]", ID_Texture, tex);
		return 1;
	}

	Uint32 format;
	if (lua_isstring(L, 2)) {
		format = checkPixelFormatEnum(L, 2);
	}
	else {
		SDL_PixelFormat* pf = checkPixelFormat(L, 2);
		format = pf->format;
	}
	int access = checkTextureAccess(L, 3);
	int w = (int)checkroundnumber(L, 4);
	int h = (int)checkroundnumber(L, 5);
	SDL_Texture* tex = SDL_CreateTexture(ren, format, access, w, h);
	pushTexture(L,tex);
	debugoutput(L, "[Create]", ID_Texture, tex);
	return 1;
}

static int l_texture_Query(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	Uint32 format;
	int access, w, h;
	if (SDL_QueryTexture(tex, &format, &access, &w, &h) == 0) {
		pushPixelFormatEnum(L, (SDL_PixelFormatEnum)format);
		pushTextureAccess(L, (SDL_TextureAccess)access);
		lua_pushinteger(L, w);
		lua_pushinteger(L, h);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 4;
}

static int l_texture_SetColorMod(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	Uint8 r = (Uint8)checkroundnumber(L, 2);
	Uint8 g = (Uint8)checkroundnumber(L, 3);
	Uint8 b = (Uint8)checkroundnumber(L, 4);
	lua_pushboolean(L, SDL_SetTextureColorMod(tex, r, g, b) == 0);
	return 1;
}

static int l_texture_GetColorMod(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	Uint8 r, g, b;
	if (SDL_GetTextureColorMod(tex, &r, &g, &b) == 0) {
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

static int l_texture_SetAlphaMod(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	Uint8 alpha = (Uint8)checkroundnumber(L, 2);
	lua_pushboolean(L, SDL_SetTextureAlphaMod(tex, alpha) == 0);
	return 1;
}

static int l_texture_GetAlphaMod(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	Uint8 alpha;
	if (SDL_GetTextureAlphaMod(tex, &alpha) == 0) {
		lua_pushinteger(L, alpha);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_texture_SetBlendMode(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_BlendMode blend = checkBlendMode(L, 2);
	lua_pushboolean(L, SDL_SetTextureBlendMode(tex, blend) == 0);
	return 1;
}

static int l_texture_GetBlendMode(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_BlendMode blend;
	if (SDL_GetTextureBlendMode(tex, &blend) == 0) {
		pushBlendMode(L, blend);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_texture_SetScaleMode(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_ScaleMode scale = checkScaleMode(L, 2);
	lua_pushboolean(L, SDL_SetTextureScaleMode(tex, scale) == 0);
	return 1;
}

static int l_texture_GetScaleMode(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_ScaleMode scale;
	if (SDL_GetTextureScaleMode(tex, &scale) == 0) {
		pushScaleMode(L, scale);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_texture_SetUserData(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	void* data = (void*)luaL_checkinteger(L, 2);
	lua_pushboolean(L, SDL_SetTextureUserData(tex, data) == 0);
	return 1;
}

static int l_texture_GetUserData(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	lua_pushinteger(L, (lua_Integer)SDL_GetTextureUserData(tex));
	return 1;
}

static int l_texture_Lock(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_Rect r;
	void* pixel;
	int pitch;
	if (SDL_LockTexture(tex, toRect(L, 2, &r), &pixel, &pitch) == 0) {
		pushVoid(L, pixel);
		lua_pushinteger(L, pitch);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 2;
}

static int l_texture_LockToSurface(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_Rect r;
	SDL_Surface* sur;
	if (SDL_LockTextureToSurface(tex, toRect(L, 2, &r), &sur) == 0) {
		pushSurface(L, sur);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_texture_Unlock(lua_State* L) {
	SDL_Texture* tex = checkTexture(L,1);
	SDL_UnlockTexture(tex);
	return 0;
}

static int l_render_TargetSupported(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	lua_pushboolean(L, SDL_RenderTargetSupported(ren));
	return 1;
}

static int l_render_SetTarget(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Texture* tex = checkTextureOrNil(L, 2);
	lua_pushboolean(L, SDL_SetRenderTarget(ren, tex) == 0);
	return 1;
}

static int l_render_GetTarget(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	pushTexture(L, SDL_GetRenderTarget(ren));
	return 1;
}

static int l_render_SetLogicalSize(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	int w = (int)checkroundnumber(L, 1);
	int h = (int)checkroundnumber(L, 2);
	lua_pushboolean(L, SDL_RenderSetLogicalSize(ren, w, h) == 0);
	return 1;
}

static int l_render_GetLogicalSize(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	int w, h;
	SDL_RenderGetLogicalSize(ren, &w, &h);
	lua_pushinteger(L, w);
	lua_pushinteger(L, h);
	return 1;
}

static int l_render_SetIntegerScale(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	lua_pushboolean(L, SDL_RenderSetIntegerScale(ren, state) == 0);
	return 1;
}

static int l_render_GetIntegerScale(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	lua_pushboolean(L, SDL_RenderGetIntegerScale(ren));
	return 1;
}

static int l_render_SetViewport(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Rect r;
	lua_pushboolean(L, SDL_RenderSetViewport(ren, toRect(L, 2, &r)) == 0);
	return 1;
}

static int l_render_GetViewport(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Rect r;
	SDL_RenderGetViewport(ren, &r);
	pushRect(L, &r);
	return 1;
}

static int l_render_SetClipRect(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Rect r;
	lua_pushboolean(L, SDL_RenderSetClipRect(ren, toRect(L, 2, &r)) == 0);
	return 1;
}

static int l_render_GetClipRect(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	if (SDL_RenderIsClipEnabled(ren)) {
		SDL_Rect r;
		SDL_RenderGetClipRect(ren, &r);
		pushRect(L, &r);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_render_SetScale(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	float x = (float)luaL_checknumber(L, 2);
	float y = (float)luaL_checknumber(L, 3);
	lua_pushboolean(L, SDL_RenderSetScale(ren, x, y) == 0);
	return 1;
}

static int l_render_GetScale(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	float x, y;
	SDL_RenderGetScale(ren, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 1;
}

static int l_render_WindowToLogical(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	int winx = (int)checkroundnumber(L, 2);
	int winy = (int)checkroundnumber(L, 3);
	float logx, logy;
	SDL_RenderWindowToLogical(ren, winx, winy, &logx, &logy);
	lua_pushnumber(L, logx);
	lua_pushnumber(L, logy);
	return 2;
}

static int l_render_LogicalToWindow(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	float logx = (float)luaL_checknumber(L, 2);
	float logy = (float)luaL_checknumber(L, 3);
	int winx, winy;
	SDL_RenderLogicalToWindow(ren, logx, logy, &winx, &winy);
	lua_pushinteger(L, winx);
	lua_pushinteger(L, winy);
	return 2;
}

static int l_render_SetDrawColor(lua_State* L) {
	Uint8 r, g, b, a;
	SDL_Renderer* ren = checkRenderer(L,1);
	if (lua_istable(L, 2)) {
		SDL_Color col;
		toColor(L, 2, &col);
		r = col.r;
		g = col.g;
		b = col.b;
		a = col.a;
	}
	else {
		r = (Uint8)luaL_checkinteger(L, 2);
		g = (Uint8)luaL_checkinteger(L, 3);
		b = (Uint8)luaL_checkinteger(L, 4);
		a = (Uint8)luaL_checkinteger(L, 5);
	}
	lua_pushboolean(L, SDL_SetRenderDrawColor(ren, r, g, b, a) == 0);
	return 1;
}

static int l_render_GetDrawColor(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	Uint8 r, g, b, a;
	if (SDL_GetRenderDrawColor(ren, &r, &g, &b, &a) == 0) {
		lua_pushinteger(L, r);
		lua_pushinteger(L, g);
		lua_pushinteger(L, b);
		lua_pushinteger(L, a);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 4;
}

static int l_render_SetDrawBlendMode(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_BlendMode blend = checkBlendMode(L, 2);
	lua_pushboolean(L, SDL_SetRenderDrawBlendMode(ren, blend) == 0);
	return 1;
}

static int l_render_GetDrawBlendMode(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_BlendMode blend;
	if (SDL_GetRenderDrawBlendMode(ren, &blend) == 0) {
		pushBlendMode(L, blend);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_render_Clear(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	lua_pushboolean(L, SDL_RenderClear(ren) == 0);
	return 1;
}

static int l_render_DrawPoint(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	float x = (float)luaL_checknumber(L, 2);
	float y = (float)luaL_checknumber(L, 3);
	lua_pushboolean(L, SDL_RenderDrawPointF(ren, x, y) == 0);
	return 1;
}

static int l_render_DrawPoints(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	int pcount;
	SDL_FPoint* points = arrayFPoint(L, 2, &pcount);
	lua_pushboolean(L, SDL_RenderDrawPointsF(ren, points, pcount) == 0);
	FreeArray(points);
	return 1;
}

static int l_render_DrawLine(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	float x1 = (float)luaL_checknumber(L, 2);
	float y1 = (float)luaL_checknumber(L, 3);
	float x2 = (float)luaL_checknumber(L, 4);
	float y2 = (float)luaL_checknumber(L, 5);
	lua_pushboolean(L, SDL_RenderDrawLineF(ren, x1, y1, x2, y2) == 0);
	return 1;
}

static int l_render_DrawLines(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	int pcount;
	SDL_FPoint* points = arrayFPoint(L, 2, &pcount);
	lua_pushboolean(L, SDL_RenderDrawLinesF(ren, points, pcount) == 0);
	FreeArray(points);
	return 1;
}

static int l_render_DrawRect(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	if (lua_isnil(L, 2)) {
		lua_pushboolean(L, SDL_RenderDrawRect(ren, NULL));
	}
	else {
		SDL_FRect rf;
		lua_pushboolean(L, SDL_RenderDrawRectF(ren, toFRect(L, 2, &rf)) == 0);
	}
	return 1;
}

static int l_render_DrawRects(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	int pcount;
	SDL_FRect* rects = arrayFRect(L, 2, &pcount);
	lua_pushboolean(L, SDL_RenderDrawRectsF(ren, rects, pcount) == 0);
	FreeArray(rects);
	return 1;
}

static int l_render_FillRect(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	if (lua_isnil(L, 2)) {
		lua_pushboolean(L, SDL_RenderFillRect(ren, NULL));
	}
	else {
		SDL_FRect rf;
		lua_pushboolean(L, SDL_RenderFillRectF(ren, toFRect(L, 2, &rf)) == 0);
	}
	return 1;
}

static int l_render_FillRects(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	int pcount;
	SDL_FRect* rects = arrayFRect(L, 2, &pcount);
	lua_pushboolean(L, SDL_RenderFillRectsF(ren, rects, pcount) == 0);
	FreeArray(rects);
	return 1;
}

static int l_render_Copy(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Texture* tex = checkTexture(L, 2);
	SDL_Rect rs;
	SDL_FRect rd;
		
	lua_pushboolean(L, SDL_RenderCopyF(ren, tex, toRect(L, 3, &rs), toFRect(L, 4, &rd)) == 0);
	return 1;
}

static int l_render_CopyEx(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Texture* tex = checkTexture(L, 2);
	SDL_Rect rs;
	SDL_FRect rd;
	double angle = (double)luaL_checknumber(L, 5);
	SDL_FPoint center;
	SDL_RendererFlip flip = checkRendererFlip(L, 7);

	lua_pushboolean(L, SDL_RenderCopyExF(ren, tex, toRect(L, 3, &rs), toFRect(L, 4, &rd), angle, toFPoint(L, 6, &center), flip) == 0);
	return 1;
}

static int l_render_Geometry(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_Texture* tex = checkTextureOrNil(L, 2);
	int vcount;
	SDL_Vertex* ver = arrayVertex(L, 3, &vcount);
	int icount;
	int* index = arrayInt(L, 4, &icount, -1);//c start with 0, lua mit 1!
	lua_pushboolean(L, SDL_RenderGeometry(ren, tex, ver, vcount, index, icount) == 0);
	FreeArray(ver);
	FreeArray(index);
	return 1;
}

static int l_render_Present(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L,1);
	SDL_RenderPresent(ren);
	return 0;
}

static int l_texture_Destroy(lua_State* L) {
	SDL_Texture* tex = checkTexture(L, 1);
	SDL_DestroyTexture(tex);
	luaEXT_setudata(L, 1, NULL);
	debugoutput(L, "[Delete]", ID_Texture, tex);

	return 0;
}

static int l_render_Destroy(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	SDL_DestroyRenderer(ren);
	luaEXT_setudata(L, 1, NULL);
	debugoutput(L, "[Delete]", ID_Renderer, ren);
	return 0;
}

static int l_render_SetVSync(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	int state = (int)lua_toboolean(L, 2);
	lua_pushboolean(L, SDL_RenderSetVSync(ren, state) == 0);
	return 1;
}

