#include "gfx.h"

#include "log.h"
#include "types.h"

#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SAFE_MODE_WIN_WIDTH 800
#define SAFE_MODE_WIN_HEIGHT 600

/* TODO: Add a bit-wise flag that keeps track of graphics state. *
 *	 Fullscreen, safe mode etc...                            */
static struct {
	struct SDL_Window *window;
	struct SDL_GLContext *gl_ctx;
	int is_safe_mode;
} gfx_ctx = {NULL, NULL, 1};

static struct {
	SDL_DisplayMode *modes;
	int num_modes;
} display = {NULL, 0};

static void get_display_modes(void)
{
	display.num_modes = SDL_GetNumDisplayModes(0);
	if (display.num_modes < 1) {
		DIE("Failed to read display modes w/ SDL. %s", SDL_GetError());
	}
	display.modes = malloc(sizeof(SDL_DisplayMode)
		* (size_t)(display.num_modes));
	if (!display.modes) {
		DIE("Failed to allocate memory for display data.");
	}
	LOG("=== DETECTED DISPLAY MODES ===");
	for (int i = 0; i < display.num_modes; i++) {
		uint32_t fmt;

		if (SDL_GetDisplayMode(0, i, &display.modes[i]) != 0) {
			DIE("Failed to read display data. %s", SDL_GetError());
		}
		fmt = display.modes[i].format;
		LOG("#%d: %dx%d %d %u %s", i, display.modes[i].w,
			display.modes[i].h, display.modes[i].refresh_rate,
			SDL_BITSPERPIXEL(fmt), SDL_GetPixelFormatName(fmt));
	}
}

void gfx_start(void)
{
	int ww, wh;
	unsigned int wf;

	if (gfx_ctx.window || gfx_ctx.gl_ctx) {
		return;
	}
	ww = SAFE_MODE_WIN_WIDTH;
	wh = SAFE_MODE_WIN_HEIGHT;
	wf = SDL_WINDOW_OPENGL;
	get_display_modes(); // TODO: Find a better name for this function.
	if (!gfx_ctx.is_safe_mode) {
		ww = display.modes[display.num_modes - 1].w;
		wh = display.modes[display.num_modes - 1].h;
		wf |= SDL_WINDOW_FULLSCREEN;
	}
	gfx_ctx.window = SDL_CreateWindow("TITLE", 0, 0, ww, wh, wf);
	if (!gfx_ctx.window) {
		DIE("Failed to create SDL window. %s", SDL_GetError());
	}
	gfx_ctx.gl_ctx = SDL_GL_CreateContext(gfx_ctx.window);
	if (!gfx_ctx.gl_ctx) {
		DIE("Failed to create SDL GL context. %s", SDL_GetError());
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	// TODO: Make SDL_SetSwapInterval() optional and read value from config.
	SDL_GL_SetSwapInterval(1);
	if (!gladLoadGL((GLADloadfunc)(SDL_GL_GetProcAddress))) {
		DIE("Failed to start 'glad' OpenGL loader.");
	}
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, ww, wh);
}

void gfx_shutdown(void)
{
	free(display.modes);
	SDL_GL_DeleteContext(gfx_ctx.gl_ctx);
	SDL_DestroyWindow(gfx_ctx.window);
}

void gfx_present_framebuffer(void)
{
	SDL_GL_SwapWindow(gfx_ctx.window);
}

void gfx_clear_framebuffer(float r, float g, float b, float a)
{
	// REVIEW: Any drawback to combining these two operations into one?
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

void gfx_get_window_size(int32_t *x, int32_t *y)
{
	SDL_GetWindowSize(gfx_ctx.window, x, y);
}
