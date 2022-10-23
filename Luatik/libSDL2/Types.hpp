#pragma once

// Types

#define ID_CACHE "SDL.cache"
#define ID_EVENT_HOOK "SDL.event_hook"

void debugoutput(lua_State* L, const char* msg, const char* type, void* pointer) {
	lua_Debug ar;

	printf("%s %s:%p in ", msg, type, pointer);

	if (lua_getstack(L, 1, &ar)) {
		lua_getinfo(L, "Slnt", &ar);

		if (ar.currentline <= 0) {
			printf("%s ", ar.short_src);
		}
		else {
			printf("%s : %d ", ar.short_src, ar.currentline);
		}
		if (*ar.namewhat != '\0') {
			printf("%s %s ", ar.namewhat, ar.name);
		}
		printf("(%d)", ar.linedefined);
	}
	else {
		printf("<unknown>");
	}
	printf("\n");
}

static void pushcachedudata(lua_State* L, void* value, const char* type) {
	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE);

	lua_pushfstring(L, "%s:%p", type, value);
	lua_pushvalue(L, -1);
	lua_rawget(L, -3);

	// -3 _cache
	// -2 %s:%p
	// -1 nil or userdata

	if (lua_isuserdata(L, -1)) {
		lua_insert(L, -3);
		lua_pop(L, 2);
		return;
	}
	lua_pop(L, 1); // remove nil

	luaEXT_pushudata(L, (void*)value, type);
	lua_pushvalue(L, -1);
	lua_insert(L, -4);

	// -4 userdata
	// -3 cache
	// -2 %s:%p
	// -1 userdata

	lua_rawset(L, -3);
	lua_pop(L, 1);

	debugoutput(L, "[Create]", type, value);

	return;
}
static void removecachedudata(lua_State* L, void* value, const char* type) {
	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE);
	lua_pushfstring(L, "%s:%p", type, value);
	lua_pushnil(L);
	lua_rawset(L, -3);
	lua_pop(L, 1);

	debugoutput(L, "[Delete]", type, value);

}
static void initcacheudata(lua_State* L) {
	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, ID_CACHE);
	return;
}

#define ID_HWND "luatik.HWND"
inline HWND checkHWND(lua_State* L, int index) {
	return (HWND)luaEXT_checkuintegerornil(L, index, ID_HWND);
}
inline void pushHWND(lua_State* L, HWND value) {
	luaEXT_pushuinteger(L, (lua_Integer)value, ID_HWND);
}


#define ID_RWops "SDL.RWops"
inline SDL_RWops* checkRWops(lua_State* L, int index) {
	return (SDL_RWops*)luaEXT_checkudata(L, index, ID_RWops);
}
inline void pushRWops(lua_State* L, SDL_RWops* value) {
	luaEXT_pushudata(L, (void*)value, ID_RWops);
}


#define ID_TouchID "SDL.TouchID"
inline SDL_TouchID checkTouchID(lua_State* L, int index) {
	if (lua_isinteger(L, index) && lua_tointeger(L, index) == -1) {
		return (SDL_TouchID)-1;
	}
	return (SDL_TouchID)luaEXT_checkuinteger(L, index, ID_TouchID);
}
inline void pushTouchID(lua_State* L, SDL_TouchID value) {
	pushcachedudata(L, (void*)value, ID_TouchID);
}
inline void removeTouchID(lua_State* L, SDL_TouchID value) {
	removecachedudata(L, (void*)value, ID_TouchID);
}

#define ID_GameController "SDL.GameController"
inline SDL_GameController* checkGameController(lua_State* L, int index) {
	return (SDL_GameController*)luaEXT_checkudata(L, index, ID_GameController);
}
inline void pushGameController(lua_State* L, const SDL_GameController* value) {
	pushcachedudata(L, (void*)value, ID_GameController);
}
inline void removeGameController(lua_State* L, const SDL_GameController* value) {
	removecachedudata(L, (void*)value, ID_GameController);
}


inline bool isType(lua_State* L, int index, const char* id) {
	return luaL_testudata(L, index, id) != NULL;
}

