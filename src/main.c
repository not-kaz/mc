#include "common.h"
#include "gfx.h"
#include "input.h"
#include "list.h"
#include "log.h"
#include "types.h"

#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SDL_INIT_FLAG (SDL_INIT_VIDEO)
#define IMG_INIT_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)

static void game_startup(void)
{
	if ((SDL_WasInit(SDL_INIT_FLAGS) & SDL_INIT_FLAGS)) {
		return;
	}
	if (SDL_Init(SDL_INIT_FLAGS) != 0) {
		DIE("Failed to initialize SDL. %s", SDL_GetError());
	}
	if (IMG_Init(IMG_INIT_FLAG) != IMG_INIT_FLAG) {
		DIE("Failed to initialize SDL image lib. %s", IMG_GetError());
	}
	gfx_start();
}

static void game_shutdown(void)
{
	gfx_shutdown();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	UNUSED(argc);
	UNUSED(argv);
	game_startup();
	while (1) {
		SDL_Delay(88);
		gfx_clear_framebuffer(0.3f, 0.2f, 0.3f, 1.0f);
		gfx_present_framebuffer();
		input_poll_events();
	}
	game_shutdown();
	return 0;
}
