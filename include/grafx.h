#ifndef GRAFX_H
#define GRAFX_H

#include "types.h"

void grafx_start(void);
void grafx_shutdown(void);
void grafx_present_framebuffer(void);
void grafx_clear_framebuffer(float r, float g, float b, float a);
void grafx_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h);
void grafx_get_window_size(int32_t *x, int32_t *y);

#endif