#define ID_Sensor "SDL.Sensor"
inline SDL_Sensor* checkSensor(lua_State* L, int index) {
	return (SDL_Sensor*)luaEXT_checkudata(L, index, ID_Sensor);
}
inline void pushSensor(lua_State* L, SDL_Sensor* value) {
	pushcachedudata(L, value, ID_Sensor);
}
inline void removeSensor(lua_State* L, SDL_Sensor* value) {
	removecachedudata(L, value, ID_Sensor);
}

#define ID_Joystick "SDL.Joystick"
inline SDL_Joystick* checkJoystick(lua_State* L, int index) {
	return (SDL_Joystick*)luaEXT_checkudata(L, index, ID_Joystick);
}
inline void pushJoystick(lua_State* L, const SDL_Joystick* value) {
	pushcachedudata(L, (void*)value, ID_Joystick);
}
inline void removeJoystick(lua_State* L, const SDL_Joystick* value) {
	removecachedudata(L, (void*)value, ID_Joystick);
}


inline SDL_JoystickGUID checkJoystickGUID(lua_State* L, int index) {
	const char* str = luaL_checkstring(L, index);
	return  SDL_JoystickGetGUIDFromString(str);
}
inline void pushJoystickGUID(lua_State* L, SDL_JoystickGUID* value) {
	char str[34] = {};
	SDL_JoystickGetGUIDString(*value, str, 34);
	lua_pushstring(L, str);
}

#define ID_Cursor "SDL.Cursor"//
inline SDL_Cursor* checkCursor(lua_State* L, int index) {
	return (SDL_Cursor*)luaEXT_checkudata(L, index, ID_Cursor);
}
inline SDL_Cursor* checkCursorOrNil(lua_State* L, int index) {
	return (SDL_Cursor*)luaEXT_checkudataornil(L, index, ID_Cursor);
}
inline void pushCursor(lua_State* L, SDL_Cursor* value) {
	luaEXT_pushudata(L, value, ID_Cursor);
}

#define ID_Renderer "SDL.Renderer"//
inline SDL_Renderer* checkRenderer(lua_State* L, int index) {
	return (SDL_Renderer*)luaEXT_checkudata(L, index, ID_Renderer);
}
inline void pushRenderer(lua_State* L, SDL_Renderer* ren) {
	luaEXT_pushudata(L, (void*)ren, ID_Renderer);
}

#define ID_Texture "SDL.Texture"//
inline SDL_Texture* checkTexture(lua_State* L, int index) {
	return (SDL_Texture*)luaEXT_checkudata(L, index, ID_Texture);
}
inline SDL_Texture* checkTextureOrNil(lua_State* L, int index) {
	return (SDL_Texture*)luaEXT_checkudataornil(L, index, ID_Texture);
}
inline void pushTexture(lua_State* L, SDL_Texture* tex) {
	luaEXT_pushudata(L, (void*)tex, ID_Texture);
}

#define ID_Window "SDL.Window"//
inline SDL_Window* checkWindow(lua_State* L, int index) {
	return (SDL_Window*)luaEXT_checkudata(L, index, ID_Window);
}
inline SDL_Window* checkWindowOrNil(lua_State* L, int index) {
	return (SDL_Window*)luaEXT_checkudataornil(L, index, ID_Window);
}
inline void pushWindow(lua_State* L, SDL_Window* win) {
	pushcachedudata(L, (void*)win, ID_Window);
}
inline void removeWindow(lua_State* L, SDL_Window* win) {
	removecachedudata(L, (void*)win, ID_Window);
}


#define ID_Surface "SDL.Surface"//
inline SDL_Surface* checkSurface(lua_State* L, int index) {
	return (SDL_Surface*)luaEXT_checkudata(L, index, ID_Surface);
}
inline SDL_Surface* checkSurfaceOrNil(lua_State* L, int index) {
	return (SDL_Surface*)luaEXT_checkudataornil(L, index, ID_Surface);
}
inline void pushSurface(lua_State* L, SDL_Surface* sur) {
	luaEXT_pushudata(L, (void*)sur, ID_Surface);
}

