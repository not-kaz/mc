#ifndef GRAFX_H
#define GRAFX_H

#include "types.h"

void grafx_setup(void);
void grafx_present_frame(void);
void grafx_clear_frame(void);
void grafx_set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void grafx_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h);
void grafx_get_window_size(int32_t *x, int32_t *y);

#endif
