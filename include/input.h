#ifndef INPUT_H
#define INPUT_H

#include "types.h"

enum input_keybind_tag {
	KEYBIND_FORWARD = 0,
	KEYBIND_BACKWARD,
	KEYBIND_LEFT,
	KEYBIND_RIGHT,
	KEYBIND_JUMP,
	KEYBIND_CROUCH,
	NUM_KEYBINDS
};

void input_poll_events(void);
bool input_is_keybind_pressed(enum input_keybind_tag bind);

#endif