#define ID_PixelFormat "SDL.PixelFormat"//
inline SDL_PixelFormat* checkPixelFormat(lua_State* L, int index) {
	return (SDL_PixelFormat*)luaEXT_checkudata(L, index, ID_PixelFormat);
}
inline void pushPixelFormat(lua_State* L, SDL_PixelFormat* pf) {
	luaEXT_pushudata(L, (void*)pf, ID_PixelFormat);
}

#define ID_Void "SDL.Void"
inline void* checkVoid(lua_State* L, int index) {
	return (void*)luaEXT_checkudata(L, index, ID_Void);
}
inline void pushVoid(lua_State* L, void* pf) {
	luaEXT_pushudata(L, (void*)pf, ID_Void);
}

// Structs 

static void pushRenderInfo(lua_State* L, SDL_RendererInfo* rinfo) {
	lua_createtable(L, 0, 6);
	luaEXT_rawsetstring(L, -1, "name", rinfo->name);
	luaEXT_rawsetflags(L, -1, "flags", rinfo->flags, flag_RendererFlags, true);

	lua_pushstring(L, "texture_formats");
	lua_createtable(L, rinfo->num_texture_formats, 0);
	for (Uint32 i = 0; i < rinfo->num_texture_formats; i++) {
		pushPixelFormatEnum(L, (SDL_PixelFormatEnum)rinfo->texture_formats[i]);
		lua_rawseti(L, -2, (lua_Integer)i + 1);
	};
	lua_rawset(L, -3);

	luaEXT_rawsetinteger(L, -1, "max_texture_width", rinfo->max_texture_width);
	luaEXT_rawsetinteger(L, -1, "max_texture_height", rinfo->max_texture_height);
}

void pushDisplayMode(lua_State* L, SDL_DisplayMode* dm) {
	lua_createtable(L, 0, 4);
	lua_pushstring(L, "format");
	pushPixelFormatEnum(L, (SDL_PixelFormatEnum)dm->format);
	lua_rawset(L, -3);
	luaEXT_rawsetinteger(L, -1, "w", dm->w);
	luaEXT_rawsetinteger(L, -1, "h", dm->h);
	luaEXT_rawsetinteger(L, -1, "refresh_rate", dm->refresh_rate);
	//luaEXT_rawsetudata(L, -1, "driverdata", dm.driverdata);
}

SDL_Point* toPoint(lua_State* L, int index, SDL_Point* p) {
	if (lua_type(L, index) != LUA_TTABLE) {
		return NULL;
	}
	p->x = (int)getKeyIndexInteger(L, index, "x", 1);
	p->y = (int)getKeyIndexInteger(L, index, "y", 2);
	return p;
}
void pushPoint(lua_State* L, const SDL_Point* p) {
	lua_createtable(L, 0, 2);
	luaEXT_rawsetinteger(L, -1, "x", p->x);
	luaEXT_rawsetinteger(L, -1, "y", p->y);
}
SDL_FPoint* toFPoint(lua_State* L, int index, SDL_FPoint* p) {
	if (lua_type(L, index) != LUA_TTABLE) {
		return NULL;
	}
	p->x = (float)getKeyIndexNumber(L, index, "x", 1);
	p->y = (float)getKeyIndexNumber(L, index, "y", 2);
	return p;
}
void pushFPoint(lua_State* L, const  SDL_FPoint* p) {
	lua_createtable(L, 0, 2);
	luaEXT_rawsetnumber(L, -1, "x", p->x);
	luaEXT_rawsetnumber(L, -1, "y", p->y);
}

