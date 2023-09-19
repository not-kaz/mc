#include "cube.h"
#include "common.h"
#include "gfx.h"
#include "input.h"
#include "list.h"
#include "log.h"
#include "shader.h"
#include "texture.h"
#include "types.h"

#include <cglm/cglm.h>
#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SDL_INIT_FLAG (SDL_INIT_VIDEO)
#define IMG_INIT_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)

static void game_startup(void)
{
	if ((SDL_WasInit(SDL_INIT_FLAG) & SDL_INIT_FLAG)) {
		return;
	}
	if (SDL_Init(SDL_INIT_FLAG) != 0) {
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
	unsigned int vao, vbo;
	unsigned int shd;
	unsigned int tex;
	int ww, wh;

	UNUSED(argc);
	UNUSED(argv);
	game_startup();
	gfx_get_window_size(&ww, &wh);
	shd = shader_build("shaders\\vert.glsl", "shaders\\frag.glsl");
	texture_build(&tex, "assets\\container.jpg");
	shader_use(shd);
	texture_bind(&tex);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
		(void *)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
		(void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	while (1) {
		mat4 model, view, projection;
		glm_mat4_identity(model);
		glm_mat4_identity(view);
		glm_mat4_identity(projection);
		glm_rotate(model, ((float) SDL_GetTicks() / 1000.0f) * glm_rad(50.0f),
		           (vec3) {0.5f, 1.0f, 0.0f});
		glm_perspective(glm_rad(45.0f), ww / wh, 0.1f, 100.0f,
			projection);
		glm_translate(view, (vec3) {0.0f, 0.0f, -3.0f});
		shader_set_mat4f(shd, "model", model[0]);
		shader_set_mat4f(shd, "view", view[0]);
		shader_set_mat4f(shd, "projection", projection[0]);
		gfx_clear_framebuffer(0.3f, 0.6f, 0.9f, 1.0f);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		gfx_present_framebuffer();
		input_poll_events();
	}
	game_shutdown();
	return 0;
}
