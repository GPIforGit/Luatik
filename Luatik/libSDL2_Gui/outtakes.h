#pragma once

// init

lua_newtable(L);
lua_setfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);

// get default font
NONCLIENTMETRICSA metrics;
metrics.cbSize = sizeof(NONCLIENTMETRICS);
SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICSA), &metrics, 0);
std::string font_name = metrics.lfMessageFont.lfFaceName;
LONG font_weight = metrics.lfMessageFont.lfWeight;
bool font_italic = metrics.lfMessageFont.lfItalic != 0;

// calulate font size
HDC dc = CreateDCA("DISPLAY", NULL, NULL, NULL);
int font_size = metrics.lfMessageFont.lfHeight;// *72 / GetDeviceCaps(dc, LOGPIXELSY);
if (metrics.lfMessageFont.lfHeight < 0) {
	//font_size = -metrics.lfMessageFont.lfHeight+3;//MulDiv(metrics.lfMessageFont.lfHeight, 72, GetDeviceCaps(dc, LOGPIXELSY));
	font_size = -MulDiv(metrics.lfMessageFont.lfHeight, GetDeviceCaps(dc, LOGPIXELSY), 72);
}
//printf("Height:%d %d\n", font_size, metrics.lfMessageFont.lfHeight);
DeleteDC(dc);

// get font path
PWSTR path;
SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &path);
std::string font_path = luaEXT_convertutf8(L, path);
CoTaskMemFree((LPVOID)path);

// get font file name from registry
LONG sel_weight = 0;
bool sel_italic = 0;
std::string sel_font = font_name + ".ttf"; // fallback
std::string sel_fontsymbol;

HKEY key;
if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 0, KEY_READ, &key) == ERROR_SUCCESS) {
	wchar_t bufValue[MAX_PATH + 2];
	wchar_t bufEntry[MAX_PATH + 2];
	DWORD index = 0;
	while (true) {
		DWORD countValue = MAX_PATH;
		DWORD type;
		DWORD entrySize = MAX_PATH * sizeof(wchar_t); // size is here in bytes noch wchar_t!
		if (RegEnumValueW(key, index++, bufValue, &countValue, NULL, &type, (LPBYTE)&bufEntry, &entrySize) != ERROR_SUCCESS) {
			break;
		}

		std::string value = luaEXT_convertutf8(L, bufValue);
		// value is same as fontname and entry is string!
		if (type == REG_SZ && font_name == value.substr(0, font_name.length())) {
			int weight = FW_REGULAR;
			size_t pos = font_name.length() - 1;
			bool italic = false;
			bool special = false;

			// lower case
			transform(value.begin(), value.end(), value.begin(), ::tolower);

			// find weight
			if (value.find("thin", pos) != std::string::npos) {
				weight = FW_THIN;
			}
			else if (value.find("extralight", pos) != std::string::npos || value.find("extra light", pos) != std::string::npos ||
				value.find("ultralight", pos) != std::string::npos || value.find("ultra light", pos) != std::string::npos) {
				weight = FW_EXTRALIGHT;
			}
			else if (value.find("light", pos) != std::string::npos) {
				weight = FW_LIGHT;
			}
			else if (value.find("normal", pos) != std::string::npos || value.find("regular", pos) != std::string::npos) {
				weight = FW_REGULAR;
			}
			else if (value.find("medium", pos) != std::string::npos) {
				weight = FW_MEDIUM;
			}
			else if (value.find("extrabold", pos) != std::string::npos || value.find("extra bold", pos) != std::string::npos ||
				value.find("ultrabold", pos) != std::string::npos || value.find("ultra bold", pos) != std::string::npos) {
				weight = FW_EXTRABOLD;
			}
			else if (value.find("bold", pos) != std::string::npos) {
				weight = FW_BOLD;
			}
			else if (value.find("heavy", pos) != std::string::npos || value.find("black", pos) != std::string::npos) {
				weight = FW_BLACK;
			}
			// italic?
			if (value.find("italic", pos) != std::string::npos) {
				italic = true;
			}
			// something special?
			if (value.find("emoji", pos) != std::string::npos || value.find("historic", pos) != std::string::npos ||
				value.find("symbol", pos) != std::string::npos) {
				special = true;
			}
			if (value.find("symbol", pos) != std::string::npos) {
				sel_fontsymbol = luaEXT_convertutf8(L, bufEntry);
			}


			printf(" %ls %ls \n", bufValue, bufEntry);
			// and does it fit?
			if (special == false) {
				// weight between selected and needed?
				if (sel_weight == 0 || (sel_weight <= weight && weight <= font_weight) || (font_weight <= weight && weight <= sel_weight)) {
					// does italic fit? (or choose italic if nothing fit)
					if (sel_weight == 0 || sel_italic != font_italic) {
						sel_weight = weight;
						sel_italic = italic;
						sel_font = luaEXT_convertutf8(L, bufEntry);

					}
				}
			}
		}
	}

	RegCloseKey(key);
}

