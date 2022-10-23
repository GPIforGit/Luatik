#pragma once


static int l_Rect_ContainsPoint(lua_State* L) {
	SDL_Rect r;
	SDL_Point p;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TTABLE);

	lua_pushboolean(L, SDL_PointInRect(toPoint(L, 2, &p), toRect(L, 1, &r)));
	return 1;
}

static int l_Rect_Empty(lua_State* L) {
	SDL_Rect r;
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_pushboolean(L, SDL_RectEmpty(toRect(L,1,&r)));
	return 1;
}

static int l_Rect_Equals(lua_State* L) {
	SDL_Rect r1, r2;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TTABLE);
	lua_pushboolean(L, SDL_RectEquals(toRect(L,1,&r1),toRect(L,2,& r2)));
	return 1;
}

static int l_Rect_Intersection(lua_State* L) {
	SDL_Rect ret;
	SDL_Rect r1, r2;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TTABLE);
	if (SDL_IntersectRect(toRect(L, 1, &r1), toRect(L, 2, &r2), &ret)) {
		pushRect(L, &ret);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

static int l_Rect_Union(lua_State* L) {
	SDL_Rect ret;
	SDL_Rect r1, r2;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TTABLE);
	SDL_UnionRect(toRect(L, 1, &r1), toRect(L, 2, &r2), &ret);
	pushRect(L, &ret);
	return 1;
}

static int l_Rect_IntersectLine(lua_State* L) {
	SDL_Rect r;
	int x1 = (int)checkroundnumber(L, 2);
	int y1 = (int)checkroundnumber(L, 3);
	int x2 = (int)checkroundnumber(L, 4);
	int y2 = (int)checkroundnumber(L, 5);
	if (SDL_IntersectRectAndLine(toRect(L,1,&r), &x1, &y1, &x2, &y2)) {
		lua_pushinteger(L, x1);
		lua_pushinteger(L, y1);
		lua_pushinteger(L, x2);
		lua_pushinteger(L, y2);
	}
	else {
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
		lua_pushnil(L);
	}
	return 4;
}

static int l_Rect_EnclosePoints(lua_State* L) {
	int pcount;
	SDL_Point* points = arrayPoint(L, 1, &pcount);
	SDL_Rect clip, res;
	luaL_checktype(L, 2, LUA_TTABLE);
	if (SDL_EnclosePoints(points, pcount, toRect(L, 3, &clip), &res)) {
		pushRect(L, &res);
	}
	else {
		lua_pushnil(L);
	}
	FreeArray(points);
	return 1;
}


