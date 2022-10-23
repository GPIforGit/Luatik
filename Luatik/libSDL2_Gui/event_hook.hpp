#pragma once

typedef enum {
	ud_code_control_menu,
}UD_CODE;


inline void SendEvent(SDL_Window* sdlwin, UD_CODE code, void* data1, void* data2) {
	SDL_Event e;
	e.type = gNotifyMessage;
	e.user.timestamp = SDL_GetTicks();
	e.user.windowID = SDL_GetWindowID(sdlwin);
	e.user.data1 = data1;
	e.user.data2 = data2;
	e.user.code = code;
	SDL_PushEvent(&e);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	sWinUserData* ud = (sWinUserData*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	if (ud == NULL) {
		return false;
	}
	// NO LUA CODE HERE!!!
	
	switch (msg) {
	case WM_SYSKEYDOWN: //--
	case WM_SYSKEYUP: //--
	case WM_SYSCOMMAND: //--
		DefWindowProc(hWnd, msg, wParam, lParam);
		// and run the sdl-thing
		break;

	case WM_SYSDEADCHAR:
	case WM_SYSCHAR:
	case WM_ENTERMENULOOP:
	case WM_EXITMENULOOP:
	case WM_GETTITLEBARINFOEX:
	case WM_MENUCOMMAND:
	case WM_MENUDRAG:
	case WM_MENUGETOBJECT:
	case WM_MENURBUTTONUP:
	case WM_NEXTMENU:
	case WM_UNINITMENUPOPUP:

		//printf("syskey\n");
		return DefWindowProc( hWnd, msg, wParam, lParam);
		break;

	case WM_NOTIFY:
	{
		break;
	}

	case WM_COMMAND:
	{
		int type = HIWORD(wParam);
		//printf("WM_COMMAND: w:%llx l:%llx lo:%x hi:%x\n", wParam, lParam, LOWORD(wParam),HIWORD(wParam));
		if (lParam == NULL && type == NULL) {
			SendEvent(ud->sdlwin, ud_code_control_menu, (void*)LOWORD(wParam), NULL);
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		break;
	}

	case WM_DESTROY:
	{
		//reset wndproc and userdata
		WNDPROC proc = ud->proc;
		if (ud->background != NULL) {
			DeleteObject(ud->background);
			ud->background = NULL;
		}
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, NULL);
		SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)proc);
		SDL_free((void*)ud);
		return CallWindowProc(proc, hWnd, msg, wParam, lParam);
	}

	} // switch end


	return CallWindowProc(ud->proc, hWnd, msg, wParam, lParam);
}


static void SetWndProcHook(HWND hWnd, SDL_Window* sdlwin) {
	if (GetWindowLongPtrW(hWnd, GWLP_USERDATA) == NULL) {
		sWinUserData* ud = (sWinUserData*)SDL_calloc(1, sizeof(sWinUserData));
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)ud);
		ud->sdlwin = sdlwin;
		ud->proc = (WNDPROC)SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
		ud->background = NULL;	
	}
}

static int l_hook_event(lua_State* L) {
	SDL_Event* e = (SDL_Event*)lua_touserdata(L, 1);

	static lua_Integer HotElementID = 0;
	static int HotWindowID = 0;
	static lua_Integer clickElementID = 0;
	static int clickWindowID = 0;

	// USERMESSAGE
	if (e->type == gNotifyMessage) {
		 if (e->user.code == ud_code_control_menu) {
			lua_newtable(L);
			luaEXT_rawsetstring(L, -1, "type", "MENU");
			luaEXT_rawsetinteger(L, -1, "timestamp", e->user.timestamp);
			
			lua_pushstring(L, "window");
			pushWindow(L, SDL_GetWindowFromID(e->user.windowID));
			lua_rawset(L, -3);

			lua_pushstring(L, "id");
			pushMENUID(L,(int) e->user.data1);
			lua_rawset(L, -3);
			//luaEXT_rawsetinteger(L, -1, "id", (lua_Integer)e->user.data1);
			return 1;
		}
		
	}

	lua_pushnil(L);
	return 1;
}
/*
void WindowsMessageHook(void* userdata, void* hWnd, unsigned int message, Uint64 wParam, Sint64 lParam) {
	if (message == WM_NOTIFY) {
		printf("NOTIFY\n");
	}

}
*/

inline static void set_event_hook(lua_State* L) {
	lua_pushcfunction(L, l_hook_event);
	lua_setfield(L, LUA_REGISTRYINDEX, ID_EVENT_HOOK);
	//SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	//SDL_SetWindowsMessageHook(WindowsMessageHook, NULL);
}

inline static void remove_event_hook(lua_State* L) {
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, ID_EVENT_HOOK);
	//SDL_EventState(SDL_SYSWMEVENT, SDL_DISABLE);
}
