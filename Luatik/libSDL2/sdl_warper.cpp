/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

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

//#include "pch.h"
#include "sdl_warper.h"


#include "flags.hpp"
#include "Types.hpp"

//ignored
//  SDL_main.h
//  SDL_stdinc.h
//  SDL_assert.h
//  SDL_atomic.h
//  SDL_audio.h
//  SDL_cpuinfo.h
//  SDL_endian.h
//  SDL_hidapi.h
//  SDL_loadso.h
//  SDL_log.h
//  SDL_metal.h
//  SDL_mutex.h
//  SDL_system.h <- WindowsMessageHook!!!
//  SDL_thread.h





#include "luasdl_hittest.hpp"

#include "luasdl_void.hpp"
#include "luasdl_init.hpp"
#include "luasdl_clipboard.hpp"
#include "luasdl_error.hpp"
#include "luasdl_event.hpp"
#include "luasdl_filesystem.hpp"
#include "luasdl_hints.hpp"
#include "luasdl_messagebox.hpp"
#include "luasdl_power.hpp"
#include "luasdl_render.hpp"
#include "luasdl_timer.hpp"
#include "luasdl_version.hpp"
#include "luasdl_video.hpp"
#include "luasdl_locale.hpp"
#include "luasdl_misc.hpp"

#include "luasdl_rect.hpp"
#include "luasdl_pixels.hpp"
#include "luasdl_blendmode.hpp"
#include "luasdl_surface.hpp"
#include "luasdl_keyboard.hpp"
#include "luasdl_mouse.hpp"
#include "luasdl_joystick.hpp"

#include "luasdl_sensor.hpp"
#include "luasdl_gamecontroller.hpp"
#include "luasdl_touch.hpp"
#include "luasdl_gesture.hpp"
#include "luasdl_rwops.hpp"


// SDL_shape.h


#include "array_funcs.hpp"

static const struct luaEXT_libs array_lib[] = {
	{ ""				, array_root_func},
	{ "BlendMode"		, array_blendmode_func},
	{ "Clipboard"		, array_Clipboard_func},
	{ "Display"			, array_Display_func},
	{ "Error"			, array_Error_func},
	{ "Event"			, array_Event_func},
	{ "Filesystem"		, array_Filesystem_func},
	{ "Hint"			, array_Hint_func},
	{ "Keyboard"		, array_Keyboard_func},
	{ "Locale"			, array_Locale_func},
	{ "MessageBox"		, array_MessageBox_array},
	{ "PixelFormat"		, array_PixelFormat_func},
	{ "Power"			, array_Power_func},
	{ "Rect"			, array_Rect_func},
	{ "Render"			, array_Render_func},
	{ "ScreenSaver"		, array_ScreenSaver_func},
	{ "Surface"			, array_Surface_func},
	{ "TextInput"		, array_TextInput_func},
	{ "Texture"			, array_Texture_func},
	{ "Time"			, array_Time_func},
	{ "Version"			, array_Version_func},
	{ "Window"			, array_Window_func},
	{ "Mouse"			, array_Mouse_func},
	{ "Cursor"			, array_Cursor_func},
	{ "Joystick"		, array_Joystick_func},
	{ "Sensor"			, array_Sensor_func},
	{ "GameController"	, array_GameController_func},
	{ "Touch"			, array_Touch_func},
	{ "RW"				, array_RW_func},
	{ "Gesture"			, array_Gesture_func},
	{NULL, NULL}
};

static const struct luaEXT_libs array_meta[] = {
	{ ID_Void			, array_Void_func},
	{ ID_Rect			, array_Rect_func},
	{ ID_TouchID		, array_Touch_func},
	{ ID_HWND			, NULL},

	{ ID_PixelFormat	, array_PixelFormat_func},
	{ ID_Surface		, array_Surface_func},
	{ ID_Window			, array_Window_func},
	{ ID_Renderer		, array_Render_func },
	{ ID_Texture		, array_Texture_func },
	{ ID_Joystick		, array_Joystick_func },
	{ ID_Cursor			, array_Cursor_func },
	{ ID_Sensor			, array_Sensor_func },
	{ ID_GameController , array_GameController_func },
	{ ID_RWops			, array_RW_func },
	
	{NULL, NULL}
};

static int l__eq(lua_State* L) {
	if (!lua_isuserdata(L, 1)) {
		luaL_error(L, "Argument %d should be a userdata", 1);
		return 0;
	}
	if (!lua_isuserdata(L, 2)) {
		luaL_error(L, "Argument %d should be a userdata", 2);
		return 0;
	}

	void* a = *((void**)lua_touserdata(L, 1));
	void* b = *((void**)lua_touserdata(L, 2));
	lua_pushboolean(L, a == b);
	return 1;
}

static int l__value(lua_State* L) {
	if (!lua_isuserdata(L, 1)) {
		luaL_error(L, "Argument %d should be a userdata", 1);
		return 0;
	}

	lua_pushinteger(L, *((lua_Integer*)lua_touserdata(L, 1)));
	return 1;
}

static int l__tostring(lua_State* L) {
	void** p = (void**)lua_touserdata(L, 1);
	if (p != NULL) {  /* value is a userdata? */
		if (lua_getmetatable(L, 1)) {  /* does it have a metatable? */
			lua_pushstring(L, "__name");
			lua_rawget(L, -2);
			const char* name = lua_tostring(L, -1);
			lua_pushfstring(L, "[%s=%p@%p]", name, *p,p);
			return 1;
		}
	}
	lua_pushnil(L);
	return 1;
}

static struct luaL_Reg array_meta_func[] = {
	{"__eq", l__eq},
	{"__tostring", l__tostring},
	{"_value", l__value},
	{NULL,NULL}
};

//extern "C" int DLL_EXPORT luaopen_SDL(lua_State * L) {
LUAMOD_API int luaopen_SDL(lua_State *L) {

	luaEXT_newlibtable(L, array_lib, ROOTLIB); // append SDL, if exist

	// add license-string
	SDL_version ver;
	SDL_GetVersion(&ver);
	lua_pushfstring(L, "%s by GPI, SDL %d.%d.%d %s", SDLWARP_VERSION, ver.major, ver.minor, ver.patch, SDL_LICENSE);
	lua_setfield(L, -2, "_license");

	// register all metas
	for (const luaEXT_libs* cmeta = array_meta; cmeta->libname != NULL; cmeta++) {
		luaL_newmetatable(L, cmeta->libname);
		lua_pushvalue(L, -1);
		lua_setfield(L, -2, "__index");
		if (cmeta->libfunc != NULL) {			
			luaL_setfuncs(L, cmeta->libfunc, 0);
		}		
		luaL_setfuncs(L, array_meta_func, 0);
		lua_pop(L, 1);
	}

	// hardcoded constant
	lua_getfield(L, -1, "Sensor");
	lua_pushnumber(L, SDL_STANDARD_GRAVITY);
	lua_setfield(L, -2, "GRAVITY");
	lua_pop(L, 1);

	return 1;
}

/*
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		SDL_SetMainReady();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

*/