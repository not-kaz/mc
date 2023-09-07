#include "common.h"
#include "grafx.h"
#include "input.h"
#include "list.h"
#include "log.h"
#include "types.h"

#include <SDL2/SDL.h>

#define SDL_INIT_FLAGS (SDL_INIT_VIDEO)

static void sdl_setup(void)
{
	if ((SDL_WasInit(SDL_INIT_FLAGS) & SDL_INIT_FLAGS)) {
		return;
	}
	if (SDL_Init(SDL_INIT_FLAGS) != 0) {
		DIE("Failed to initialize SDL. %s", SDL_GetError());
	}
}

int main(int argc, char **argv)
{
	int x, y;

	UNUSED(argc);
	UNUSED(argv);
	sdl_setup();
	grafx_setup();
	grafx_get_window_size(&x, &y);
	LOG("%d %d", x, y);
	grafx_set_draw_color(0, 0, 0, 255);
	grafx_clear_frame();
	while (1) {
		SDL_Delay(88);
		grafx_set_draw_color(0, 0, 0, 255);
		grafx_clear_frame();
		grafx_present_frame();
		input_poll_events();
	}
	SDL_Quit();
	return 0;
}