// combine font-file string

//sel_font = "seguisym.ttf";

std::string font = font_path + "\\" + sel_font;

//printf("%s %d\n", font.c_str(), font_size);

// load font
gSystemFont = TTF_OpenFont(font.c_str(), font_size);
if (gSystemFont == NULL) {
	//Hard fallback!
	gSystemFont = TTF_OpenFont("C:\\WINDOWS\\Fonts\\segoeui.ttf", font_size);
}

if (sel_fontsymbol == "") {
	sel_fontsymbol = sel_font;
}

font = font_path + "\\" + sel_fontsymbol;
gSymbolFont = TTF_OpenFont(font.c_str(), font_size);
if (gSymbolFont == NULL) {
	//Hard fallback!
	gSymbolFont = TTF_OpenFont("C:\\WINDOWS\\Fonts\\seguisym.ttf", font_size);
}


//quit

if (gSystemFont != NULL) {
	TTF_CloseFont(gSystemFont);
	gSystemFont = NULL;
}
if (gSymbolFont != NULL) {
	TTF_CloseFont(gSymbolFont);
	gSymbolFont = NULL;
}



static int l_gui_GetDefaultTheme(lua_State* L) {
	sColorTheme def = defaultTheme();
	pushColorTheme(L, &def);
	return 1;
}


static void RequiredSize(sGuiElement* ele, int* w, int* h) {

	GetTextureSize(ele->texNormal, w, h);

	int imgw = 0, imgh = 0, ww, hh;

	switch (ele->Type) {
	case Control_Button:

		if (ele->tex.back) {
			GetTextureSize(ele->tex.back, &ww, &hh);
			imgw = imgw < ww ? ww : imgw;
			imgh = imgh < hh ? hh : imgh;
		}
		if (ele->tex.fore) {
			GetTextureSize(ele->tex.fore, &ww, &hh);
			imgw = imgw < ww ? ww : imgw;
			imgh = imgh < hh ? hh : imgh;
		}
		if (ele->tex.top) {
			GetTextureSize(ele->tex.top, &ww, &hh);
			imgw = imgw < ww ? ww : imgw;
			imgh = imgh < hh ? hh : imgh;
		}
		printf("%d %d", imgw, imgh);
		*w += GetSystemMetrics(SM_CXFRAME) * 2 + imgw;
		*h += GetSystemMetrics(SM_CYFRAME) * 2 + imgh;



		break;
	default:
		printf("UNKNOWN ELEMENT TYPE %d\n", ele->Type);

	}


}

static int l_gui_CreateButton(lua_State* L) {
	SDL_Window* sdlwin = checkWindow(L, 1);
	int w = (int)checkroundnumber(L, 2);
	int h = (int)checkroundnumber(L, 3);
	const char* text = luaL_checkstring(L, 4);
	DWORD style = checkButtonFlags(L, 5);
	sColorTheme ct = toColorTheme(L, 6);

	sGuiElement* ele = CreateGuiElement(L, Control_Button, text, style, sdlwin, &ct, w, h);
	//printf(" %s = %s \n", text, ele->text.c_str());

	SDL_Surface* sur;

	SDL_Color light = {
		col_offset(ct.normal.back.r,50),
		col_offset(ct.normal.back.g,50),
		col_offset(ct.normal.back.b,50),
		ct.normal.back.a
	};

	sur = TTF_RenderUNICODE_Blended(gSymbolFont, (const Uint16*)charRadioBack, light);
	ele->tex.back = SDL_CreateTextureFromSurface(ele->renderer, sur);
	SDL_FreeSurface(sur);

	sur = TTF_RenderUNICODE_Blended(gSymbolFont, (const Uint16*)charRadioFore, ele->ct.normal.fore);
	ele->tex.fore = SDL_CreateTextureFromSurface(ele->renderer, sur);
	SDL_FreeSurface(sur);

	sur = TTF_RenderUNICODE_Blended(gSymbolFont, (const Uint16*)charRadioCheck, ele->ct.selected.fore);
	ele->tex.top = SDL_CreateTextureFromSurface(ele->renderer, sur);
	SDL_FreeSurface(sur);


	return 1;
}

