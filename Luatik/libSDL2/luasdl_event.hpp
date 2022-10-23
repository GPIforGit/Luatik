#pragma once


void pushEvent(lua_State* L, SDL_Event* e) {
	
	if (e == NULL) {
		lua_newtable(L);
		return;
	}

	if (lua_getfield(L, LUA_REGISTRYINDEX, ID_EVENT_HOOK)== LUA_TFUNCTION) {
		lua_pushlightuserdata(L, (void*)e);
		lua_call(L, 1, 1);
		if (lua_istable(L, -1)) {
			return;
		}
		lua_pop(L, 1);

	}
	else {
		lua_pop(L,1);
	}

	
	lua_newtable(L);



	luaEXT_rawsetflag(L, -1, "type", e->type, flag_EventType);
	luaEXT_rawsetinteger(L, -1, "timestamp", e->common.timestamp);

	switch (e->type) {
	case SDL_DISPLAYEVENT:
		luaEXT_rawsetinteger(L, -1, "display", e->display.display);
		luaEXT_rawsetflag(L, -1, "event", e->display.event, flag_DisplayEventID);
		if (e->display.event == SDL_DISPLAYEVENT_ORIENTATION) {
			luaEXT_rawsetflag(L, -1, "orientation", e->display.data1, flag_DisplayOrientation);
		}
		break;

	case SDL_DROPBEGIN: 
	case SDL_DROPFILE: 
	case SDL_DROPTEXT: 
	case SDL_DROPCOMPLETE:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->drop.windowID));
		lua_rawset(L, -3);
		luaEXT_rawsetstring(L, -1, "file", e->drop.file);
		SDL_free(e->drop.file);
		break;

	case SDL_KEYDOWN:
	case SDL_KEYUP:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->key.windowID));
		lua_rawset(L, -3);
		luaEXT_rawsetboolean(L, -1, "state", e->key.state);
		luaEXT_rawsetinteger(L, -1, "repeated", e->key.repeat);
		luaEXT_rawsetflagorinteger(L, -1, "scancode", e->key.keysym.scancode, flag_Scancode);
		//luaEXT_rawsetflagorinteger(L, -1, "sym", e->key.keysym.sym, flag_KeyCode);
		lua_pushstring(L, "sym");
		if (luaEXT_pushflagorinteger(L, e->key.keysym.sym, flag_KeyCode) == false) {
			lua_pop(L, 1);
			std::wstring str;
			str.push_back(e->key.keysym.sym);
			luaEXT_pushwstring(L, str.c_str());
		}
		lua_rawset(L, -1 - 2);
		


		luaEXT_rawsetflags(L, -1, "mod", e->key.keysym.mod, flag_Keymod, false);
		break;

	case SDL_MOUSEMOTION:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->motion.windowID));
		lua_rawset(L, -3);
		if (e->motion.which == SDL_TOUCH_MOUSEID) {
			luaEXT_rawsetstring(L, -1, "which", "TOUCH_MOUSE");
		}
		else {
			luaEXT_rawsetinteger(L, -1, "which", e->motion.which);
		}
		luaEXT_rawsetflags(L, -1, "button", e->motion.state, flag_MouseButton, true);
		luaEXT_rawsetboolean(L, -1, "state", SDL_PRESSED);
		luaEXT_rawsetinteger(L, -1, "x", e->motion.x);
		luaEXT_rawsetinteger(L, -1, "y", e->motion.y);
		luaEXT_rawsetinteger(L, -1, "xrel", e->motion.xrel);
		luaEXT_rawsetinteger(L, -1, "yrel", e->motion.yrel);
		break;

	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->button.windowID));
		lua_rawset(L, -3);
		if (e->button.which == SDL_TOUCH_MOUSEID) {
			luaEXT_rawsetstring(L, -1, "which", "TOUCH_MOUSE");
		}
		else {
			luaEXT_rawsetinteger(L, -1, "which", e->button.which);
		}
		if (e->button.button > 0 && e->button.button < 17) {
			luaEXT_rawsetstring(L, -1, "button", flag_MouseButton[e->button.button].name);
		} else {
			luaEXT_rawsetinteger(L, -1, "button", e->button.button);
		}
		luaEXT_rawsetboolean(L, -1, "state", e->button.state);
		luaEXT_rawsetinteger(L, -1, "clicks", e->button.clicks);
		luaEXT_rawsetinteger(L, -1, "x", e->button.x);
		luaEXT_rawsetinteger(L, -1, "y", e->button.y);
		break;

	case SDL_MOUSEWHEEL:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->wheel.windowID));
		lua_rawset(L, -3);
		if (e->button.which == SDL_TOUCH_MOUSEID) {
			luaEXT_rawsetstring(L, -1, "which", "TOUCH_MOUSE");
		}
		else {
			luaEXT_rawsetinteger(L, -1, "which", e->wheel.which);
		}
		luaEXT_rawsetinteger(L, -1, "x", e->wheel.x);
		luaEXT_rawsetinteger(L, -1, "y", e->wheel.y);
		luaEXT_rawsetflag(L, -1, "direction", e->wheel.direction, flag_MouseWheel);
		luaEXT_rawsetnumber(L, -1, "preciseX", e->wheel.preciseX);
		luaEXT_rawsetnumber(L, -1, "preciseY", e->wheel.preciseY);
		break;

	case SDL_TEXTEDITING:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->edit.windowID));
		lua_rawset(L, -3);
		luaEXT_rawsetstring(L, -1, "text", e->edit.text);
		luaEXT_rawsetinteger(L, -1, "start", e->edit.start);
		luaEXT_rawsetinteger(L, -1, "length", e->edit.length);
		break;

	case SDL_TEXTINPUT:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->text.windowID));
		lua_rawset(L, -3);
		luaEXT_rawsetstring(L, -1, "text", e->text.text);
		break;

	case SDL_QUIT:
		break;

	case SDL_WINDOWEVENT:
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->window.windowID));
		lua_rawset(L, -3);
		luaEXT_rawsetflag(L, -1, "event", e->window.event, flag_WindowEventID);
		if (e->window.event == SDL_WINDOWEVENT_MOVED) {
			luaEXT_rawsetinteger(L, -1, "x", e->window.data1);
			luaEXT_rawsetinteger(L, -1, "y", e->window.data2);
		}
		else if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
			luaEXT_rawsetinteger(L, -1, "w", e->window.data1);
			luaEXT_rawsetinteger(L, -1, "h", e->window.data2);
		}
		else if (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			luaEXT_rawsetinteger(L, -1, "w", e->window.data1);
			luaEXT_rawsetinteger(L, -1, "h", e->window.data2);
		}
		else if (e->window.event == SDL_WINDOWEVENT_DISPLAY_CHANGED) {
			luaEXT_rawsetinteger(L, -1, "display", e->window.data1);
		}
		break;

	case SDL_SYSWMEVENT:
		luaEXT_rawsetinteger(L, -1, "hwnd",(lua_Integer) e->syswm.msg->msg.win.hwnd);
		luaEXT_rawsetinteger(L, -1, "msg", (lua_Integer)e->syswm.msg->msg.win.msg);
		luaEXT_rawsetinteger(L, -1, "wParam", (lua_Integer)e->syswm.msg->msg.win.wParam);
		luaEXT_rawsetinteger(L, -1, "lParam", (lua_Integer)e->syswm.msg->msg.win.lParam);
		break;

	case SDL_JOYAXISMOTION:
		lua_pushstring(L, "which");
		pushJoystick(L, SDL_JoystickFromInstanceID(e->jaxis.which));
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "axis", e->jaxis.axis);
		luaEXT_rawsetnumber(L, -1, "value", (double)(e->jaxis.value / (e->jaxis.value >= 0 ? 32767.0 : 32768.0)));
		break;

	case SDL_JOYBALLMOTION:
		lua_pushstring(L, "which");
		pushJoystick(L, SDL_JoystickFromInstanceID(e->jball.which));
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "ball", e->jball.ball);
		luaEXT_rawsetinteger(L, -1, "xrel", e->jball.xrel);
		luaEXT_rawsetinteger(L, -1, "yrel", e->jball.yrel);
		break;

	case SDL_JOYHATMOTION:
		lua_pushstring(L, "which");
		pushJoystick(L, SDL_JoystickFromInstanceID(e->jhat.which));
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "hat", e->jhat.hat);
		luaEXT_rawsetflags(L, -1, "value", e->jhat.value, flag_JoystickHat, true);
		break;

	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		lua_pushstring(L, "which");
		pushJoystick(L, SDL_JoystickFromInstanceID(e->jbutton.which));
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "button", e->jbutton.button);
		luaEXT_rawsetboolean(L, -1, "state", e->jbutton.state);
		break;

	case SDL_JOYDEVICEADDED:
		luaEXT_rawsetinteger(L, -1, "which", e->jdevice.which);
		break;

	case SDL_JOYDEVICEREMOVED:
		lua_pushstring(L, "which");
		pushJoystick(L, SDL_JoystickFromInstanceID(e->jdevice.which));
		lua_rawset(L, -3);
		break;

	case SDL_SENSORUPDATE:
		lua_pushstring(L, "which");
		pushSensor(L, SDL_SensorFromInstanceID(e->sensor.which));
		lua_rawset(L, -3);
		luaEXT_rawsetnumber(L, -1, "x", e->sensor.data[0]);
		luaEXT_rawsetnumber(L, -1, "y", e->sensor.data[1]);
		luaEXT_rawsetnumber(L, -1, "z", e->sensor.data[2]);
		break;

	case SDL_CONTROLLERAXISMOTION:
		lua_pushstring(L, "which");
		pushGameController(L, SDL_GameControllerFromInstanceID(e->caxis.which));
		lua_rawset(L, -3);
		luaEXT_rawsetflag(L, -1, "axis", e->caxis.axis, flag_GameControllerAxis);
		luaEXT_rawsetnumber(L, -1, "value", (double)(e->caxis.value / (e->caxis.value >= 0 ? 32767.0 : 32768.0)));
		break;

	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		lua_pushstring(L, "which");
		pushGameController(L, SDL_GameControllerFromInstanceID(e->cbutton.which));
		lua_rawset(L, -3);
		luaEXT_rawsetflag(L, -1, "button", e->cbutton.button, flag_GameControllerButton);
		luaEXT_rawsetboolean(L, -1, "state", e->cbutton.state);
		break;

	case SDL_CONTROLLERDEVICEADDED:
		luaEXT_rawsetinteger(L, -1, "which", e->cdevice.which);
		break;

	case SDL_CONTROLLERDEVICEREMOVED:
	case SDL_CONTROLLERDEVICEREMAPPED:
		lua_pushstring(L, "which");
		pushGameController(L, SDL_GameControllerFromInstanceID(e->cdevice.which));
		lua_rawset(L, -3);
		break;

	case SDL_CONTROLLERTOUCHPADDOWN:
	case SDL_CONTROLLERTOUCHPADUP:
	case SDL_CONTROLLERTOUCHPADMOTION:
		lua_pushstring(L, "which");
		pushGameController(L, SDL_GameControllerFromInstanceID(e->ctouchpad.which));
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "touchpad", e->ctouchpad.touchpad);
		luaEXT_rawsetinteger(L, -1, "finger", e->ctouchpad.finger);
		luaEXT_rawsetnumber(L, -1, "x", e->ctouchpad.x);
		luaEXT_rawsetnumber(L, -1, "y", e->ctouchpad.y);
		luaEXT_rawsetnumber(L, -1, "pressure", e->ctouchpad.pressure);
		break;

	case SDL_CONTROLLERSENSORUPDATE:
		lua_pushstring(L, "which");
		pushGameController(L, SDL_GameControllerFromInstanceID(e->csensor.which));
		lua_rawset(L, -3);
		luaEXT_rawsetflag(L, -1, "sensor", e->csensor.sensor, flag_SensorType);
		luaEXT_rawsetnumber(L, -1, "x", e->csensor.data[0]);
		luaEXT_rawsetnumber(L, -1, "y", e->csensor.data[1]);
		luaEXT_rawsetnumber(L, -1, "z", e->csensor.data[2]);
		break;

	case SDL_AUDIODEVICEADDED:
	case SDL_AUDIODEVICEREMOVED:
		// ignore
		break;

	case SDL_FINGERMOTION:
	case SDL_FINGERDOWN:
	case SDL_FINGERUP:
		lua_pushstring(L, "touchId");
		pushTouchID(L, e->tfinger.touchId);
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "fingerId", e->tfinger.fingerId);
		luaEXT_rawsetnumber(L, -1, "x", e->tfinger.x);
		luaEXT_rawsetnumber(L, -1, "y", e->tfinger.y);
		luaEXT_rawsetnumber(L, -1, "dx", e->tfinger.dx);
		luaEXT_rawsetnumber(L, -1, "dy", e->tfinger.dy);
		luaEXT_rawsetnumber(L, -1, "pressure", e->tfinger.pressure);
		lua_pushstring(L, "window");
		pushWindow(L, SDL_GetWindowFromID(e->tfinger.windowID));
		lua_rawset(L, -3);
		break;

	case SDL_MULTIGESTURE:
		lua_pushstring(L, "touchId");
		pushTouchID(L, e->mgesture.touchId);
		lua_rawset(L, -3);
		luaEXT_rawsetnumber(L, -1, "dTheta", e->mgesture.dTheta);
		luaEXT_rawsetnumber(L, -1, "dDist", e->mgesture.dDist);
		luaEXT_rawsetnumber(L, -1, "x", e->mgesture.x);
		luaEXT_rawsetnumber(L, -1, "y", e->mgesture.y);
		luaEXT_rawsetinteger(L, -1, "numFingers", e->mgesture.numFingers);
		break;

	case SDL_DOLLARGESTURE:
	case SDL_DOLLARRECORD:
		lua_pushstring(L, "touchId");
		pushTouchID(L, e->dgesture.touchId);
		lua_rawset(L, -3);
		luaEXT_rawsetinteger(L, -1, "gestureId", e->dgesture.gestureId);
		luaEXT_rawsetinteger(L, -1, "numFingers", e->dgesture.numFingers);
		luaEXT_rawsetnumber(L, -1, "error", e->dgesture.error);
		luaEXT_rawsetnumber(L, -1, "x", e->dgesture.x);
		luaEXT_rawsetnumber(L, -1, "y", e->dgesture.y);
		break;

	default:
		if (e->type >= SDL_USEREVENT && e->type < SDL_LASTEVENT) {
			luaEXT_rawsetstring(L, -1, "type", "USER");
			luaEXT_rawsetinteger(L, -1, "event", e->type);
			lua_pushstring(L, "window");
			pushWindow(L, SDL_GetWindowFromID(e->user.windowID));
			lua_rawset(L, -3);
			luaEXT_rawsetinteger(L, -1, "code", e->user.code);
			luaEXT_rawsetinteger(L, -1, "data1", (lua_Integer)e->user.data1);
			luaEXT_rawsetinteger(L, -1, "data2", (lua_Integer)e->user.data2);
			break;
		}


		//missing SDL_AudioDeviceEvent
		//missing SDL_TouchFingerEvent
		//missing SDL_MultiGestureEvent
		//missing SDL_DollarGestureEvent

	}

}

