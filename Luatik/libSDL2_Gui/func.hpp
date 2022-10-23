#pragma once

const struct luaL_Reg array_Gui_func[] = {
	{"Init", l_gui_init},
	{"Quit", l_gui_quit},	
	{NULL,NULL}
};

const struct luaL_Reg array_Requester_func[] = {
	{"OpenFile",l_Requester_OpenFile},
	{"SaveFile",l_Requester_SaveFile},
	{"Message",l_Requester_Message},
	{NULL,NULL}
};
