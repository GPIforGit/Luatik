#pragma once

const struct luaL_Reg array_root_func[] = {
		{ "Quit", l_Quit }, // init
		{ "Init", l_Init }, // init
		{ "OpenURL", l_OpenURL}, // misc

		{ "POINT", l_POINT }, // new type
		{ "RECT", l_RECT }, // new type
		{ "VERTEX", l_VERTEX}, // new type
		{ "COLOR",l_COLOR}, // new type
		{ NULL, NULL}
};

const struct luaL_Reg array_blendmode_func[] = {
	{"ComposeCustom", l_BlendMode_ComposeCustom },
	{NULL, NULL}
};

const struct luaL_Reg array_Clipboard_func[] = {
	{"SetText", l_Clipboard_SetText},
	{"GetText", l_Clipboard_GetText},
	{"HasText", l_Clipboard_HasText},
	{"GetSurface", l_Clipboard_GetSurface},
	{NULL,NULL}
};

const struct luaL_Reg array_Display_func[] = {
	{"GetNum", l_Display_GetNum},
	{"GetName", l_Display_GetName},
	{"GetBounds", l_Display_GetBounds},
	{"GetUsableBounds", l_Display_GetUsableBounds},
	{"GetDPI", l_Display_GetDPI},
	{"GetOrientation", l_Display_GetOrientation},
	{"GetDesktopMode", l_Display_GetDesktopMode},
	{NULL,NULL}
};

const struct luaL_Reg array_Error_func[] = {
	{ "Get", l_error_get },
	{ "Clear", l_error_clear },
	{ "Set", l_error_set},
	{ NULL, NULL}
};

const struct luaL_Reg array_Event_func[] = {
	{"Pump", l_Event_Pump},
	{"Poll", l_Event_Poll},
	{"Wait", l_Event_Wait},
	{"Push", l_Event_Push},
	{"State", l_Event_State},
	{"GetState", l_Event_GetState},
	{"Register", l_Event_Register},
	{NULL, NULL }
};

const struct luaL_Reg array_Filesystem_func[] = {
	{"GetBasePath", l_Filesystem_GetBasePath},
	{"GetPrefPath", l_Filesystem_GetPrefPath},
	{NULL, NULL}
};

const struct luaL_Reg array_Hint_func[] = {
	{ "Set", l_hint_Set},
	{ "Get", l_hint_Get},
	{ "Clear", l_hint_Clear},
	{ "Reset", l_hint_Reset},
	{ NULL, NULL }
};

const struct luaL_Reg array_Keyboard_func[] = {
	{"GetFocus",l_Keyboard_GetFocus},
	{"GetState",l_Keyboard_GetState},
	{"GetScancodeValue",l_Keyboard_GetScancodeValue},
	{"GetKeyValue",l_Keyboard_GetKeyValue},
	{"GetModState",l_Keyboard_GetModState},
	{"SetModState",l_Keyboard_SetModState},
	{"GetKeyFromScancode",l_Keyboard_GetKeyFromScancode},
	{"GetScancodeFromKey",l_Keyboard_GetScancodeFromKey},
	{"GetScancodeName",l_Keyboard_GetScancodeName},
	{"GetScancodeFromName",l_Keyboard_GetScancodeFromName},
	{"GetKeyName",l_Keyboard_GetKeyName},
	{"GetKeyFromName",l_Keyboard_GetKeyFromName},
	{"HasScreenKeyboardSuppoer",l_Keyboard_HasScreenKeyboardSupport},
	{"IsScreenKeyboardShown",l_Keyboard_IsScreenKeyboardShown},
	{"Reset",l_Keyboard_Reset},
	{NULL,NULL}
};

const struct luaL_Reg array_Locale_func[] = {
	{"GetPreferred", l_locale_GetPreferred},
	{NULL,NULL}
};

const struct luaL_Reg array_MessageBox_array[] = {
	{"Show",l_MessageBox_Show},
	{"ShowSimple",l_MessageBox_ShowSimple},
	{NULL,NULL}
};