SDL_Event toEvent(lua_State* L, int index) {
	SDL_Event ret;
	SDL_Event* e = &ret;
	lua_getfield(L, index, "type");
	ret.type = checkEventType(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, index, "timestamp");
	ret.common.timestamp = (Uint32) lua_tonumber(L, -1);
	lua_pop(L, 1);




	//missing

	return ret;
}

static int l_Event_Pump(lua_State* L) {
	SDL_PumpEvents();
	return 0;
}

static int l_Event_Poll(lua_State* L) {
	SDL_Event e;
	if (SDL_PollEvent(&e) == 1) {
		pushEvent(L, &e);
	}
	else {
		pushEvent(L, NULL);
	}
	return 1;
}

static int l_Event_Wait(lua_State* L) {
	int timeout = (int) luaL_optinteger(L, 1, 0);
	SDL_Event e;
	int ret;
	if (timeout <= 0) {
		ret = SDL_WaitEvent(&e);
	}
	else {
		ret = SDL_WaitEventTimeout(&e, timeout);
	}
	if (ret == 1) {
		pushEvent(L, &e);
	}
	else {
		pushEvent(L, NULL);
	}
	return 1;
}

static int l_Event_Push(lua_State* L) {
	SDL_Event e = toEvent(L, 1);
	lua_pushboolean(L, SDL_PushEvent(&e) >= 0);
	return 1;
}

static int l_Event_State(lua_State* L) {
	Uint32 type = checkEventType(L, 1);
	int state = checkEventState(L, 2);
	pushEventState(L, SDL_EventState(type, state));
	return 1;
}

static int l_Event_GetState(lua_State* L) {
	Uint32 type = checkEventType(L, 1);
	pushEventState(L, SDL_EventState(type, SDL_QUERY));
	return 1;
}


static int l_Event_Register(lua_State* L) {
	int num = (int)luaL_checkinteger(L, 1);
	lua_pushinteger(L, SDL_RegisterEvents(num));
	return 1;
}
