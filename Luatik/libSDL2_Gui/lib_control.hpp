#pragma once

static int l_control_CreateButton(lua_State* L) {
	SDL_Window* parent = checkWindow(L, 1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	std::wstring text = luaEXT_checkwstring(L, 4);
	DWORD style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT | checkButtonFlags(L, 5);

	sControl* ctrl = CreateControl(L, Control_Button, text.c_str(), style, parent, w, h); // also push it on stack!
	return 1;
}
static int l_control_CreateCheckbox(lua_State* L) {
	SDL_Window* parent = checkWindow(L, 1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	std::wstring text = luaEXT_checkwstring(L, 4);
	DWORD style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT | BS_AUTOCHECKBOX | checkCheckboxFlags(L, 5);

	sControl* ctrl = CreateControl(L, Control_Checkbox, text.c_str(), style, parent, w, h); // also push it on stack!
	return 1;
}
static int l_control_CreateRadiobutton(lua_State* L) {
	SDL_Window* parent = checkWindow(L, 1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	std::wstring text = luaEXT_checkwstring(L, 4);
	DWORD style = WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | checkRadiobuttonFlags(L, 5);

	sControl* ctrl = CreateControl(L, Control_Radiobutton, text.c_str(), style, parent, w, h); // also push it on stack!
	return 1;
}
static int l_control_CreateSplitbutton(lua_State* L) {
	SDL_Window* parent = checkWindow(L, 1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	std::wstring text = luaEXT_checkwstring(L, 4);
	HMENU popup = checkHMENUsub(L, 5);
	DWORD style = WS_VISIBLE | WS_CHILD | BS_TEXT | BS_SPLITBUTTON | checkButtonFlags(L, 6);

	sControl* ctrl = CreateControl(L, Control_Splitbutton, text.c_str(), style, parent, w, h); // also push it on stack!

	ctrl->popup = popup;
	return 1;
}

static int l_control_CreateCombobox(lua_State* L) {
	SDL_Window* parent = checkWindow(L, 1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	DWORD style = WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS | checkComboboxFlags(L, 4);

	sControl* ctrl = CreateControl(L, Control_Combobox, NULL, style, parent, w, h);
		
	return 1;
}

static int l_control_AddItem(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	std::wstring text = luaEXT_checkwstring(L, 2);
	lua_Integer data = luaL_optinteger(L, 3, 0);
	int pos = luaL_optinteger(L, 4, -1);

	

	switch (ctrl->Type) {

	case Control_Combobox:
	{
		pos = SendMessageW(ctrl->hWnd, CB_INSERTSTRING, pos, (LPARAM)text.c_str());
		if (pos >= 0) {
			SendMessageW(ctrl->hWnd, CB_SETITEMDATA, pos, (LPARAM)data);
			lua_pushinteger(L, pos);
		}
		else {
			lua_pushnil(L);
		}
		return 1;
	}


	}

	lua_pushnil(L);
	return 1;
}
static int l_control_DeleteItem(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	int pos = luaL_checkinteger(L, 2);
	lua_pushboolean(L, SendMessageW(ctrl->hWnd, CB_DELETESTRING, pos, NULL) >= 0);
	return 1;
}

static int l_control_CountItems(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	lua_pushinteger(L, SendMessageW(ctrl->hWnd, CB_GETCOUNT, NULL, NULL));
	return 1;
}

static int l_control_SetItem(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	int pos = luaL_checkinteger(L, 2);
	if (!lua_isnoneornil(L, 3)) {
		std::wstring text = luaEXT_checkwstring(L, 3);
		setControlItemText(L, ctrl, pos, text.c_str());
	}
	if (!lua_isnoneornil(L, 4)) {
		lua_Integer data = luaL_checkinteger(L, 4);
		setControlItemData(L, ctrl, pos, data);
	}
	return 0;
}

static int l_control_GetItem(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	int pos = luaL_checkinteger(L, 2);
	pushControlItemText(L, ctrl, pos);
	pushControlItemData(L, ctrl, pos);
	return 2;
}

static int l_control_ClearItems(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	switch (ctrl->Type) {

	case Control_Combobox:
		SendMessageW(ctrl->hWnd, CB_RESETCONTENT, NULL, NULL);

	}
	return 0;
}

static int l_control_GetState(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	pushControlState(L, ctrl);
	switch (ctrl->Type) {

	case Control_Combobox:
	{
		int pos = SendMessageW(ctrl->hWnd, CB_GETCURSEL, 0, 0);
		if (pos >= 0) {
			pushControlItemText(L, ctrl, pos);
			pushControlItemData(L, ctrl, pos);			
		}
		else {
			lua_pushnil(L);
			lua_pushnil(L);
		}
		return 3;
	}

	}
	return 1;
}

static int l_control_SetState(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	switch (ctrl->Type) {
	case Control_Button:
		setControlState(L, ctrl, lua_toboolean(L, 2));
		break;

	case Control_Combobox:
		if (lua_isinteger(L, 2)) {
			setControlState(L, ctrl, luaL_checkinteger(L, 2));
		}
		else {
			std::wstring text = luaEXT_checkwstring(L, 2);
			SendMessageW(ctrl->hWnd, CB_SELECTSTRING, -1, (LPARAM)text.c_str());
		}
		break;

	}
	return 0;
}

static int l_control_GetText(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	int len = GetWindowTextLengthW(ctrl->hWnd) + 1;
	wchar_t* text = (wchar_t*)SDL_calloc(len, sizeof(wchar_t));
	GetWindowTextW(ctrl->hWnd, text, len + 1);
	luaEXT_pushwstring(L, text);
	SDL_free(text);
	return 1;
}

static int l_control_SetText(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	std::wstring text = luaEXT_checkwstring(L, 2);
	SetWindowTextW(ctrl->hWnd, text.c_str());
	return 0;
}

static int l_control_GetSize(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	RECT r;
	GetWindowRect(ctrl->hWnd, &r);
	MapWindowPoints(HWND_DESKTOP, GetParent(ctrl->hWnd), (LPPOINT)&r, 2);
	lua_pushinteger(L, r.left);
	lua_pushinteger(L, r.top);
	lua_pushinteger(L, r.right - r.left);

	if (ctrl->Type == Control_Combobox) {
		lua_pushinteger(L, SendMessageW(ctrl->hWnd, CB_GETITEMHEIGHT, -1, 0));
	}
	else {
		lua_pushinteger(L, r.bottom - r.top);
	}
	return 4;
}

static int l_control_SetSize(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);

	RECT r;
	GetWindowRect(ctrl->hWnd, &r);
	MapWindowPoints(HWND_DESKTOP, ctrl->hParent, (LPPOINT)&r, 2);
	int x = r.left;
	int y = r.top;
	int w = r.right - r.left;
	int h = r.bottom - r.top;
	if (ctrl->Type == Control_Combobox) {
		h = SendMessageW(ctrl->hWnd, CB_GETITEMHEIGHT, -1, 0);
	}



	if (lua_isnumber(L, 2) || lua_isnoneornil(L, 2)) {
		// simple set
		x = (int)optroundnumber(L, 2, x);
		y = (int)optroundnumber(L, 3, y);
		w = (int)optroundnumber(L, 4, w);
		h = (int)optroundnumber(L, 5, h);

		if (x < 0 || y < 0) {
			RECT r;
			GetClientRect(ctrl->hParent, &r);

			if (x < 0) {
				x = (r.right - r.left) - w + x + 1;
			}
			if (y < 0) {
				y = (r.bottom - r.top) - h + y + 1;
			}
		}

	}
	else {
		int pos = checkPos(L, 2);
		int space = (int)checkroundnumber(L, 3);
		sControl* anker = checkControl(L, 4);
		w = (int)optroundnumber(L, 5, w);
		h = (int)optroundnumber(L, 6, h);
		RECT r;
		GetWindowRect(anker->hWnd, &r);
		MapWindowPoints(HWND_DESKTOP, GetParent(ctrl->hWnd), (LPPOINT)&r, 2);

		switch (pos) {
		case Pos_TopLeft:
			x = r.left;
			y = r.top - h - space;
			break;
		case Pos_Top:
			x = (r.left + r.right - w) / 2;
			y = r.top - h - space;
			break;
		case Pos_TopRight:
			x = r.right - w + 1;
			y = r.top - h - space;
			break;

		case Pos_BottomLeft:
			x = r.left;
			y = r.bottom + space;
			break;
		case Pos_Bottom:
			x = (r.left + r.right - w) / 2;
			y = r.bottom + space;
			break;
		case Pos_BottomRight:
			x = r.right - w + 1;
			y = r.bottom + space;
			break;

		case Pos_LeftTop:
			x = r.left - w - space;
			y = r.top;
			break;
		case Pos_Left:
			x = r.left - w - space;
			y = (r.top + r.bottom - h) / 2;
			break;
		case Pos_LeftBottom:
			x = r.left - w - space;
			y = r.bottom - h;
			break;

		case Pos_RightTop:
			x = r.right + space;
			y = r.top;
			break;
		case Pos_Right:
			x = r.right + space;
			y = (r.top + r.bottom - h) / 2;
			break;
		case Pos_RightBottom:
			x = r.right + space;
			y = r.bottom + h;
			break;
		}


	}
	MoveWindow(ctrl->hWnd, x, y, w, h, true);
	if (ctrl->Type == Control_Combobox) {
		SendMessageW(ctrl->hWnd, CB_SETITEMHEIGHT, -1, h);
	}

	return 0;
}

static int l_control_SetEnable(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	bool state = lua_toboolean(L, 2);
	EnableWindow(ctrl->hWnd, state);
	return 0;
}

static int l_control_GetEnable(lua_State* L) {
	sControl* ctrl = checkControl(L, 1);
	lua_pushboolean(L, IsWindowEnabled(ctrl->hWnd));
	return 1;
}

static int l_control_SetBackground(lua_State* L) {
	if (luaL_testudata(L, 1, ID_Window) != NULL) {
		SDL_Window* sdlwin = checkWindow(L, 1);
		HWND hWnd = GetHWND(sdlwin);
		SetWndProcHook(hWnd, sdlwin);

		sWinUserData* ud = (sWinUserData*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
		if (ud == NULL) {
			return 0;
		}

		if (ud->background != NULL) {
			DeleteObject(ud->background);
			ud->background = NULL;
		}
		if (!lua_isnone(L, 2)) {
			int r = (int)checkroundnumber(L, 2);
			int g = (int)checkroundnumber(L, 3);
			int b = (int)checkroundnumber(L, 4);
			ud->background = CreateSolidBrush(RGB(r, g, b));
		}
		return 0;
	}

	sControl* ctrl = checkControl(L, 1);

	sControlUserData* ud = (sControlUserData*)GetWindowLongPtrW(ctrl->hWnd, GWLP_USERDATA);
	if (ud == NULL) {
		return 0;
	}

	if (ud->background != NULL) {
		DeleteObject(ud->background);
		ud->background = NULL;
	}
	if (!lua_isnone(L, 2)) {
		int r = (int)checkroundnumber(L, 2);
		int g = (int)checkroundnumber(L, 3);
		int b = (int)checkroundnumber(L, 4);
		ud->background = CreateSolidBrush(RGB(r, g, b));
	}
	return 0;
}