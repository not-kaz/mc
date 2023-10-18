#include "input.h"

#include "log.h"

#include <SDL2/SDL.h>

struct keybind {
	enum input_keybind_tag bind;
	int scancode;
};

/* Keybinds need to be sorted the same as the keybind enums in the header. */
static struct keybind keybinds[NUM_KEYBINDS] = {
	{KEYBIND_FORWARD, SDL_SCANCODE_W},
	{KEYBIND_BACKWARD, SDL_SCANCODE_S},
	{KEYBIND_LEFT, SDL_SCANCODE_A},
	{KEYBIND_RIGHT, SDL_SCANCODE_D},
	{KEYBIND_JUMP, SDL_SCANCODE_SPACE},
	{KEYBIND_CROUCH, SDL_SCANCODE_LCTRL}
};

static const uint8_t *keyboard_state;

void input_poll_events(void)
{
	SDL_Event event;

	keyboard_state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			DIE("Quit even called. Shutting down...");
		}
	}
}

// HACKME: Use a ternary if statement to return true/false bool instead of u8.
bool input_is_keybind_pressed(enum input_keybind_tag keybind)
{
	return keyboard_state[keybinds[keybind].scancode] ? true : false;
}
