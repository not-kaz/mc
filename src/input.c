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

static int32_t mouse_x_rel;
static int32_t mouse_y_rel;
static const uint8_t *keyboard_state;

void input_poll_events(void)
{
	SDL_Event event;

	keyboard_state = SDL_GetKeyboardState(NULL);
	mouse_x_rel = 0;
	mouse_y_rel = 0;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			DIE("Quit even called. Shutting down...");
		}
		if (event.type == SDL_MOUSEMOTION) {
			mouse_x_rel = event.motion.xrel;
			mouse_y_rel = event.motion.yrel;
		}
	}
}

bool input_is_keybind_pressed(enum input_keybind_tag bind)
{
	return keyboard_state[keybinds[bind].scancode] ? true : false;
}

void input_get_relative_mouse_position(int32_t *x, int32_t *y)
{
	(*x) = mouse_x_rel;
	(*y) = mouse_y_rel;
}