const struct luaL_Reg array_PixelFormat_func[] = {
	{ "Alloc", l_PixelFormat_Alloc },
	{ "Free", l_PixelFormat_Free },
	{ "Destroy", l_PixelFormat_Free },
	{ "MapRGB", l_PixelFormat_MapRGB },
	{ "MapRGBA", l_PixelFormat_MapRGBA },
	{ "GetRGB", l_PixelFormat_GetRGB },
	{ "GetRGBA", l_PixelFormat_GetRGBA },
	{ NULL, NULL}
};

const struct luaL_Reg array_Power_func[] = {
	{"GetInfo", l_Power_GetInfo},
	{NULL,NULL}
};

const struct luaL_Reg array_Rect_func[] = {
	{"ContainsPoint", l_Rect_ContainsPoint },
	{"Empty", l_Rect_Empty },
	{"Equals", l_Rect_Equals },
	{"Intersection", l_Rect_Intersection },
	{"Union", l_Rect_Union },
	{"IntersectLine", l_Rect_Union },
	{NULL,NULL}
};

const struct luaL_Reg array_Render_func[] = {
	{"Create", l_render_create},
	{"CreateSoftware", l_render_CreateSoftware},
	{"GetNumDrivers", l_render_GetNumDrivers},
	{"GetDriverInfo", l_render_GetDriverInfo},
	{"Get", l_render_Get},
	{"GetInfo", l_render_GetInfo},
	{"GetOutputSize", l_render_GetOutputSize},
	{"CreateTexture", l_render_CreateTexture},
	{"TargetSupported", l_render_TargetSupported},
	{"SetTarget", l_render_SetTarget},
	{"GetTarget", l_render_GetTarget},
	{"SetLogicalSize", l_render_SetLogicalSize},
	{"GetLogicalSize", l_render_GetLogicalSize},
	{"SetIntegerScale", l_render_SetIntegerScale},
	{"GetIntegerScale", l_render_GetIntegerScale},
	{"SetViewport", l_render_SetViewport},
	{"GetViewport", l_render_GetViewport},
	{"SetClipRect", l_render_SetClipRect},
	{"GetClipRect", l_render_GetClipRect},
	{"SetScale", l_render_SetScale},
	{"GetScale", l_render_GetScale},
	{"WindowToLogical", l_render_WindowToLogical},
	{"LogicalToWindow", l_render_LogicalToWindow},
	{"SetDrawColor",l_render_SetDrawColor},
	{"GetDrawColor",l_render_GetDrawColor},
	{"SetDrawBlendMode",l_render_SetDrawBlendMode},
	{"GetDrawBlendMode",l_render_GetDrawBlendMode},
	{"Clear",l_render_Clear},
	{"DrawPoint",l_render_DrawPoint},
	{"DrawPoints",l_render_DrawPoints},
	{"DrawLine",l_render_DrawLine},
	{"DrawLines",l_render_DrawLines},
	{"DrawRect",l_render_DrawRect},
	{"DrawRects",l_render_DrawRects},
	{"FillRect",l_render_FillRect},
	{"FillRects",l_render_FillRects},
	{"Copy", l_render_Copy},
	{"CopyEx", l_render_CopyEx},
	{"Geometry", l_render_Geometry},
	{"Present", l_render_Present},
	{"Destroy", l_render_Destroy},
	{"Free", l_render_Destroy},
	{"SetVSync", l_render_SetVSync},
	{NULL,NULL}
};

const struct luaL_Reg array_ScreenSaver_func[] = {
	{"IsEnabled", l_ScreenSaver_IsEnabled},
	{"Enable", l_ScreenSaver_Enable},
	{"Disable", l_ScreenSaver_Disable},
	{NULL,NULL}
};