static int l_gui_Draw(lua_State* L) {
	SDL_Renderer* ren = checkRenderer(L, 1);

	SDL_RenderSetViewport(ren, NULL);

	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);
	lua_pushnil(L);  /* first key */
	while (lua_next(L, -2) != 0) {
		sGuiElement* ele = (sGuiElement*)lua_touserdata(L, -1);

		if (ele->renderer == ren) {
			//printf("Draw Ren! %s \n", ele->text.c_str());
			//printf("  %d %d %d %d\n", ele->pos.x, ele->pos.y, ele->pos.w, ele->pos.h);
			SDL_RenderSetClipRect(ele->renderer, &ele->pos);

			SDL_Texture* tex = NULL;
			SDL_Color* fg, * bg;

			if (ele->state & GuiElement_Style_Disabled) {
				bg = &ele->ct.inactive.back;
				fg = &ele->ct.inactive.fore;
				tex = ele->texInactive;
			}
			else if (ele->state & GuiElement_Style_Selected) {
				if (ele->state & GuiElement_Style_Hot) {
					bg = &ele->ct.hot.backselected;
				}
				else {
					bg = &ele->ct.selected.back;
				}
				fg = &ele->ct.selected.fore;
				tex = ele->texSelected;
			}
			else {
				if (ele->state & GuiElement_Style_Hot) {
					bg = &ele->ct.hot.back;
				}
				else {
					bg = &ele->ct.normal.back;
				}
				fg = &ele->ct.normal.fore;
				tex = ele->texNormal;
			}

			switch (ele->Type) {
			case Control_Button:

				SDL_SetRenderDrawColor(ele->renderer, bg->r, bg->g, bg->b, bg->a);
				SDL_RenderFillRect(ele->renderer, &ele->pos);

				if (ele->style & BS_DEFPUSHBUTTON) {
					SDL_SetRenderDrawColor(ele->renderer, ele->ct.selected.fore.r, ele->ct.selected.fore.g, ele->ct.selected.fore.b, ele->ct.selected.fore.a);
					SDL_Rect r = ele->pos;
					SDL_RenderDrawRect(ele->renderer, &r);
					r.x += 1;
					r.y += 1;
					r.w -= 2;
					r.h -= 2;
					SDL_RenderDrawRect(ele->renderer, &r);
				}
				else {
					SDL_SetRenderDrawColor(ele->renderer, fg->r, fg->g, fg->b, fg->a);
					SDL_RenderDrawRect(ele->renderer, &ele->pos);
				}

				SDL_Rect dest;
				GetTextureSize(tex, &dest.w, &dest.h);
				if (ele->style & BS_LEFT) {
					dest.x = ele->pos.x + GetSystemMetrics(SM_CXFRAME);
				}
				else if (ele->style & BS_RIGHT) {
					dest.x = ele->pos.x + ele->pos.w - dest.w - GetSystemMetrics(SM_CXFRAME);
				}
				else {
					dest.x = ele->pos.x + (ele->pos.w - dest.w) / 2;
				}
				if (ele->style & BS_TOP) {
					dest.y = ele->pos.y + GetSystemMetrics(SM_CYFRAME);
				}
				else if (ele->style & BS_BOTTOM) {
					dest.y = ele->pos.y + ele->pos.h - dest.h - GetSystemMetrics(SM_CYFRAME);
				}
				else {
					dest.y = ele->pos.y + (ele->pos.h - dest.h) / 2;
				}
				if (ele->state & GuiElement_Style_Selected) {
					dest.x += 1;
					dest.y += 1;
				}

				SDL_RenderCopy(ele->renderer, tex, NULL, &dest);

				int imgw = 0, imgh = 0;
				int backw, backh, forew, foreh, topw, toph;
				if (ele->tex.back) {
					GetTextureSize(ele->tex.back, &backw, &backh);
					imgw = imgw < backw ? backw : imgw;
					imgh = imgh < backh ? backh : imgh;
				}
				if (ele->tex.fore) {
					GetTextureSize(ele->tex.fore, &forew, &foreh);
					imgw = imgw < forew ? forew : imgw;
					imgh = imgh < foreh ? foreh : imgh;
				}
				if (ele->tex.top) {
					GetTextureSize(ele->tex.top, &topw, &toph);
					imgw = imgw < topw ? topw : imgw;
					imgh = imgh < toph ? toph : imgh;
				}
				SDL_Rect destImg;
				if (ele->tex.back) {
					destImg.x = dest.x - (imgw + backw) / 2;
					destImg.y = dest.y + (dest.h - imgh) / 2 + (imgh - backh) / 2;
					destImg.w = backw;
					destImg.h = backh;
					SDL_RenderCopy(ele->renderer, ele->tex.back, NULL, &destImg);
				}
				if (ele->tex.fore) {
					destImg.x = dest.x - (imgw + forew) / 2;
					destImg.y = dest.y + (dest.h - imgh) / 2 + (imgh - foreh) / 2;
					destImg.w = forew;
					destImg.h = foreh;
					SDL_RenderCopy(ele->renderer, ele->tex.fore, NULL, &destImg);
				}
				if (ele->tex.top) {
					destImg.x = dest.x - (imgw + topw) / 2;
					destImg.y = dest.y + (dest.h - imgh) / 2 + (imgh - toph) / 2;
					destImg.w = topw;
					destImg.h = toph;
					SDL_RenderCopy(ele->renderer, ele->tex.top, NULL, &destImg);
				}

			}


		}

		lua_pop(L, 1);
	}
	lua_pop(L, 1);

	SDL_RenderSetClipRect(ren, NULL);
	return 0;
}


