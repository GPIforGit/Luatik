#pragma once

const struct luaEXT_constpair flag_RequesterMessageFlags[] = {
	{"OK", MB_OK},
	{"OKCANCEL", MB_OKCANCEL},
	{"RETRYCANCEL",  MB_RETRYCANCEL},
	{"YESNO", MB_YESNO},
	{"YESNOCANCEL", MB_YESNOCANCEL},
	{"ABORTRETRYIGNORE", MB_ABORTRETRYIGNORE},
	{"CANCELTRYCONTINUE", MB_CANCELTRYCONTINUE},

	{"WARNING", MB_ICONWARNING},
	{"INFORMATION", MB_ICONINFORMATION},
	{"QUESTION", MB_ICONQUESTION},
	{"STOP", MB_ICONSTOP},

	{"DEFAULT1", MB_DEFBUTTON1},
	{"DEFAULT2", MB_DEFBUTTON2},
	{"DEFAULT3", MB_DEFBUTTON3},
	{"DEFAULT4", MB_DEFBUTTON4},
	{NULL, NULL}
};
inline DWORD checkRequesterMessageFlags(lua_State* L, int index) {
	if (lua_isnoneornil(L, index)) {
		return 0;
	}
	return (DWORD)luaEXT_checkflags(L, index, flag_RequesterMessageFlags);
}

const struct luaEXT_constpair flag_RequesterMessageAnswerFlags[] = {
	{"ABORT", IDABORT},
	{"CANCEL", IDCANCEL},
	{"CONTINUE", IDCONTINUE},
	{"IGNORE", IDIGNORE},
	{"NO", IDNO},
	{"YES", IDYES},
	{"OK", IDOK},
	{"RETRY", IDRETRY},
	{"TRY", IDTRYAGAIN},
	{NULL, NULL}
};
inline void pushRequesterMessageAnswerFlag(lua_State* L, int value) {
	luaEXT_pushflag(L, value, flag_RequesterMessageAnswerFlags);
}

const struct luaEXT_constpair flag_RequesterFileFlags[] = {
	{"MUSTEXIST", OFN_FILEMUSTEXIST},
	{"CREATEPROMT", OFN_CREATEPROMPT},
	{"OVERWRITEPROMT", OFN_OVERWRITEPROMPT},
	{NULL,NULL}
};
inline DWORD checkRequesterFileFlags(lua_State* L, int index) {
	if (lua_isnoneornil(L, index)) {
		return 0;
	}
	return (DWORD)luaEXT_checkflags(L, index, flag_RequesterFileFlags);
}
