#pragma once

static int l_Display_GetNum(lua_State* L) {
	lua_pushinteger(L, SDL_GetNumVideoDisplays());
	return 1;
}

static int l_Display_GetName(lua_State* L) {
	int i = (int)luaL_checkinteger(L, 1);
	lua_pushstring(L, SDL_GetDisplayName(i));
	return 1;
}

static int l_Display_GetBounds(lua_State* L) {
	int i = (int)luaL_checkinteger(L, 1);
	SDL_Rect r = { 0,0,0,0 };
	if (SDL_GetDisplayBounds(i, &r) == 0) {
		pushRect(L, &r);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Display_GetUsableBounds(lua_State* L) {
	int i = (int)luaL_checkinteger(L, 1);
	SDL_Rect r = { 0,0,0,0 };
	if (SDL_GetDisplayUsableBounds(i, &r) == 0) {
		pushRect(L, &r);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Display_GetDPI(lua_State* L) {
	int i = (int)luaL_checkinteger(L, 1);
	float ddpi, hdpi, vdpi;
	if (SDL_GetDisplayDPI(i, &ddpi, &hdpi, &vdpi) == 0) {
		lua_pushnumber(L, ddpi);
		lua_pushnumber(L, hdpi);
		lua_pushnumber(L, vdpi);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 3;
}

static int l_Display_GetOrientation(lua_State* L) {
	int i = (int)luaL_checkinteger(L, 1);
	SDL_DisplayOrientation o = SDL_GetDisplayOrientation(i);
	if (o != SDL_ORIENTATION_UNKNOWN) {
		pushDisplayOrientation(L, o);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Display_GetDesktopMode(lua_State* L) {
	int di = (int)luaL_checkinteger(L, 1);
	SDL_DisplayMode ret;
	if (SDL_GetDesktopDisplayMode(di, &ret) == 0) {
		pushDisplayMode(L, &ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Window_GetDisplayIndex(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int index = SDL_GetWindowDisplayIndex(win);
	if (index >= 0) {
		lua_pushinteger(L, index);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Window_GetPixelFormat(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	Uint32 pfe = (Uint32)SDL_GetWindowPixelFormat(win);
	if (pfe != SDL_PIXELFORMAT_UNKNOWN) {
		pushPixelFormatEnum(L, (SDL_PixelFormatEnum)pfe);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Window_Create(lua_State* L) {
	const char* title = luaL_checkstring(L, 1);
	int x = checkWindowPos(L, 2);
	int y = checkWindowPos(L, 3);
	int w = (int)checkroundnumber(L, 4);
	int h = (int)checkroundnumber(L, 5);
	uint64_t flags = checkWindowFlags(L, 6, 0);

	if (flags & SDL_WINDOW_ALLOW_HIGHDPI) {
		// int ret = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		// SDL ignores highdpi under windows! 
		SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
	}

	if (flags & WINDOWFLAG_SHAPED) {
		pushWindow(L, SDL_CreateShapedWindow(title, x, y, w, h, flags & WINDOWFLAG_MASK));
	}
	else {
		pushWindow(L, SDL_CreateWindow(title, x, y, w, h, flags & WINDOWFLAG_MASK));
	}
	return 1;
}

static int l_Window_SetHitBox(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	SDL_Surface* sur = checkSurfaceOrNil(L, 2);
	if (sur == NULL) {
		lua_pushboolean(L, SDL_SetWindowHitTest(win, NULL, NULL)==0);
	} else{

		lua_pushboolean(L, SDL_SetWindowHitTest(win, HitTest, (void*)sur)==0);
	}
	return 1;
}

static int l_Window_SetShape(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	SDL_Surface* sur = checkSurface(L, 2);
	SDL_WindowShapeMode wsm;
	wsm.mode = checkWindowShapeMode(L, 3);
	if (wsm.mode == ShapeModeColorKey) {
		if (toColor(L, 4, &wsm.parameters.colorKey) == NULL) {
			luaL_error(L, "Argument %d should be a color table.", 4);
		}
	}
	else if (wsm.mode != ShapeModeDefault) {
		wsm.parameters.binarizationCutoff = (Uint8)checkroundnumber(L, 4);
	}
	lua_pushboolean(L, SDL_SetWindowShape(win, sur, &wsm) == 0);
	return 1;
}

static int l_Window_GetShape(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	SDL_WindowShapeMode wsm;
	if (SDL_GetShapedWindowMode(win, &wsm) == 0) {
		pushWindowShapeMode(L, wsm.mode);

		if (wsm.mode == ShapeModeColorKey) {
			pushColor(L, &wsm.parameters.colorKey);
			return 2;
		}
		else if (wsm.mode != ShapeModeDefault) {
			lua_pushinteger(L, wsm.parameters.binarizationCutoff);
			return 2;
		}
	}
	else {
		lua_pushnil(L);
	}
	return 1;	
}

static int l_Window_GetFlags(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	uint64_t flags = SDL_GetWindowFlags(win);
	if (SDL_IsShapedWindow(win)) {
		flags |= WINDOWFLAG_SHAPED;			\
	}
	pushWindowFlags(L, flags );
	return 1;
}

static int l_Window_SetTitle(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	const char* title = luaL_checkstring(L, 2);
	SDL_SetWindowTitle(win, title);
	return 0;
}

static int l_Window_GetTitle(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	lua_pushstring(L, SDL_GetWindowTitle(win));
	return 1;
}

static int l_Window_SetIcon(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_Surface* icon = (SDL_Surface*)luaEXT_checkudata(L, 2, ID_Surface);
	SDL_SetWindowIcon(win, icon);
	return 0;
}

static int l_Window_SetData(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	const char* key = luaL_checkstring(L, 2);
	void* value = (void*)luaL_checkinteger(L, 3);
	lua_pushinteger(L, (lua_Integer)SDL_SetWindowData(win, key, value));
	return 1;
}

static int l_Window_GetData(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	const char* key = luaL_checkstring(L, 2);
	lua_pushinteger(L, (lua_Integer)SDL_GetWindowData(win, key));
	return 1;
}

static int l_Window_SetPosition(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int x = checkWindowPos(L, 2);
	int y = checkWindowPos(L, 3);
	SDL_SetWindowPosition(win, x, y);
	return 0;
}

static int l_Window_GetPosition(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int x, y;
	SDL_GetWindowPosition(win, &x, &y);
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	return 2;
}

static int l_Window_SetSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	SDL_SetWindowSize(win, w, h);
	return 0;
}

static int l_Window_GetSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	lua_pushinteger(L, w);
	lua_pushinteger(L, h);
	return 2;
}

static int l_Window_GetBordersSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int top, left, bottom, right;
	if (SDL_GetWindowBordersSize(win, &top, &left, &bottom, &right) == 0) {
		lua_pushinteger(L, top);
		lua_pushinteger(L, left);
		lua_pushinteger(L, bottom);
		lua_pushinteger(L, right);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 4;
}

static int l_Window_SetMinimumSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	SDL_SetWindowMinimumSize(win, w, h);
	return 0;
}

static int l_Window_GetMinimumSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int w, h;
	SDL_GetWindowMinimumSize(win, &w, &h);
	lua_pushinteger(L, w);
	lua_pushinteger(L, h);
	return 2;
}

static int l_Window_SetMaximumSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int w = (int)luaL_checkinteger(L, 2);
	int h = (int)luaL_checkinteger(L, 3);
	SDL_SetWindowMaximumSize(win, w, h);
	return 0;
}

static int l_Window_GetMaximumSize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	int w, h;
	SDL_GetWindowMaximumSize(win, &w, &h);
	lua_pushinteger(L, w);
	lua_pushinteger(L, h);
	return 2;
}

static int l_Window_SetBordered(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	SDL_SetWindowBordered(win, state);
	return 0;
}

static int l_Window_SetResizable(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	SDL_SetWindowResizable(win, state);
	return 0;
}

static int l_Window_SetAlwaysOnTop(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	SDL_SetWindowAlwaysOnTop(win, state);
	return 0;
}

static int l_Window_Show(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_ShowWindow(win);
	return 0;
}

static int l_Window_Hide(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_HideWindow(win);
	return 0;
}

static int l_Window_Raise(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_RaiseWindow(win);
	return 0;
}

static int l_Window_Maximize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_MaximizeWindow(win);
	return 0;
}

static int l_Window_Minimize(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_MinimizeWindow(win);
	return 0;
}

static int l_Window_Restore(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_RestoreWindow(win);
	return 0;
}

static int l_Window_SetFullscreen(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	Uint32 flags = checkWindowFullscreen(L, 2);
	lua_pushboolean(L, SDL_SetWindowFullscreen(win, flags) == 0);
	return 1;
}

static int l_Window_GetSurface(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	luaEXT_pushudata(L, SDL_GetWindowSurface(win), ID_Surface);
	return 1;
}

static int l_Window_UpdateSurface(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	lua_pushboolean(L, SDL_UpdateWindowSurface(win) == 0);
	return 1;
}

static int l_Window_SetGrab(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	SDL_SetWindowGrab(win, state);
	return 0;
}

static int l_Window_SetKeyboardGrab(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	SDL_SetWindowKeyboardGrab(win, state);
	return 0;
}

static int l_Window_SetMouseGrab(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_bool state = (SDL_bool)lua_toboolean(L, 2);
	SDL_SetWindowMouseGrab(win, state);
	return 0;
}

static int l_Window_GetGrab(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	lua_pushboolean(L, SDL_GetWindowGrab(win));
	return 1;
}

static int l_Window_GetKeyboardGrab(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	lua_pushboolean(L, SDL_GetWindowKeyboardGrab(win));
	return 1;
}

static int l_Window_GetMouseGrab(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	lua_pushboolean(L, SDL_GetWindowMouseGrab(win));
	return 1;
}

static int l_Window_GetGrabbed(lua_State* L) {
	pushWindow(L, SDL_GetGrabbedWindow());
	return 1;
}

static int l_Window_SetMouseRect(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	if (lua_isnoneornil(L, 2)) {
		lua_pushboolean(L, SDL_SetWindowMouseRect(win, NULL) == 0);
	}
	else {
		SDL_Rect r;
		lua_pushboolean(L, SDL_SetWindowMouseRect(win, toRect(L, 2,&r)) == 0);
	}
	return 1;
}

static int l_Window_GetMouseRect(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	const SDL_Rect* r = SDL_GetWindowMouseRect(win);
	if (r == NULL) {
		lua_pushnil(L);
	}
	else {
		pushRect(L, r);
	}
	return 1;
}

static int l_Window_SetOpacity(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	float o = (float)luaL_checknumber(L, 2);
	lua_pushboolean(L, SDL_SetWindowOpacity(win, o) == 0);
	return 1;
}

static int l_Window_GetOpacity(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	float o;
	if (SDL_GetWindowOpacity(win, &o) == 0) {
		lua_pushnumber(L, o);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Window_ModalFor(lua_State* L) {
	SDL_Window* win1 = checkWindow(L,1);
	SDL_Window* win2 = checkWindow(L, 2);
	lua_pushboolean(L, SDL_SetWindowModalFor(win1, win2) == 0);
	return 1;
}

static int l_Window_SetInputFocus(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	lua_pushboolean(L, SDL_SetWindowInputFocus(win) == 0);
	return 1;
}

static int l_Window_Flash(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	SDL_FlashOperation f = checkFlashOperation(L, 2);
	lua_pushboolean(L, SDL_FlashWindow(win,f) == 0);
	return 1;
}

static int l_Window_Destroy(lua_State* L) {
	SDL_Window* win = checkWindow(L,1);
	removeWindow(L, win);
	SDL_DestroyWindow(win);	
	luaEXT_setudata(L, 1, NULL);
	return 0;
}

static int l_ScreenSaver_IsEnabled(lua_State* L) {
	lua_pushboolean(L, SDL_IsScreenSaverEnabled());
	return 1;
}

static int l_ScreenSaver_Enable(lua_State* L) {
	SDL_IsScreenSaverEnabled();
	return 0;
}

static int l_ScreenSaver_Disable(lua_State* L) {
	SDL_IsScreenSaverEnabled();
	return 0;
}

static int l_Window_GetOsHandle(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	if (SDL_GetWindowWMInfo(win, &info)) {
		pushHWND(L, info.info.win.window);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}