static int l_element_SetSize(lua_State* L) {
	sGuiElement* ele = checkGuiElement(L, 1);


	int& x = ele->pos.x;
	int& y = ele->pos.y;
	int& w = ele->pos.w;
	int& h = ele->pos.h;

	if (lua_isnumber(L, 2) || lua_isnoneornil(L, 2)) {
		// simple set
		x = (int)optroundnumber(L, 2, x);
		y = (int)optroundnumber(L, 3, y);
		w = (int)optroundnumber(L, 4, w);
		h = (int)optroundnumber(L, 5, h);

		if (x < 0 || y < 0) {
			int rw, rh;
			SDL_GetRendererOutputSize(ele->renderer, &rw, &rh);

			if (x < 0) {
				x = rw - w + x + 1;
			}
			if (y < 0) {
				y = rh - h + y + 1;
			}
		}

	}
	else {
		int pos = checkPos(L, 2);
		int space = (int)checkroundnumber(L, 3);
		sGuiElement* anker = checkGuiElement(L, 4);
		w = (int)optroundnumber(L, 5, w);
		h = (int)optroundnumber(L, 6, h);

		switch (pos) {
		case Pos_TopLeft:
			x = anker->pos.x;
			y = anker->pos.y - h - space;
			break;
		case Pos_Top:
			x = anker->pos.x + (anker->pos.w - w) / 2;
			y = anker->pos.y - h - space;
			break;
		case Pos_TopRight:
			x = anker->pos.x + anker->pos.w - w;
			y = anker->pos.y - h - space;
			break;

		case Pos_BottomLeft:
			x = anker->pos.x;
			y = anker->pos.y + anker->pos.h + space;
			break;
		case Pos_Bottom:
			x = anker->pos.x + (anker->pos.w - w) / 2;
			y = anker->pos.y + anker->pos.h + space;
			break;
		case Pos_BottomRight:
			x = anker->pos.x + anker->pos.w - w;
			y = anker->pos.y + anker->pos.h + space;
			break;

		case Pos_LeftTop:
			x = anker->pos.x - w - space;
			y = anker->pos.y;
			break;
		case Pos_Left:
			x = anker->pos.x - w - space;
			y = anker->pos.y + (anker->pos.h - h) / 2;
			break;
		case Pos_LeftBottom:
			x = anker->pos.x - w - space;
			y = anker->pos.y + anker->pos.h - h;
			break;

		case Pos_RightTop:
			x = anker->pos.x + anker->pos.w + space;
			y = anker->pos.y;
			break;
		case Pos_Right:
			x = anker->pos.x + anker->pos.w + space;
			y = anker->pos.y + (anker->pos.h - h) / 2;
			break;
		case Pos_RightBottom:
			x = anker->pos.x + anker->pos.w + space;
			y = anker->pos.y + anker->pos.h - h;
			break;
		}


	}

	return 0;
}

