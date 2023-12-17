#include "camera.h"
#include "chunk.h"
#include "common.h"
#include "gfx.h"
#include "input.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "types.h"

#include <cglm/cglm.h>
#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define SDL_INIT_FLAG (SDL_INIT_VIDEO)
#define IMG_INIT_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)

// TODO: Replace CGLM with a lightweight alternative. It takes too long to comp.

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
	int ww;
	int wh;
	struct camera *cam;
	struct chunk *chunk;
	vec2 pp;
	unsigned int texture_atlas;

	srand(time(NULL));
	UNUSED(argc);
	UNUSED(argv);
	game_startup();
	gfx_get_window_size(&ww, &wh);
	shd = shader_build("shaders\\block_textured_vert.glsl", "shaders\\block_textured_frag.glsl");
	shader_use(shd);
	//block_build_shared_mesh();
	cam = camera_create();
	chunk = chunk_create(0, 0);
	texture_build(&texture_atlas, "assets\\sprites.jpg");
	texture_bind(&texture_atlas);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	while (1) {
		mat4 model;
		mat4 view;
		mat4 projection;

		glm_mat4_identity(model);
		glm_mat4_identity(projection);
		glm_mat4_identity(view);
		glm_perspective(glm_rad(45.0f), (float)(ww) / (float)(wh), 0.1f,
			1000.0f, projection);
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
		gfx_clear_framebuffer(0.2f, 0.2f, 0.2f, 1.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		chunk_draw(chunk);
		gfx_present_framebuffer();
	}
	game_shutdown();
	return 0;
}