#define ID_Rect "SDL.Rect"
SDL_Rect* toRect(lua_State* L, int index, SDL_Rect* r) {
	if (lua_type(L, index) != LUA_TTABLE) {
		return NULL;
	}
	r->x = (int)getKeyIndexNumber(L, index, "x", 1);
	r->y = (int)getKeyIndexNumber(L, index, "y", 2);
	r->w = (int)getKeyIndexNumber(L, index, "w", 3);
	r->h = (int)getKeyIndexNumber(L, index, "h", 4);
	return r;
}
void pushRect(lua_State* L, const SDL_Rect* p) {
	lua_createtable(L, 0, 4);
	luaEXT_rawsetinteger(L, -1, "x", p->x);
	luaEXT_rawsetinteger(L, -1, "y", p->y);
	luaEXT_rawsetinteger(L, -1, "w", p->w);
	luaEXT_rawsetinteger(L, -1, "h", p->h);
	luaL_getmetatable(L, ID_Rect);
	lua_setmetatable(L, -2);
}
SDL_FRect* toFRect(lua_State* L, int index, SDL_FRect* r) {
	if (lua_type(L, index) != LUA_TTABLE) {
		return NULL;
	}
	r->x = (float)getKeyIndexNumber(L, index, "x", 1);
	r->y = (float)getKeyIndexNumber(L, index, "y", 2);
	r->w = (float)getKeyIndexNumber(L, index, "w", 3);
	r->h = (float)getKeyIndexNumber(L, index, "h", 4);
	return r;
}
void pushFRect(lua_State* L, const SDL_FRect* p) {
	lua_createtable(L, 0, 4);
	luaEXT_rawsetnumber(L, -1, "x", p->x);
	luaEXT_rawsetnumber(L, -1, "y", p->y);
	luaEXT_rawsetnumber(L, -1, "w", p->w);
	luaEXT_rawsetnumber(L, -1, "h", p->h);
}

void pushColor(lua_State* L, SDL_Color* col) {
	lua_createtable(L, 0, 4);
	luaEXT_rawsetinteger(L, -1, "r", col->r);
	luaEXT_rawsetinteger(L, -1, "g", col->g);
	luaEXT_rawsetinteger(L, -1, "b", col->b);
	luaEXT_rawsetinteger(L, -1, "a", col->a);
}
SDL_Color* toColor(lua_State* L, int index, SDL_Color* ret) {
	if (lua_type(L, index) != LUA_TTABLE) {
		return NULL;
	}
	ret->r = (Uint8)getKeyIndexInteger(L, index, "r", 1);
	ret->g = (Uint8)getKeyIndexInteger(L, index, "g", 2);
	ret->b = (Uint8)getKeyIndexInteger(L, index, "b", 3);
	ret->a = (Uint8)getKeyIndexInteger(L, index, "a", 4);
	return ret;
}

// Array

