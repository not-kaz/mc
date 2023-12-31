#ifndef GFX_H
#define GFX_H

#include "types.h"

void gfx_start(void);
void gfx_shutdown(void);
void gfx_present_framebuffer(void);
void gfx_clear_framebuffer(float r, float g, float b, float a);
void gfx_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h);
void gfx_get_window_size(int32_t *x, int32_t *y);

#endif
