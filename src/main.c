#include "common.h"
#include "grafx.h"
#include "input.h"
#include "list.h"
#include "log.h"
#include "types.h"

#include <glad/gl.h>
#include <SDL2/SDL.h>

#define SDL_INIT_FLAGS (SDL_INIT_VIDEO)

static void startup(void)
{
	if ((SDL_WasInit(SDL_INIT_FLAGS) & SDL_INIT_FLAGS)) {
		return;
	}
	if (SDL_Init(SDL_INIT_FLAGS) != 0) {
		DIE("Failed to initialize SDL. %s", SDL_GetError());
	}
	grafx_start();
}

static void shutdown(void)
{
	grafx_shutdown();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	int x, y;

	startup();
	UNUSED(argc);
	UNUSED(argv);
	startup();
	grafx_get_window_size(&x, &y);
	while (1) {
		SDL_Delay(88);
		grafx_clear_framebuffer(0.3f, 0.2f, 0.3f, 1.0f);
		grafx_present_framebuffer();
		input_poll_events();
	}
	shutdown();
	return 0;
}
