#pragma once

static int l_menu_Create(lua_State* L) {
	HMENU menu = CreateMenu();
	pushHMENU(L, menu);
	return 1;
}

static int l_menu_CreatePopup(lua_State* L) {
	HMENU menu = CreatePopupMenu();
	pushHMENUsub(L, menu);
	return 1;
}

static int l_menu_Add(lua_State* L) {
	if (luaL_testudata(L, 1, ID_HMENU) != NULL) {
		HMENU bar = checkHMENU(L, 1);
		std::wstring str = luaEXT_checkwstring(L, 2);

		HMENU submenu = CreatePopupMenu();
		AppendMenuW(bar, MF_POPUP, (UINT_PTR)submenu, str.c_str());
		pushHMENUsub(L, submenu);
		return 1;
	}

	HMENU menu = checkHMENUsub(L, 1);

	if (lua_isnoneornil(L, 2)) {
		AppendMenuW(menu, MF_SEPARATOR, 0, NULL);
		return 0;
	}

	std::wstring str = luaEXT_checkwstring(L, 2);
	if (lua_isstring(L, 3)) {
		int id = checkMENUID(L, 3); //(int)luaL_checkinteger(L, 3);
		int flag = checkMenuFlags(L, 4, 0);
		AppendMenuW(menu, MF_STRING | flag, id, str.c_str());
		return 0;
	}

	HMENU submenu = checkHMENUsub(L, 3);
	AppendMenuW(menu, MF_STRING | MF_POPUP, (UINT_PTR)submenu, str.c_str());
	pushHMENUsub(L, submenu);
	return 1;

}

static int l_menu_SetWindow(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	HMENU bar = NULL;
	if (!lua_isnoneornil(L, 2)) {
		bar = checkHMENU(L, 2);
	}
	HWND w = GetHWND(win);
	lua_pushboolean(L, SetMenu(w, bar) != 0);
	DrawMenuBar(w);

	set_event_hook(L);
	SetWndProcHook(w, win);

	return 0;
}

static int l_menu_Height(lua_State* L) {
	lua_pushinteger(L, GetSystemMetrics(SM_CYMENU));
	return 1;
}

static int l_menu_Destroy(lua_State* L) {
	if (luaL_testudata(L, 1, ID_HMENU) != NULL) {
		HMENU bar = checkHMENU(L, 1);
		DestroyMenu(bar);
		return 0;
	}

	HMENU menu = checkHMENUsub(L, 1);
	DestroyMenu(menu);
	return 0;
}

static int l_menu_Show(lua_State* L) {
	HMENU menu = checkHMENUsub(L, 1);
	SDL_Window* swin = checkWindow(L, 2);
	POINT p;
	p.x = (int)checkroundnumber(L, 3);
	p.y = (int)checkroundnumber(L, 4);
	HWND hwin = GetHWND(swin);
	ClientToScreen(hwin, &p);
	int flag = GetSystemMetrics(SM_MENUDROPALIGNMENT);
	TrackPopupMenu(menu, flag | TPM_RIGHTBUTTON, p.x, p.y, 0, hwin, NULL);
	return 0;
}

static int l_menu_SetCheck(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int id = checkMENUID(L, 2); //(int)luaL_checkinteger(L, 2);
	bool state = lua_toboolean(L, 3);
	CheckMenuItem(menu, id, MF_BYCOMMAND | (state ? MF_CHECKED : MF_UNCHECKED));
	return 0;
}

static int l_menu_SetRadio(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int idFirst = checkMENUID(L, 2); // (int)luaL_checkinteger(L, 2);
	int idLast = checkMENUID(L, 3); //(int)luaL_checkinteger(L, 3);
	int id = checkMENUID(L, 4); //(int)luaL_checkinteger(L, 4);
	CheckMenuRadioItem(menu, idFirst, idLast, id, MF_BYCOMMAND);
	return 0;
}

static int l_menu_GetCheck(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int id = checkMENUID(L, 2); // (int)luaL_checkinteger(L, 2);
	lua_pushboolean(L, (GetMenuState(menu, id, MF_BYCOMMAND) & MF_CHECKED) != 0);
	return 1;
}

static int l_menu_SetText(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int id = checkMENUID(L, 2); //(int)luaL_checkinteger(L, 2);
	std::wstring str = luaEXT_checkwstring(L, 3);
	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STRING;
	info.dwTypeData = (LPWSTR)str.c_str();
	SetMenuItemInfoW(menu, id, false, &info);
	return 0;
}

static int l_menu_GetText(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int id = checkMENUID(L, 2); // (int)luaL_checkinteger(L, 2);
	MENUITEMINFOW info;
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STRING;
	info.dwTypeData = NULL;
	GetMenuItemInfoW(menu, id, false, &info);
	info.cch += 1;
	wchar_t* str = (wchar_t*)SDL_calloc(info.cch, sizeof(wchar_t));
	info.dwTypeData = str;
	GetMenuItemInfoW(menu, id, false, &info);
	luaEXT_pushwstring(L, str);
	SDL_free(str);
	return 1;
}

static int l_menu_SetEnable(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int id = checkMENUID(L, 2); // (int)luaL_checkinteger(L, 2);
	bool state = lua_toboolean(L, 3);
	EnableMenuItem(menu, id, state ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
	return 0;
}

static int l_menu_GetEnable(lua_State* L) {
	HMENU menu = checkAnyHMENU(L, 1);
	int id = checkMENUID(L, 2); //(int)luaL_checkinteger(L, 2);
	lua_pushboolean(L, (GetMenuState(menu, id, MF_BYCOMMAND) & MF_DISABLED) == 0);
	return 1;
}