static SDL_Vertex* arrayVertex(lua_State* L, int index, int* count) {
	if (lua_isnil(L, index)) {
		*count = 0;
		return NULL;
	}
	lua_len(L, index);
	*count = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	SDL_Vertex* ret = (SDL_Vertex*)SDL_calloc(*count, sizeof(SDL_Vertex));
	if (ret == NULL) {
		return NULL;
	}

	SDL_Vertex* v = ret;
	for (int i = 1; i <= *count; i++, v++) {
		lua_geti(L, index, i);

		lua_getfield(L, -1, "position");
		toFPoint(L, -1, &(v->position));

		lua_getfield(L, -2, "color");
		toColor(L, -1, &(v->color));

		lua_getfield(L, -3, "tex_coord");
		toFPoint(L, -1, &(v->tex_coord));

		lua_pop(L, 4);
	};

	return ret;
}
static SDL_Point* arrayPoint(lua_State* L, int index, int* count) {
	if (lua_isnoneornil(L, index)) {
		*count = 0;
		return NULL;
	}
	lua_len(L, index);
	*count = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	SDL_Point* ret = (SDL_Point*)SDL_calloc(*count, sizeof(SDL_Point));
	if (ret == NULL) {
		return NULL;
	}

	SDL_Point* v = ret;
	for (int i = 1; i <= *count; i++, v++) {
		lua_geti(L, index, i);
		toPoint(L, -1, v);
		lua_pop(L, 1);
	};

	return ret;
}
static SDL_FPoint* arrayFPoint(lua_State* L, int index, int* count) {
	if (lua_isnoneornil(L, index)) {
		*count = 0;
		return NULL;
	}
	lua_len(L, index);
	*count = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	SDL_FPoint* ret = (SDL_FPoint*)SDL_calloc(*count, sizeof(SDL_FPoint));
	if (ret == NULL) {
		return NULL;
	}

	SDL_FPoint* v = ret;
	for (int i = 1; i <= *count; i++, v++) {
		lua_geti(L, index, i);
		toFPoint(L, -1, v);
		lua_pop(L, 1);
	};

	return ret;
}
static SDL_Rect* arrayRect(lua_State* L, int index, int* count) {
	if (lua_isnoneornil(L, index)) {
		*count = 0;
		return NULL;
	}
	lua_len(L, index);
	*count = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	SDL_Rect* ret = (SDL_Rect*)SDL_calloc(*count, sizeof(SDL_Rect));
	if (ret == NULL) {
		return NULL;
	}

	SDL_Rect* v = ret;
	for (int i = 1; i <= *count; i++, v++) {
		lua_geti(L, index, i);
		toRect(L, -1, v);
		lua_pop(L, 1);
	};

	return ret;
}
static SDL_FRect* arrayFRect(lua_State* L, int index, int* count) {
	if (lua_isnoneornil(L, index)) {
		*count = 0;
		return NULL;
	}
	lua_len(L, index);
	*count = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	SDL_FRect* ret = (SDL_FRect*)SDL_calloc(*count, sizeof(SDL_FRect));
	if (ret == NULL) {
		return NULL;
	}

	SDL_FRect* v = ret;
	for (int i = 1; i <= *count; i++, v++) {
		lua_geti(L, index, i);
		toFRect(L, -1, v);
		lua_pop(L, 1);
	};

	return ret;
}
static int* arrayInt(lua_State* L, int index, int* count, int offset) {
	if (lua_isnoneornil(L, index)) {
		*count = 0;
		return NULL;
	}
	lua_len(L, index);
	*count = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	int* ret = (int*)SDL_calloc(*count, sizeof(SDL_FRect));
	if (ret == NULL) {
		return NULL;
	}

	int* v = ret;
	for (int i = 1; i <= *count; i++, v++) {
		lua_geti(L, index, i);
		*v = (int)checkroundnumber(L, -1) + offset;
		lua_pop(L, 1);
	};

	return ret;
}

#define FreeArray(a) SDL_free((void*)(a))

// new structure/table

static int l_POINT(lua_State* L) {
	SDL_FPoint p = {
		(float)checkroundnumber(L,1),
		(float)checkroundnumber(L,2)
	};
	pushFPoint(L, &p);
	return 1;
}
static int l_RECT(lua_State* L) {
	SDL_FRect r = {
		(float)checkroundnumber(L,1),
		(float)checkroundnumber(L,2),
		(float)checkroundnumber(L,3),
		(float)checkroundnumber(L,4)
	};
	pushFRect(L, &r);
	luaL_getmetatable(L, ID_Rect);
	lua_setmetatable(L, -2);
	return 1;
}
static int l_VERTEX(lua_State* L) {
	SDL_Vertex f;
	f.position.x = (float)luaL_checknumber(L, 1);
	f.position.y = (float)luaL_checknumber(L, 2);
	f.color.r = (Uint8)luaL_checkinteger(L, 3);
	f.color.g = (Uint8)luaL_checkinteger(L, 4);
	f.color.b = (Uint8)luaL_checkinteger(L, 5);
	f.color.a = (Uint8)luaL_checkinteger(L, 6);
	f.tex_coord.x = (float)luaL_optnumber(L, 7, 0.0);
	f.tex_coord.y = (float)luaL_optnumber(L, 8, 0.0);
	lua_createtable(L, 0, 3);
	lua_pushstring(L, "position");
	pushFPoint(L, &f.position);
	lua_rawset(L, -3);
	lua_pushstring(L, "color");
	pushColor(L, &f.color);
	lua_rawset(L, -3);
	lua_pushstring(L, "tex_coord");
	pushFPoint(L, &f.tex_coord);
	lua_rawset(L, -3);
	return 1;
}
static int l_COLOR(lua_State* L) {
	SDL_Color c = {
		(Uint8)luaL_checkinteger(L, 1),
		(Uint8)luaL_checkinteger(L, 2),
		(Uint8)luaL_checkinteger(L, 3),
		(Uint8)luaL_optinteger(L, 4,255)
	};
	pushColor(L, &c);
	return 1;
}

