#pragma once


//const char* fields_colorScheme[] = { "BACKGROUND","TEXT", "BUTTON_BORDER", "BUTTON_BACKGROUND","BUTTON_SELECTED" };

static int l_MessageBox_Show(lua_State* L) {
	SDL_MessageBoxData mbd;
	
	// strings (keep on stack!)
	lua_getfield(L, 1, "title");
	mbd.title = lua_tostring(L, -1);
	lua_getfield(L, 1, "message");
	mbd.message = lua_tostring(L, -1);

	//flags
	lua_getfield(L, 1, "flags");
	mbd.flags = checkMessageBoxFlags(L, -1);
	
	lua_getfield(L, 1, "window");
	mbd.window = checkWindowOrNil(L, -1);
	lua_pop(L, 2);

	// scan buttons
	lua_getfield(L, 1, "buttons");
	lua_len(L, -1);
	mbd.numbuttons =(int) lua_tointeger(L, -1);
	lua_pop(L, 1);

	SDL_MessageBoxButtonData* cmbbd = (SDL_MessageBoxButtonData*)SDL_calloc(mbd.numbuttons, sizeof(SDL_MessageBoxButtonData));
	mbd.buttons = cmbbd;
	
	for (int i = 1; i <= mbd.numbuttons; i++, cmbbd++) {
		lua_geti(L, - i, i); // every button leaves a string on the stack!

		lua_getfield(L, -1, "flags");
		cmbbd->flags = checkMessageBoxButtonFlags(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "buttonid");
		cmbbd->buttonid = (Uint32)lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "text");
		cmbbd->text = lua_tostring(L, -1); // don't remove from stack!

		//remove table
		lua_remove(L, -2);
	};
	lua_remove(L, -1 - mbd.numbuttons); // remove buttons-table

	/* not supported on windows - so ignore it!
	// colorScheme
	SDL_MessageBoxColorScheme mbcs;
	lua_getfield(L, 1, "colorScheme");
	if (!lua_isnil(L, -1)) {
		mbd.colorScheme = &mbcs;
		for (int i = 0; i < SDL_MESSAGEBOX_COLOR_MAX; i++) {
			lua_getfield(L, -1, fields_colorScheme[i]);
			lua_getfield(L, -1, "r");
			mbcs.colors[i].r = (Uint8)lua_tointeger(L, -1);
			lua_getfield(L, -2, "g");
			mbcs.colors[i].g = (Uint8)lua_tointeger(L, -1);
			lua_getfield(L, -3, "b");
			mbcs.colors[i].b = (Uint8)lua_tointeger(L, -1);
			lua_pop(L, 4);

			printf(" color %d %s : %d %d %d\n", i, fields_colorScheme[i], mbcs.colors[i].r, mbcs.colors[i].g, mbcs.colors[i].b);

		}
	} else {
		mbd.colorScheme = NULL;
	}
	*/
	mbd.colorScheme = NULL;

	int ret;
	if (SDL_ShowMessageBox(&mbd, &ret) == 0) {
		lua_pushinteger(L, ret);
	}
	else {
		lua_pushnil(L);
	}

	SDL_free((void*)mbd.buttons);
	return 1;
}

static int l_MessageBox_ShowSimple(lua_State* L) {
	Uint32 flags = checkMessageBoxFlags(L, 1);
	const char* title = luaL_checkstring(L, 2);
	const char* msg = luaL_checkstring(L, 3);
	SDL_Window* win = checkWindowOrNil(L, 4);
	lua_pushboolean(L, SDL_ShowSimpleMessageBox(flags, title, msg, win) == 0);
	return 1;
}