const struct luaL_Reg array_Surface_func[] = {
	{"CreateRGB", l_Surface_CreateRGB},
	{"LoadBMP", l_Surface_LoadBMP},
	{"Duplicate", l_Surface_Duplicate},
	{"Convert", l_Surface_Convert},

	{"GetPixelFormat", l_Surface_GetPixelFormat},
	{"GetSize", l_Surface_GetSize},
	{"GetPixels", l_Surface_GetPixels},
	{"Free", l_Surface_Free},
	{"Destroy", l_Surface_Free},
	{"Lock", l_Surface_Lock},
	{"Unlock", l_Surface_Unlock},
	{"SaveBMP", l_Surface_SaveBMP},
	{"SetRLE", l_Surface_SetRLE},
	{"HasRLE", l_Surface_HasRLE},
	{"SetColorKey", l_Surface_SetColorKey},
	{"GetColorKey", l_Surface_GetColorKey},
	{"SetColorMod", l_Surface_SetColorMod},
	{"GetColorMod", l_Surface_GetColorMod},
	{"SetAlphaMod", l_Surface_SetAlphaMod},
	{"GetAlphaMod", l_Surface_GetAlphaMod},
	{"SetBlendMode", l_Surface_SetBlendMode},
	{"GetBlendMode", l_Surface_GetBlendMode},
	{"SetClip", l_Surface_SetClip},
	{"GetClip", l_Surface_GetClip},
	{"FillRect", l_Surface_FillRect},
	{"Blit", l_Surface_Blit},
	{"BlitScaled", l_Surface_BlitScaled},
	{"SoftStretched", l_Surface_SoftStretch},
	{"SetYUVConversionMode", l_Surface_SetYUVConversionMode},
	{"GetYUVConversionMode", l_Surface_GetYUVConversionMode},
	{"GetYUVConversionModeForResolution", l_Surface_GetYUVConversionModeForResolution},
	{"CreateSoftwareRenderer", l_render_CreateSoftware },

	{NULL,NULL}
};

const struct luaL_Reg array_TextInput_func[] = {
	{"Start",l_TextInput_Start},
	{"IsActive",l_TextInput_IsActive},
	{"Stop",l_TextInput_Stop},
	{"SetRect", l_TextInput_SetRect},
	{NULL,NULL}
};

const struct luaL_Reg array_Texture_func[] = {
	{"Create", l_render_CreateTexture},
	{"Query", l_texture_Query},
	{"SetColorMod", l_texture_SetColorMod},
	{"GetColorMod", l_texture_GetColorMod},
	{"SetAlphaMod", l_texture_SetAlphaMod},
	{"GetAlphaMod", l_texture_GetAlphaMod},
	{"SetBlendMode", l_texture_SetBlendMode},
	{"GetBlendMode", l_texture_GetBlendMode},
	{"SetScaleMode", l_texture_SetScaleMode},
	{"GetScaleMode", l_texture_GetScaleMode},
	{"SetUserData", l_texture_SetUserData},
	{"GetUserData", l_texture_GetUserData},
	{"Lock", l_texture_Lock},
	{"LockToSurface", l_texture_LockToSurface},
	{"Unlock", l_texture_Unlock},
	{"Destroy", l_texture_Destroy},
	{"Free", l_texture_Destroy},
	{NULL,NULL}
};

const struct luaL_Reg array_Time_func[] = {
	{"GetTicks", l_Time_GetTicks },
	{"GetPerformanceCounter", l_Time_GetPerformanceCounter},
	{"GetPerformanceFrequency", l_Time_GetPerformanceFrequency},
	{"Get", l_Time_Get},
	{"Delay", l_Time_Delay},
	{NULL, NULL}
};

const struct luaL_Reg array_Version_func[] = {
	{"Get", l_Version_Get },
	{"AtLeast", l_Version_AtLeast},
	{NULL,NULL}
};

const struct luaL_Reg array_Void_func[] = {
	{"set8",l_void_set8},
	{"set16",l_void_set16},
	{"set32",l_void_set32},
	{"set64",l_void_set64},

	{"setu8",l_void_setu8},
	{"setu16",l_void_setu16},
	{"setu32",l_void_setu32},
	{"setu64",l_void_setu64},

	{"get8",l_void_get8},
	{"get16",l_void_get16},
	{"get32",l_void_get32},
	{"get64",l_void_get64},

	{"getu8",l_void_getu8},
	{"getu16",l_void_getu16},
	{"getu32",l_void_getu32},
	{"getu64",l_void_getu64},

	{NULL,NULL}
};