// eventhook
if (e->type == SDL_WINDOWEVENT) {
	if (e->window.event == SDL_WINDOWEVENT_LEAVE) {
		if (e->window.windowID = HotWindowID) {
			sGuiElement* ele = pushGuiElementID(L, HotElementID);
			if (ele != NULL) {
				ele->state &= ~GuiElement_Style_Hot;
			}
			HotWindowID = 0;
			HotElementID = 0;
		}
		if (e->window.windowID = clickWindowID) {
			sGuiElement* ele = pushGuiElementID(L, clickElementID);
			if (ele != NULL) {
				ele->state &= ~GuiElement_Style_Selected;
			}
			clickWindowID = 0;
			clickElementID = 0;
		}



	}

}
else

if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN) {

	Sint32 x = -1, y = -1;

	if (e->type == SDL_MOUSEMOTION) {
		x = e->motion.x;
		y = e->motion.y;
	}
	else if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN) {
		x = e->button.x;
		y = e->button.y;
	}


	HotWindowID = 0;
	HotElementID = 0;

	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);
	lua_pushnil(L);  /* first key */
	while (lua_next(L, -2) != 0) {
		sGuiElement* ele = (sGuiElement*)lua_touserdata(L, -1);

		if (ele != NULL) {
			if (ele->parentID == e->motion.windowID) {
				SDL_Point p = { e->motion.x,e->motion.y };
				if (SDL_PointInRect(&p, &ele->pos)) {
					HotWindowID = ele->parentID;
					HotElementID = ele->ID;
					ele->state |= GuiElement_Style_Hot;

					if (e->type == SDL_MOUSEBUTTONDOWN && clickElementID == 0 && e->button.button == 1) {
						if (ele->style & BS_AUTOCHECKBOX) {
							ele->state ^= GuiElement_Style_Selected;
							printf("CLICK ELEMENT! %lld\n", ele->ID);
						}
						else {
							clickElementID = ele->ID;
							clickWindowID = ele->parentID;
							ele->state |= GuiElement_Style_Selected;
						}
					}
					else if (e->type == SDL_MOUSEBUTTONUP && clickElementID == ele->ID && e->button.button == 1) {
						printf("CLICK ELEMENT! %lld\n", ele->ID);
						clickElementID = 0;
						clickWindowID = 0;
						ele->state &= ~GuiElement_Style_Selected;
					}


				}
				else {
					ele->state &= ~GuiElement_Style_Hot;
					if (e->type == SDL_MOUSEBUTTONUP && clickElementID == ele->ID && e->button.button == 1) {
						printf("cancel click element! %lld\n", ele->ID);
						clickElementID = 0;
						clickWindowID = 0;
						ele->state &= ~GuiElement_Style_Selected;
					}
				}
			}
			else {
				ele->state &= ~GuiElement_Style_Hot;
			}
		}

		lua_pop(L, 1);
	}
	lua_pop(L, 2);




}
else

//types
#define ID_CACHE_ELEMENT "SDL.cache.element"


typedef enum {
	GuiElement_Style_none = 0,
	GuiElement_Style_Selected = 0x0001,
	GuiElement_Style_Disabled = 0x0002,
	GuiElement_Style_Hot = 0x0004,
} GuiElement_Style;

typedef struct {
	union {
		SDL_Color fore;
		SDL_Color backselected;
	};
	SDL_Color back;
} sColorPair;
typedef struct {
	sColorPair normal;
	sColorPair inactive;
	sColorPair selected;
	sColorPair hot;
}sColorTheme;

typedef struct {
	lua_Integer ID;
	SDL_Rect pos;
	SDL_Texture* texNormal;
	SDL_Texture* texInactive;
	SDL_Texture* texSelected;
	SDL_Window* parent;
	Uint32 parentID;
	SDL_Renderer* renderer;
	ControlType Type;
	int state;
	int style;
	sColorTheme ct;
	union {
		struct {
			SDL_Texture* back;
			SDL_Texture* fore;
			SDL_Texture* top;
		} tex;
	};



} sGuiElement;


