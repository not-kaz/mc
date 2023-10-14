#include "input.h"

#include "log.h"

#include <SDL2/SDL.h>

void input_poll_events(const uint8_t **keystates)
{
	SDL_Event event;

	(*keystates) = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			DIE("Quit even called. Shutting down...");
		}
	}
}