const struct luaL_Reg array_Window_func[] = {
	{"Create", l_Window_Create},
	{"GetGrabbed", l_Window_GetGrabbed},

	{"GetDisplayIndex", l_Window_GetDisplayIndex},
	{"GetPixelFormat", l_Window_GetPixelFormat},
	{"GetFlags", l_Window_GetFlags},
	{"SetTitle", l_Window_SetTitle},
	{"GetTitle", l_Window_GetTitle},
	{"SetIcon", l_Window_SetIcon},
	{"SetData", l_Window_SetData},
	{"GetData", l_Window_GetData},
	{"SetPosition", l_Window_SetPosition},
	{"GetPosition", l_Window_GetPosition},
	{"SetSize", l_Window_SetSize},
	{"GetSize", l_Window_GetSize},
	{"GetBordersSize", l_Window_GetBordersSize},
	{"SetMinimumSize", l_Window_SetMinimumSize},
	{"GetMinimumSize", l_Window_GetMinimumSize},
	{"SetMaximumSize", l_Window_SetMaximumSize},
	{"GetMaximumSize", l_Window_GetMaximumSize},
	{"SetBordered", l_Window_SetBordered},
	{"SetResizable", l_Window_SetResizable},
	{"SetAlwaysOnTop", l_Window_SetAlwaysOnTop},
	{"Show", l_Window_Show},
	{"Hide", l_Window_Hide},
	{"Raise", l_Window_Raise},
	{"Maximize", l_Window_Maximize},
	{"Minimize", l_Window_Minimize},
	{"Restore", l_Window_Restore},
	{"SetFullscreen", l_Window_SetFullscreen},
	{"GetSurface", l_Window_GetSurface},
	{"UpdateSurface", l_Window_UpdateSurface},
	{"SetGrab", l_Window_SetGrab},
	{"SetKeyboardGrab", l_Window_SetKeyboardGrab},
	{"SetMouseGrab", l_Window_SetMouseGrab},
	{"GetGrab", l_Window_GetGrab},
	{"GetKeyboardGrab", l_Window_GetKeyboardGrab},
	{"GetMouseGrab", l_Window_GetMouseGrab},
	{"SetMouseRect", l_Window_SetMouseRect},
	{"GetMouseRect", l_Window_GetMouseRect},
	{"SetOpacity", l_Window_SetOpacity},
	{"GetOpacity", l_Window_GetOpacity},
	{"ModalFor", l_Window_ModalFor},
	{"SetInputFocus", l_Window_SetInputFocus},
	{"Flash", l_Window_Flash},
	{"Destroy", l_Window_Destroy},
	{"Free", l_Window_Destroy},
	{"IsScreenKeyboardShown",l_Keyboard_IsScreenKeyboardShown},
	{"WarpMouseIn",l_mouse_WarpInWindow},

	{"CreateRenderer", l_render_create },
	{"GetRenderer", l_render_Get},

	{"GetOsHandle", l_Window_GetOsHandle},

	{"SetShape", l_Window_SetShape},
	{"GetShape", l_Window_GetShape},
	{"SetHitBox", l_Window_SetHitBox},

	{NULL,NULL}
};

const struct luaL_Reg array_Mouse_func[] = {
	{"GetFocus", l_mouse_GetFocus},
	{"GetState", l_mouse_GetState},
	{"GetGlobalState", l_mouse_GetGlobalState},
	{"GetRelativeState", l_mouse_GetRelativeState},
	{"WarpInWindow", l_mouse_WarpInWindow},
	{"WarpGlobal", l_mouse_WarpGlobal},
	{"SetRelativeMode", l_mouse_SetRelativeMode},
	{"GetRelativeMode", l_mouse_GetRelativeMode},
	{"Capture", l_mouse_Capture},
	{NULL,NULL}
};

