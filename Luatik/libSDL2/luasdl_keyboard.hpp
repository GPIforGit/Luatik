#pragma once

static int l_Keyboard_Reset(lua_State* L) {
	SDL_ResetKeyboard();
	return 0;
}

static int l_Keyboard_GetFocus(lua_State* L) {
	pushWindow(L, SDL_GetKeyboardFocus());
	return 1;
}

static int l_Keyboard_GetState(lua_State* L) {
	int numkeys;
	const Uint8* state = SDL_GetKeyboardState(&numkeys);
	SDL_Scancode key = checkScancode(L, 1);
	if (key >= numkeys || key < 0) {
		lua_pushnil(L);
	}
	else {
		lua_pushboolean(L, state[key]);
	}
	return 1;
}

static int l_Keyboard_GetScancodeValue(lua_State* L) {
	SDL_Scancode scan = checkScancode(L, 1);
	lua_pushinteger(L, scan);
	return 1;
}

static int l_Keyboard_GetKeyValue(lua_State* L) {
	SDL_Keycode key = checkKeyCode(L, 1);
	lua_pushinteger(L, key);
	return 1;
}

static int l_Keyboard_GetModState(lua_State* L) {
	pushKeymod(L, SDL_GetModState());
	return 1;
}

static int l_Keyboard_SetModState(lua_State* L) {
	SDL_Keymod mod = checkKeymod(L, 1);
	SDL_SetModState(mod);
	return 0;
}

static int l_Keyboard_GetKeyFromScancode(lua_State* L) {
	SDL_Scancode scan = checkScancode(L, 1);
	pushKeyCode(L, SDL_GetKeyFromScancode(scan));
	return 1;
}

static int l_Keyboard_GetScancodeFromKey(lua_State* L) {
	SDL_Keycode key = checkKeyCode(L, 1);
	pushScancode(L, SDL_GetScancodeFromKey(key));
	return 1;
}

static int l_Keyboard_GetScancodeName(lua_State* L) {
	SDL_Scancode scan = checkScancode(L, 1);
	lua_pushstring(L, SDL_GetScancodeName(scan));
	return 1;
}

static int l_Keyboard_GetScancodeFromName(lua_State* L) {
	const char* scan = luaL_checkstring(L, 1);
	pushScancode(L, SDL_GetScancodeFromName(scan));
	return 1;
}

static int l_Keyboard_GetKeyName(lua_State* L) {
	SDL_Keycode key = checkKeyCode(L, 1);
	lua_pushstring(L, SDL_GetKeyName(key));
	return 1;
}

static int l_Keyboard_GetKeyFromName(lua_State* L) {
	const char* key = luaL_checkstring(L, 1);
	pushKeyCode(L, SDL_GetKeyFromName(key));
	return 1;
}

static int l_Keyboard_HasScreenKeyboardSupport(lua_State* L) {
	lua_pushboolean(L, SDL_HasScreenKeyboardSupport());
	return 1;
}

static int l_Keyboard_IsScreenKeyboardShown(lua_State* L) {
	SDL_Window* win = checkWindow(L, 1);
	lua_pushboolean(L, SDL_IsScreenKeyboardShown(win));
	return 1;
}

static int l_TextInput_Start(lua_State* L) {
	SDL_StartTextInput();
	return 0;
}

static int l_TextInput_IsActive(lua_State* L) {
	lua_pushboolean(L, SDL_IsTextInputActive());
	return 1;
}

static int l_TextInput_Stop(lua_State* L) {
	SDL_StopTextInput();
	return 0;
}

static int l_TextInput_SetRect(lua_State* L) {
	SDL_Rect r;
	SDL_SetTextInputRect(toRect(L, 1, &r));
	return 0;
}


