#include "input.h"

#include "log.h"

#include <SDL2/SDL.h>

void input_poll_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			DIE("Quit even called. Shutting down...");
		}
	}
}