const struct luaL_Reg array_Cursor_func[] = {
	{"Create", l_cursor_Create},
	{"Set", l_cursor_Set},
	{"Get", l_cursor_Get},
	{"GetDefault", l_cursor_GetDefault},
	{"Free", l_cursor_Free},
	{"Destroy", l_cursor_Free},
	{"Show", l_cursor_Show},
	{NULL,NULL}
};

const struct luaL_Reg array_Joystick_func[] = {
	{"GetNum", l_joystick_GetNum},
	{"GetName", l_joystick_GetName},
	{"GetPlayerIndex", l_joystick_GetPlayerIndex},
	{"GetGUID", l_joystick_GetGUID},
	{"GetVendor", l_joystick_GetVendor},
	{"GetProduct", l_joystick_GetProduct},
	{"GetProductVersion", l_joystick_GetProductVersion},
	{"GetType", l_joystick_GetType},
	{"Open", l_joystick_Open},
	{"FromPlayerIndex", l_joystick_FromPlayerIndex},
	{"AttachVirtual", l_joystick_AttachVirtual},
	{"DetachVirtual", l_joystick_DetachVirtual},
	{"IsVirtual", l_joystick_IsVirtual},
	{"SetVirtualAxis", l_joystick_SetVirtualAxis},
	{"SetVirtualButton", l_joystick_SetVirtualButton},
	{"SetVirtualHat", l_joystick_SetVirtualHat},
	{"SetPlayerIndex", l_joystick_SetPlayerIndex},
	{"GetSerial", l_joystick_GetSerial},
	{"GetAttached", l_joystick_GetAttached},
	{"GetNumAxes", l_joystick_GetNumAxes},
	{"GetNumBalls", l_joystick_GetNumBalls},
	{"GetNumHats", l_joystick_GetNumHats},
	{"GetNumButtons", l_joystick_GetNumButtons},
	{"Update",l_joystick_Update},
	{"EventState",l_Joystick_EventState},
	{"GetAxis",l_joystick_GetAxis},
	{"GetAxisInitalState",l_joystick_GetAxisInitialState},
	{"GetHat",l_joystick_GetHat},
	{"GetBall",l_joystick_GetBall},
	{"GetButton",l_joystick_GetButton},
	{"Rumble",l_joystick_Rumble},
	{"RumbleTriggers",l_joystick_RumbleTriggers},
	{"HasLED",l_joystick_HasLED},
	{"HasRumble",l_joystick_HasRumble},
	{"HasRumbleTriggers",l_joystick_HasRumbleTriggers},
	{"SetLED",l_joystick_SetLED},
	{"Close",l_joystick_Close},
	{"GetPowerLevel",l_joystick_GetPowerLevel},
	{NULL,NULL}
};

const struct luaL_Reg array_Sensor_func[] = {
	{"GetNum", l_sensor_GetNum},
	{"GetName", l_sensor_GetName},
	{"GetType", l_sensor_GetType},
	{"Open", l_sensor_Open},
	{"GetData", l_sensor_GetData},
	{"Close", l_sensor_Close},
	{"Update", l_sensor_Update},
	{NULL,NULL}
};