#define ID_GuiElement "SDL.gui.element"
static void RequiredSize(sGuiElement* ele, int* w, int* h);
inline sGuiElement* checkGuiElement(lua_State* L, int index) {
	return (sGuiElement*)luaL_checkudata(L, index, ID_GuiElement);
}
inline sGuiElement* pushGuiElement(lua_State* L, sGuiElement* value) {
	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);
	lua_geti(L, -1, value->ID);
	lua_remove(L, -2);//remove cache-table
	return value;
}
inline sGuiElement* pushGuiElementID(lua_State* L, lua_Integer ID) {
	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);
	lua_geti(L, -1, ID);
	lua_remove(L, -2);//remove cache-table
	return (sGuiElement*)lua_touserdata(L, -1);
}
inline void removeGuiElement(lua_State* L, sGuiElement* value) {
	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);
	lua_pushnil(L);
	lua_seti(L, -2, value->ID);
	lua_pop(L, 1);
}
inline sGuiElement* CreateGuiElement(lua_State* L, ControlType type, const char* text, int style, SDL_Window* parent, sColorTheme* ct, int w, int h) {
	static lua_Integer any = 1;

	sGuiElement* ele = (sGuiElement*)lua_newuserdatauv(L, sizeof(sGuiElement), 0);
	memset((void*)ele, 0, sizeof(sGuiElement));
	luaL_setmetatable(L, ID_GuiElement);

	SDL_Renderer* ren = SDL_GetRenderer(parent);
	SDL_Surface* sur;


	sur = TTF_RenderUTF8_Blended(gSystemFont, text, ct->normal.fore);
	ele->texNormal = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);

	sur = TTF_RenderUTF8_Blended(gSystemFont, text, ct->inactive.fore);
	ele->texInactive = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);

	sur = TTF_RenderUTF8_Blended(gSystemFont, text, ct->selected.fore);
	ele->texSelected = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);

	std::string tt = text;

	ele->ID = any++;
	//ele->text = tt;
	ele->Type = type;
	ele->parent = parent;
	ele->parentID = SDL_GetWindowID(parent);
	ele->renderer = ren;
	ele->state = 0;
	ele->style = style;
	ele->ct = *ct;
	ele->pos.x = 0;
	ele->pos.y = 0;

	if (w <= 0 || h <= 0) {
		int rw, rh;
		RequiredSize(ele, &rw, &rh);
		if (w <= 0) {
			w = rw > -w ? rw : -w;
		}
		if (h <= 0) {
			h = rw > -h ? rh : -h;
		}
	}

	ele->pos.w = w;
	ele->pos.h = h;




	lua_getfield(L, LUA_REGISTRYINDEX, ID_CACHE_ELEMENT);
	lua_pushvalue(L, -2);
	lua_seti(L, -2, ele->ID);
	lua_pop(L, 1);

	SetWndProcHook(GetHWND(ele->parent), ele->parent);

	return ele;
}


inline int col_offset(int col, int offset) {
	int ret = col > 128 ? col + offset : col - offset;
	return (ret < 0 ? 0 : (ret > 255 ? 255 : ret));
}
inline int col_highlight(int col, int offset = 15) { return (col > 255 - offset ? 255 : col + offset); }
inline int col_lowlight(int col, int offset = 50) { return (col < offset ? 0 : col - offset); }

