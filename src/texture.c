#include "texture.h"

#include "log.h"

#include <glad/gl.h>
#include <SDL2/SDL_image.h>

/* REVIEW: To keep it simple, we should use a single texture atlas.  *
 * Alternatively, we must keep track of every single texture object. */

static void assign_gl_tex_params(unsigned int *id, SDL_Surface *data)
{
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, (*id));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->w, data->h, 0, GL_RGB,
		GL_UNSIGNED_BYTE, data->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void texture_build(unsigned int *tex, const char *img_path)
{
	SDL_Surface *data;

	data = IMG_Load(img_path);
	if (!data) {
		DIE("Failed to load image from path: %s", img_path);
	}
	assign_gl_tex_params(tex, data);
	SDL_FreeSurface(data);
}

void texture_bind(unsigned int *tex)
{
	glActiveTexture(GL_TEXTURE0); // REVIEW: What is GL_TEXTURE0?
	glBindTexture(GL_TEXTURE_2D, (*tex));
}