const struct luaL_Reg array_GameController_func[] = {
	{"AddMappingFromFile", l_GameController_AddMappingFromFile},
	{"AddMapping", l_GameController_AddMapping},
	{"GetNumMappings", l_GameController_GetNumMappings},
	{"GetMappingFromIndex", l_GameController_GetMappingFromIndex},
	{"GetMapping", l_GameController_GetMapping},
	{"Is",l_GameController_Is},
	{"Open", l_GameController_Open},
	{"FromPlayerIndex", l_GameControllerFromPlayerIndex},
	{"GetName", l_GameController_GetName},
	{"GetType", l_GameController_GetType},
	{"GetPlayerIndex", l_GameController_GetPlayerIndex},
	{"SetPlayerIndex", l_GameController_SetPlayerIndex},
	{"GetVendor", l_GameController_GetVendor},
	{"GetProduct", l_GameController_GetProduct},
	{"GetProductVersion", l_GameController_GetProductVersion},
	{"GetSerial", l_GameController_GetSerial},
	{"GetAttached", l_GameController_GetAttached},
	{"GetJoystick", l_GameController_GetJoystick},
	{"EventState", l_GameController_EventState},
	{"Update", l_GameController_Update},
	{"HasAxis", l_GameController_HasAxis},
	{"GetAxis", l_GameController_GetAxis},
	{"HasButton", l_GameController_HasButton},
	{"GetButton", l_GameController_GetButton},
	{"GetNumTouchpad", l_GameController_GetNumTouchpads},
	{"GetNumTouchpadFingers", l_GameController_GetNumTouchpadFingers },
	{"GetTouchpadFinger", l_GameController_GetTouchpadFinger},
	{"HasSensor",l_GameController_HasSensor},
	{"SetSensorEnabled", l_GameController_SetSensorEnabled},
	{"IsSensorEnabled", l_GameController_IsSensorEnabled},
	{"GetSensorDataRate", l_GameController_GetSensorDataRate},
	{"GetSensorData", l_GameController_GetSensorData},
	{"Rumble", l_GameController_Rumble},
	{"RumbleTriggers", l_GameController_RumbleTriggers},
	{"HasLED", l_GameController_HasLED},
	{"HasRumble", l_GameController_HasRumble},
	{"HasRumbleTriggers", l_GameController_HasRumbleTriggers},
	{"Close",l_GameController_Close},


	{NULL,NULL}
};

const struct luaL_Reg array_Touch_func[] = {
	{"GetNum", l_touch_GetNum},
	{"Open",l_touch_Open},
	{"Close",l_touch_Close},
	{"GetNumFingers", l_touch_GetNumFingers},
	{"GetFinger",l_touch_GetFinger},
	{NULL,NULL}
};

const struct luaL_Reg array_RW_func[] = {
	{"Open", l_RW_Open},
	{"Size", l_RW_Size},
	{"Seek", l_RW_Seek},
	{"Tell", l_RW_Tell},
	{"ReadString", l_RW_ReadString},
	{"WriteString", l_RW_WriteString},
	{"Close", l_RW_Close},
	{"Load", l_RW_Load},
	{"Save", l_RW_Save},
	
	{"ReadU8", l_RW_ReadU8},
	{"ReadLEU16",l_RW_ReadLEU16},
	{"ReadBEU16",l_RW_ReadBEU16},
	{"ReadLEU32",l_RW_ReadLEU32},
	{"ReadBEU32",l_RW_ReadBEU32},
	
	{"ReadS8", l_RW_ReadS8},
	{"ReadLES16",l_RW_ReadLES16},
	{"ReadBES16",l_RW_ReadBES16},
	{"ReadLES32",l_RW_ReadLES32},
	{"ReadBES32",l_RW_ReadBES32},
	{"ReadLES64",l_RW_ReadLES64},
	{"ReadBES64",l_RW_ReadBES64},

	{"ReadULEFloat",l_RW_ReadLEFloat},
	{"ReadUBEFloat",l_RW_ReadBEFloat},
	{"ReadLEDouble",l_RW_ReadLEDouble},
	{"ReadBEDouble",l_RW_ReadBEDouble},

	{"Write8",l_RW_Write8},
	{"WriteLE16",l_RW_WriteLE16},
	{"WriteBE16",l_RW_WriteBE16},
	{"WriteLE32",l_RW_WriteLE32},
	{"WriteBE32",l_RW_WriteBE32},
	{"WriteLE64",l_RW_WriteLE64},
	{"WriteBE64",l_RW_WriteBE64},

	{"WriteLEFloat",l_RW_WriteLEFloat},
	{"WriteBEFloat",l_RW_WriteBEFloat},
	{"WriteLEDouble",l_RW_WriteLEDouble},
	{"WriteBEDouble",l_RW_WriteBEDouble},

	{NULL,NULL}
};

const struct luaL_Reg array_Gesture_func[] = {
	{"Record",l_gesture_Record},
	{"SaveTemplate", l_gesture_SaveTemplate},
	{"SaveAllTemplates", l_gesture_SaveAllTemplates},
	{"LoadTempaltes",l_gesture_LoadTemplates},
	{NULL,NULL},
};
