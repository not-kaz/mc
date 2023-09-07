#include "grafx.h"

#include "log.h"
#include "types.h"

#include <SDL2/SDL.h>

static struct SDL_Window *window;
static struct SDL_Renderer *renderer;

void grafx_setup(void)
{
	/* TODO: Read window size and flags from configuration file. */
	if (!(SDL_WasInit(0)) || window || renderer) {
		return;
	}
	window = SDL_CreateWindow("", 0, 0, 1024, 768, 0);
	if (!window) {
		DIE("Failed to create SDL window. %s", SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, -1, 0 );
	if (!renderer) {
		DIE("Failed to create SDL renderer. %s", SDL_GetError());
	}
}

void grafx_present_frame(void)
{
	SDL_RenderPresent(renderer);
}

void grafx_clear_frame(void)
{
	SDL_RenderClear(renderer);
}

void grafx_set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void grafx_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h)
{
	SDL_Rect rect = {x, y, w, h};

	SDL_RenderFillRect(renderer, &rect);
}

void grafx_get_window_size(int32_t *x, int32_t *y)
{
	SDL_GetWindowSize(window, x, y);
}
