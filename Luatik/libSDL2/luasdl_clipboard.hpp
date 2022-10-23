#pragma once

static int l_Clipboard_SetText(lua_State* L) {
	const char* txt = luaL_checkstring(L, 1);
	lua_pushboolean(L, SDL_SetClipboardText(txt) == 0);
	return 1;
}

static int l_Clipboard_GetText(lua_State* L) {
	const char* txt = SDL_GetClipboardText();
	lua_pushstring(L, txt);
	SDL_free((void*) txt);
	return 1;
}

static int l_Clipboard_HasText(lua_State* L) {
	lua_pushboolean(L, SDL_HasClipboardText());
	return 1;
}

static int l_Clipboard_GetSurface(lua_State* L) {
	SDL_Surface* surf = NULL;
	if (OpenClipboard(NULL)) {

		HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
		if (hBitmap != NULL) {

			BITMAP bm;
			GetObject(hBitmap, sizeof(bm), &bm);

			Uint32 pm = bm.bmBitsPixel == 32 ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_BGR24;
			surf = SDL_CreateRGBSurfaceWithFormat(0, bm.bmWidth, bm.bmHeight, bm.bmBitsPixel, pm);
			if (surf != NULL && SDL_LockSurface(surf) == 0) {
				GetBitmapBits(hBitmap, surf->h * surf->pitch, surf->pixels);
				SDL_UnlockSurface(surf);
			}
		}
		CloseClipboard();
	}

	pushSurface(L, surf);
	return 1;	
}
