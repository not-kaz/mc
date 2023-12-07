#include "block.h"
#include "camera.h"
#include "common.h"
#include "gfx.h"
#include "input.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "types.h"
#include "world.h"

#include <cglm/cglm.h>
#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SDL_INIT_FLAG (SDL_INIT_VIDEO)
#define IMG_INIT_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)

/* TODO: Replace CGLM with a light alternative or make a minimal math header. */

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
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);
}

static void game_shutdown(void)
{
	gfx_shutdown();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char **argv)
{
	unsigned int shd;
	int ww, wh;
	struct camera *cam;
	vec2 pp;

	UNUSED(argc);
	UNUSED(argv);
	game_startup();
	gfx_get_window_size(&ww, &wh);
	shd = shader_build("shaders\\block_colored_vert.glsl", "shaders\\block_colored_frag.glsl");
	shader_use(shd);
	block_build_shared_mesh();
	cam = camera_create();
	world_init();
	while (1) {
		mat4 model, view, projection;

		glm_mat4_identity(model);
		glm_mat4_identity(projection);
		glm_mat4_identity(view);
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glm_perspective(glm_rad(45.0f), (float)(ww) / (float)(wh), 0.1f,
			100.0f, projection);
		camera_calc_view_matrix(cam, view);
		shader_set_uniform(shd, "model", model[0],
			SHADER_UNIFORM_TYPE_MAT4);
		shader_set_uniform(shd, "view", view[0],
			SHADER_UNIFORM_TYPE_MAT4);
		shader_set_uniform(shd, "projection", projection[0],
			SHADER_UNIFORM_TYPE_MAT4);
		input_poll_events();
		camera_update(cam);
		camera_get_position(cam, pp);
		gfx_clear_framebuffer(0.2f, 0.5f, 0.5f, 1.0f);
		world_draw(pp, shd);
		gfx_present_framebuffer();
	}
	game_shutdown();
	return 0;
}
