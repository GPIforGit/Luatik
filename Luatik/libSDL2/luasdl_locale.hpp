#pragma once

static int l_locale_GetPreferred(lua_State* L) {
	SDL_Locale* loc = SDL_GetPreferredLocales();
	if (loc == NULL) {
		lua_pushnil(L);
		return 1;
	}

	lua_newtable(L);
	int i = 1;
	for (SDL_Locale* cLoc = loc; cLoc->country != NULL; cLoc++) {
		//printf("%s %s\n", cLoc->language, cLoc->language);
		lua_createtable(L, 0, 2);
		luaEXT_rawsetstring(L, -1, "language", cLoc->language);
		luaEXT_rawsetstring(L, -1, "country", cLoc->country);
		lua_rawseti(L, -2, i++);		
	}

	SDL_free(loc);
	return 1;
}

