#pragma once


static int l_Requester_File(lua_State* L, bool isOpen) {
	SDL_Window* swin = checkWindowOrNil(L, 1);
	std::wstring title = luaEXT_checkwstring(L, 2);
	std::wstring defFile = luaEXT_checkwstring(L, 3);
	std::wstring Filter = luaEXT_checkwstring(L, 4);
	DWORD FilterIndex = (DWORD)luaL_optinteger(L, 5, 1);
	DWORD flags = checkRequesterFileFlags(L, 6);

	Filter += L"||";
	{
		auto first = Filter.begin();
		auto last = Filter.end();
		for (; first != last; ++first) {
			if (*first == L'|') {
				*first = 0;
			}
		}
	}



	const size_t nMaxFile = 1024;
	wchar_t* retFile = (wchar_t*)SDL_calloc(nMaxFile+1, sizeof(wchar_t));

	memcpy(retFile, defFile.c_str(), (defFile.length()) * sizeof(wchar_t) );
	retFile[defFile.length()] = 0;

	OPENFILENAMEW  dialog;
	dialog.lStructSize = sizeof(dialog);
	dialog.hwndOwner = GetHWND(swin);
	dialog.lpstrFilter = Filter.c_str();
	dialog.lpstrCustomFilter = NULL;
	dialog.nFilterIndex = FilterIndex;
	dialog.lpstrFile = retFile;
	dialog.nMaxFile = nMaxFile;
	dialog.lpstrFileTitle = NULL;
	dialog.lpstrInitialDir = NULL;
	dialog.lpstrTitle = title.c_str();
	dialog.Flags = flags | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
	dialog.lpstrDefExt = NULL;
	dialog.FlagsEx = NULL;


	bool result = isOpen ? GetOpenFileNameW(&dialog) : GetSaveFileNameW(&dialog);
	
	if (result) {
		luaEXT_pushwstring(L, retFile);
		lua_pushinteger(L, dialog.nFilterIndex);
	} 
	else {
		lua_pushnil(L);
		lua_pushnil(L);
	}
	

	SDL_free(retFile);
	SDL_ResetKeyboard();

	return 2;
}

static int l_Requester_OpenFile(lua_State* L) {
	return l_Requester_File(L, true);
}

static int l_Requester_SaveFile(lua_State* L) {
	return l_Requester_File(L, false);
}

static int l_Requester_Message(lua_State* L) {
	SDL_Window* swin = checkWindowOrNil(L, 1);
	std::wstring text = luaEXT_checkwstring(L, 2);
	std::wstring title = luaEXT_checkwstring(L, 3);
	UINT type = checkRequesterMessageFlags(L, 4);
	int ret = MessageBoxW(GetHWND(swin), title.c_str(), text.c_str(), type);
	pushRequesterMessageAnswerFlag(L,ret);
	SDL_ResetKeyboard();
	return 1;
}