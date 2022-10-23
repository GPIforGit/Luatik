/*
  SDL_image:  An example image loading library for use with SDL
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#pragma warning(disable : 26812)

// types 


#include "sdlimage_warper.h"

void debugoutput(lua_State* L, const char* msg, const char* type, void* pointer);

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

#define ID_Renderer "SDL.Renderer"//
inline SDL_Renderer* checkRenderer(lua_State* L, int index) {
	return (SDL_Renderer*)luaEXT_checkudata(L, index, ID_Renderer);
}
inline void pushRenderer(lua_State* L, SDL_Renderer* ren) {
	luaEXT_pushudata(L, (void*)ren, ID_Renderer);
}

#define ID_RWops "SDL.RWops"
inline SDL_RWops* checkRWops(lua_State* L, int index) {
	return (SDL_RWops*)luaEXT_checkudata(L, index, ID_RWops);
}
inline void pushRWops(lua_State* L, SDL_RWops* value) {
	luaEXT_pushudata(L, (void*)value, ID_RWops);
}

// flags

const struct luaEXT_constpair flag_imginit[] = {
	{"NONE", 0},
	{"JPG", IMG_INIT_JPG},
	{"PNG", IMG_INIT_PNG},
	{"TIF", IMG_INIT_TIF},
	{"WEBP", IMG_INIT_WEBP},
	{"JXL", IMG_INIT_JXL},
	{"AVIF",IMG_INIT_AVIF},
	{"EVERYTHING", IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF},

	// dummy-values - doesn't need to initalize, but 
	{ "TGA",0 },
	{ "CUR",0 },
	{ "ICO",0 },
	{ "BMP",0 },
	{ "GIF",0 },
	{ "LBM",0 },
	{ "PCX",0 },
	{ "PNM",0 },
	{ "SVG",0 },
	{ "XCF",0 },
	{ "XPM",0 },
	{ "XV",0 },
	{ "WEBP",0 },

	{NULL,NULL}
};
inline int checkImgInit(lua_State* L, int index) {
	return (int)luaEXT_checkflags(L, index, flag_imginit);
}

// funcs

static int l_Version_GetImage(lua_State* L) {
	const SDL_version* ver = IMG_Linked_Version();
	lua_pushinteger(L, ver->major);
	lua_pushinteger(L, ver->minor);
	lua_pushinteger(L, ver->patch);
	lua_pushinteger(L, SDL_VERSIONNUM((lua_Integer)ver->major, (lua_Integer)ver->minor, (lua_Integer)ver->patch));
	return 4;
}

static int l_Version_AtLeastImage(lua_State* L) {
	const SDL_version* ver = IMG_Linked_Version();
	lua_pushboolean(
		L,
		SDL_VERSIONNUM((lua_Integer)ver->major, (lua_Integer)ver->minor, (lua_Integer)ver->patch)
		>=
		SDL_VERSIONNUM(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2), luaL_checkinteger(L, 3))
	);
	return 1;
}

static int l_Image_Init(lua_State* L) {
	int flags = checkImgInit(L, 1);
	if (flags == 0) {
		lua_pushboolean(L, true);
	}
	else {
		lua_pushboolean(L, flags == IMG_Init(flags));
	}
	return 1;
}

static int l_Image_Quit(lua_State* L) {
	IMG_Quit();
	return 0;
}

static int l_surface_Load(lua_State* L) {
	SDL_Surface* sf;

	if (lua_isstring(L, 1)) {

		const char* file = luaL_checkstring(L, 1);
		const char* type = luaL_optstring(L, 2, NULL);
		if (type == NULL) {
			sf = IMG_Load(file);
		}
		else {
			sf =  IMG_LoadTyped_RW(SDL_RWFromFile(file, "rb"), 1, type);
		}

	}
	else {
		SDL_RWops* rw = checkRWops(L, 1);
		const char* type = luaL_optstring(L, 2, NULL);
		if (type == NULL) {
			sf =  IMG_Load_RW(rw, 0);
		}
		else {
			sf = IMG_LoadTyped_RW(rw, 0, type);
		}
	}
	pushSurface(L, sf);
	debugoutput(L, "[Create]", ID_Surface, sf);
	return 1;
}

static int l_render_LoadTexture(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);
	SDL_Texture* tex;
	if (lua_isstring(L, 2)) {
		const char* file = luaL_checkstring(L, 2);
		const char* type = luaL_optstring(L, 3, NULL);
		if (type == NULL) {
			tex = IMG_LoadTexture(ren, file);
		}
		else {
			tex = IMG_LoadTextureTyped_RW(ren, SDL_RWFromFile(file, "rb"), 1, type);
		}
	}
	else {
		SDL_RWops* rw = checkRWops(L, 2);
		const char* type = luaL_optstring(L, 3, NULL);
		if (type == NULL) {
			tex = IMG_LoadTexture_RW(ren, rw, 0);
		}
		else {
			tex = IMG_LoadTextureTyped_RW(ren, rw, 0, type);
		}
	}
	pushTexture(L, tex);
	debugoutput(L, "[Create]", ID_Texture, tex);
	return 1;
}

static int l_surface_SavePNG(lua_State* L) {
	SDL_Surface* sur = checkSurface(L, 1);
	if (lua_isstring(L, 2)) {
		const char* file = luaL_checkstring(L, 2);
		lua_pushboolean(L, IMG_SavePNG(sur, file) == 0);
	}
	else {
		SDL_RWops* rw = checkRWops(L, 2);
		lua_pushboolean(L, IMG_SavePNG_RW(sur, rw, 0) == 0);
	}
	return 1;
}

static int l_surface_SaveJPG(lua_State* L) {
	SDL_Surface* sur = checkSurface(L, 1);
	if (lua_isstring(L, 2)) {
		const char* file = luaL_checkstring(L, 2);
		int quality = (int)luaL_checknumber(L, 3);
		lua_pushboolean(L, IMG_SaveJPG(sur, file, quality) == 0);
	}
	else {
		SDL_RWops* rw = checkRWops(L, 2);
		int quality = (int)luaL_checknumber(L, 3);
		lua_pushboolean(L, IMG_SaveJPG_RW(sur, rw, 0, quality) == 0);
	}
	return 1;
}

// array

const struct luaL_Reg array_Version_func[] = {
	{"GetImage",l_Version_GetImage},
	{"AtLeastImage",l_Version_AtLeastImage},
	{NULL,NULL}
};

const struct luaL_Reg array_Image_func[] = {
	{"Init",l_Image_Init},
	{"Quit",l_Image_Quit},
	{NULL,NULL}
};

const struct luaL_Reg array_Surface_func[] = {
	{"Load",l_surface_Load},
	{"SaveJPG",l_surface_SaveJPG},
	{"SavePNG",l_surface_SavePNG},
	{NULL,NULL}
};

const struct luaL_Reg array_Render_func[] = {
	{"LoadTexture",l_render_LoadTexture},
	{NULL,NULL}
};

const struct luaL_Reg array_Texture_func[] = {
	{"Load",l_render_LoadTexture},
	{NULL,NULL}
};

// LIB

static const struct luaEXT_libs array_lib[] = {
	{ "Render"		, array_Render_func},
	{ "Surface"		, array_Surface_func},
	{ "Texture"		, array_Texture_func},
	{ "Version"		, array_Version_func},
	{ "Image"		, array_Image_func},
	{NULL,NULL}
};

static const struct luaEXT_libs array_meta[] = {
	{ ID_Surface		, array_Surface_func},
	{ ID_Renderer		, array_Render_func},
	{ ID_Texture		, array_Texture_func },
	{ ID_RWops			, NULL},
	{NULL, NULL}
};

// Mains

LUAMOD_API int luaopen_SDLimage(lua_State *L){
	luaEXT_newlibtable(L, array_lib, "SDL"); // append SDL, if exist

	// dummy license-string
	lua_newtable(L);
	const SDL_version* ver = IMG_Linked_Version();
	lua_pushfstring(L, "%s by GPI, SDL_image %d.%d.%d %s", SDLIMAGEWARP_VERSION, ver->major, ver->minor, ver->patch, SDLIMAGE_LICENSE);
	lua_setfield(L, -2, "_license");

	// register all metas
	for (const luaEXT_libs* cmeta = array_meta; cmeta->libname != NULL; cmeta++) {
		luaL_newmetatable(L, cmeta->libname);
		if (cmeta->libfunc != NULL) {
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "__index");
			luaL_setfuncs(L, cmeta->libfunc, 0);
		}
		lua_pop(L, 1);
	}

	return 1;
}