static sColorTheme defaultTheme() {
	sColorTheme ret;
	DWORD col;

	col = GetSysColor(COLOR_3DFACE);
	ret.normal.back.r = GetRValue(col);
	ret.normal.back.g = GetGValue(col);
	ret.normal.back.b = GetBValue(col);
	ret.normal.back.a = 255;
	col = GetSysColor(COLOR_BTNTEXT);
	ret.normal.fore.r = GetRValue(col);
	ret.normal.fore.g = GetGValue(col);
	ret.normal.fore.b = GetBValue(col);
	ret.normal.fore.a = 255;

	ret.selected.back.r = col_lowlight(ret.normal.back.r);
	ret.selected.back.g = col_lowlight(ret.normal.back.g);
	ret.selected.back.b = col_lowlight(ret.normal.back.b);
	ret.selected.back.a = 255;
	col = GetSysColor(COLOR_HIGHLIGHT);
	ret.selected.fore.r = GetRValue(col);
	ret.selected.fore.g = GetGValue(col);
	ret.selected.fore.b = GetBValue(col);
	ret.selected.fore.a = 255;

	ret.inactive.back.r = col_lowlight(ret.normal.back.r);
	ret.inactive.back.g = col_lowlight(ret.normal.back.g);
	ret.inactive.back.b = col_lowlight(ret.normal.back.b);
	ret.inactive.back.a = 255;
	ret.inactive.fore.r = col_lowlight(ret.normal.fore.r);
	ret.inactive.fore.g = col_lowlight(ret.normal.fore.g);
	ret.inactive.fore.b = col_lowlight(ret.normal.fore.b);
	ret.inactive.fore.a = 255;

	ret.hot.back.r = col_highlight(ret.normal.back.r);
	ret.hot.back.g = col_highlight(ret.normal.back.g);
	ret.hot.back.b = col_highlight(ret.normal.back.b);
	ret.hot.back.a = 255;
	ret.hot.backselected.r = col_highlight(ret.selected.back.r);
	ret.hot.backselected.g = col_highlight(ret.selected.back.g);
	ret.hot.backselected.b = col_highlight(ret.selected.back.b);
	ret.hot.backselected.a = 255;
	printf("col %d %d\n", ret.normal.back.r, ret.hot.back.r);
	return ret;
}
void pushColorTheme(lua_State* L, sColorTheme* ct) {
	lua_createtable(L, 0, 3);

	lua_createtable(L, 0, 2);
	pushColor(L, &ct->inactive.fore);
	lua_setfield(L, -2, "fore");
	pushColor(L, &ct->inactive.back);
	lua_setfield(L, -2, "back");
	lua_setfield(L, -2, "inactive");

	lua_createtable(L, 0, 2);
	pushColor(L, &ct->selected.fore);
	lua_setfield(L, -2, "fore");
	pushColor(L, &ct->selected.back);
	lua_setfield(L, -2, "back");
	lua_setfield(L, -2, "selected");

	lua_createtable(L, 0, 2);
	pushColor(L, &ct->normal.fore);
	lua_setfield(L, -2, "fore");
	pushColor(L, &ct->normal.back);
	lua_setfield(L, -2, "back");
	lua_setfield(L, -2, "normal");

	lua_createtable(L, 0, 2);
	pushColor(L, &ct->hot.backselected);
	lua_setfield(L, -2, "backselected");
	pushColor(L, &ct->hot.back);
	lua_setfield(L, -2, "back");
	lua_setfield(L, -2, "normal");

}
sColorTheme toColorTheme(lua_State* L, int index) {
	sColorTheme ct = defaultTheme();
	if (lua_type(L, index) != LUA_TTABLE) {
		return ct;
	}

	if (lua_getfield(L, index, "inactive") == LUA_TTABLE) {
		if (lua_getfield(L, -1, "fore") == LUA_TTABLE) {
			toColor(L, -1, &ct.inactive.fore);
		}
		if (lua_getfield(L, -1, "back") == LUA_TTABLE) {
			toColor(L, -1, &ct.inactive.back);
		}
		lua_pop(L, 2);
	}
	lua_pop(L, 1);

	if (lua_getfield(L, index, "selected") == LUA_TTABLE) {
		if (lua_getfield(L, -1, "fore") == LUA_TTABLE) {
			toColor(L, -1, &ct.selected.fore);
		}
		if (lua_getfield(L, -1, "back") == LUA_TTABLE) {
			toColor(L, -1, &ct.selected.back);
		}
		lua_pop(L, 2);
	}
	lua_pop(L, 1);

	if (lua_getfield(L, index, "normal") == LUA_TTABLE) {
		if (lua_getfield(L, -1, "fore") == LUA_TTABLE) {
			toColor(L, -1, &ct.normal.fore);
		}
		if (lua_getfield(L, -1, "back") == LUA_TTABLE) {
			toColor(L, -1, &ct.normal.back);
		}
		lua_pop(L, 2);
	}
	lua_pop(L, 1);

	if (lua_getfield(L, index, "hot") == LUA_TTABLE) {
		if (lua_getfield(L, -1, "backselected") == LUA_TTABLE) {
			toColor(L, -1, &ct.hot.backselected);
		}
		if (lua_getfield(L, -1, "back") == LUA_TTABLE) {
			toColor(L, -1, &ct.hot.back);
		}
		lua_pop(L, 2);
	}
	lua_pop(L, 1);
	return ct;
}
