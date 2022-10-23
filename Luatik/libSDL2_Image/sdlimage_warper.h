#pragma once

#define SDLIMAGEWARP_VERSION "0.1"
#define SDLIMAGE_LICENSE "(C) Sam Lantinga"

#include "../lua/lua.hpp"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static

#define SDL_MAIN_HANDLED
#include "../sdl2/SDL.h"
#include "../sdl2/SDL_image.h"




