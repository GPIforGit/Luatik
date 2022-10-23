#pragma once

#define COLOR_NUM(r,g,b) (((r)&0xFF) | ((g)&0xFF)<<8| ((b)&0xFF)<<16)
#define COLOR_RED(c) ((c) & 0xff)
#define COLOR_GREEN(c)  ( ((c)>>8) & 0xff )
#define COLOR_BLUE(c)  ( ((c)>>16) & 0xff )

void getpixel(SDL_Surface* surface, int x, int y, Uint8* r, Uint8* g, Uint8* b)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)surface->pixels + (size_t)y * (size_t)surface->pitch + (size_t)x * (size_t)bpp;
	Uint32 pixel;

	switch (bpp)
	{
	case 1:
		pixel = *p;
		break;

	case 2:
		pixel = *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixel = p[0] << 16 | p[1] << 8 | p[2];
		else
			pixel = p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		pixel = *(Uint32*)p;
		break;

	default:
		pixel = 0;       /* shouldn't happen, but avoids warnings */
	}

	SDL_GetRGB(pixel, surface->format, r, g, b);
	return;
}

typedef struct {
	int hit;
	int col;
} sHitTestColor;

const sHitTestColor HitTestColor[] = {

	{SDL_HITTEST_NORMAL, COLOR_NUM(0x00, 0x00, 0x00)},

	{SDL_HITTEST_DRAGGABLE, COLOR_NUM(0xFF, 0xFF, 0xFF)},

	{SDL_HITTEST_RESIZE_TOPLEFT, COLOR_NUM(0xff, 0x00, 0x00)},
	{SDL_HITTEST_RESIZE_TOP, COLOR_NUM(0x00, 0xff, 0x00)},
	{SDL_HITTEST_RESIZE_TOPRIGHT, COLOR_NUM(0x00, 0x00, 0xff)},

	{SDL_HITTEST_RESIZE_LEFT, COLOR_NUM(0xff, 0xff, 0x00)},
	{SDL_HITTEST_RESIZE_RIGHT, COLOR_NUM(0xff, 0x00, 0xff)},

	{SDL_HITTEST_RESIZE_BOTTOMLEFT, COLOR_NUM(0x00, 0xff, 0xff)},
	{SDL_HITTEST_RESIZE_BOTTOM, COLOR_NUM(0xff, 0x7f, 0x00)},
	{SDL_HITTEST_RESIZE_BOTTOMRIGHT, COLOR_NUM(0x7f, 0x00, 0xff)},

	{-1,-1}
};

static int distance2(int c1, int c2) {
	int r = COLOR_RED(c1) - COLOR_RED(c2);
	int g = COLOR_GREEN(c1) - COLOR_GREEN(c2);
	int b = COLOR_BLUE(c1) - COLOR_BLUE(c2);
	return r * r + g * g + b * b;
}

extern "C" SDL_HitTestResult HitTest(SDL_Window * win, const SDL_Point * area, void* data) {
	SDL_Surface* sur = (SDL_Surface*)data;
	Uint8 r, g, b;

	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	int x = area->x * sur->w / w;
	int y = area->y * sur->h / h;

	x = x < 0 ? 0 : (x >= sur->w ? sur->w - 1: x);
	y = y < 0 ? 0 : (y >= sur->h ? sur->h - 1: y);

	getpixel(sur, x, y, &r, &g, &b);
	int col = COLOR_NUM(r, g, b);

	SDL_HitTestResult ret = SDL_HITTEST_NORMAL;
	int retdist = 255 * 255 + 255 * 255 + 255 * 255;

	for (const sHitTestColor* hc = HitTestColor; hc->hit >= 0; hc++) {
		int dist = distance2(hc->col, col);
		if (dist < retdist) {
			retdist = dist;
			ret = (SDL_HitTestResult)hc->hit;
		}
	}
	return ret;
}