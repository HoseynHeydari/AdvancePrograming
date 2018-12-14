#include <iostream>
#include "rsdl.h"

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}
 
void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:
 
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;
 
    while (x >= y)
    {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);
 
        if (x != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
 
        if (y != 0)
        {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
 
        if (x != 0 && y != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
    // Note that there is more to altering the bitrate of this 
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;
 
    double r = (double)radius;
 
    for (double dy = 1; dy <= r; dy += 1.0)
    {
        // This loop is unrolled a bit, only iterating through half of the
        // height of the circle.  The result is used to draw a scan line and
        // its mirror image below it.
 
        // The following formula has been simplified from our original.  We
        // are using half of the width of the circle because we are provided
        // with a center and we need left/right coordinates.
 
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = cx - dx;
 
        // Grab a pointer to the left-most pixel for each half of the circle
        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
 
        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }
    }
}

int window::instance_count = 0;

void window::init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw string("SDL could not initialize! SDL_Error: ") + SDL_GetError();
}

window::window(int width, int height)
{
	if (instance_count == 0)
		init();
	instance_count++;
	
	win = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
	if (win == NULL)
		throw string("Window could not be created! SDL_Error: ") + SDL_GetError();

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	surface = SDL_GetWindowSurface(win);
}

window::~window()
{
	SDL_DestroyWindow(win);
	instance_count--;
	if (instance_count == 0)
		SDL_Quit();
}

void window::set_color(RGB color)
{
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
}

void window::draw_point(int x, int y, RGB color)
{
	set_color(color);
	SDL_RenderDrawPoint(renderer, x, y);
	SDL_RenderPresent(renderer);
}

void window::draw_line(int x1, int y1, int x2, int y2, RGB color)
{
	set_color(color);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderPresent(renderer);
}

void window::draw_rect(int x, int y, int w, int h, RGB color)
{
	SDL_Rect r = { x, y, w, h };
	set_color(color);
	SDL_RenderDrawRect(renderer, &r);
	SDL_RenderPresent(renderer);
}

void window::fill_rect(int x, int y, int w, int h, RGB color)
{
	SDL_Rect r = { x, y, w, h };
	set_color(color);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);
}

void window::draw_bmp(string filename, int x, int y)
{
	SDL_Surface* res = SDL_LoadBMP(filename.c_str());
	SDL_Rect r = {x, y, 0, 0};
	SDL_BlitSurface(res, NULL, surface, &r);
	SDL_UpdateWindowSurface(win);
}

void window::draw_transparent_bmp(string filename, int x, int y, RGB color)
{
	SDL_Surface* res = SDL_LoadBMP(filename.c_str());
	Uint32 color_uint = SDL_MapRGB(res->format, color.red, color.green, color.blue);
	SDL_SetColorKey(res, SDL_TRUE, color_uint);
	SDL_Rect r = {x, y, 0, 0};
	SDL_BlitSurface(res, NULL, surface, &r);
	SDL_UpdateWindowSurface(win);
}

void window::draw_circle(int x, int y, int r, RGB color)
{
	Uint32 c = 0xff000000 + ((color.red % 0x100) << 16) + ((color.green % 0x100) << 8) + (color.blue % 0x100);
	::draw_circle(surface, x, y, r, c);
	SDL_UpdateWindowSurface(win);
}

void window::fill_circle(int x, int y, int r, RGB color)
{
	Uint32 c = 0xff000000 + ((color.red % 0x100) << 16) + ((color.green % 0x100) << 8) + (color.blue % 0x100);
	::fill_circle(surface, x, y, r, c);
	SDL_UpdateWindowSurface(win);
}
