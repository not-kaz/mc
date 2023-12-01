#include "block.h"

#include "cube.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include <stdlib.h>

#include <cglm/types.h>

#define DEFAULT_TEXTURE_SIZE_PX 16.0f

enum block_face {
	BLOCK_FACE_NONE = 0x0,
	BLOCK_FACE_FRONT = 0x2,
	BLOCK_FACE_BACK = 0x4,
	BLOCK_FACE_RIGHT = 0x8,
	BLOCK_FACE_LEFT = 0x10,
	BLOCK_FACE_TOP = 0x20,
	BLOCK_FACE_BOTTOM = 0x40,
	BLOCK_FACE_ALL = 0xFF,
	NUM_BLOCK_FACES = 6
};

struct block_texture_data {
	enum block_type block_type;
	struct {
		int offset_x;
		int offset_y;
	} face[NUM_BLOCK_FACES];
};

// TODO: Make this customizable, read these values from a json file.
// Consider a function that returns these values for simplicity.
struct block_texture_data texture_data[] = {
	/*     TYPE         FRONT   BACK    LEFT    RIGHT   TOP    BOTTOM */
	{BLOCK_TYPE_DIRT, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{BLOCK_TYPE_GRASS, {{1, 0}, {1, 0}, {1, 0}, {1, 0}, {2, 0}, {0, 0}}},
	{BLOCK_TYPE_COBBLE, {{3, 0}, {3, 0}, {3, 0}, {3, 0}, {3, 0}, {3, 0}}}
};

static struct mesh *block_mesh;
static unsigned int texture_atlas;

// TODO: Change incorrect variable types. We use floats where they don't make sense.

void block_build_shared_mesh(void)
{
	// HACK: Figure out a better way of handling this!
	if (block_mesh) {
		LOG("Shared block mesh already created. Creating again...");
		free(block_mesh);
	}
	block_mesh = mesh_create(cube_vertices, sizeof(cube_vertices),
		cube_elements, sizeof(cube_elements));
	if (!block_mesh) {
		LOG("Failed to create block mesh.");
		block_mesh = NULL;
		return;
	}
	mesh_assign_attr(block_mesh, "pos_attr", 3);
	mesh_assign_attr(block_mesh, "tex_coord_attr", 2);
	mesh_process_attr_layout(block_mesh);
	texture_build(&texture_atlas, "assets\\sprites.jpg");
  }

void block_init(struct block *block, int x, int y, int z, enum block_type type)
{
	if (!block) {
		return;
	}
	block->x = x;
	block->y = y;
	block->z = z;

	block->visible_faces = BLOCK_FACE_TOP;
	block->type = type;
}

void block_draw(struct block *block, unsigned int shd)
{
	// HACK: Do we need these variables? Can't we use struct fields?
	vec2 offset;
	vec2 size;
	vec3 pos;

	if (!block) {
		return;
	}
	texture_bind(&texture_atlas);
	// HACK: This is unreadable and hacky.
	size[0] = DEFAULT_TEXTURE_SIZE_PX;
	size[1] = DEFAULT_TEXTURE_SIZE_PX;
	pos[0] = (float)(block->x);
	pos[1] = (float)(block->y);
	pos[2] = (float)(block->z);
	for (int i = 0; i < NUM_BLOCK_FACES; i++) {
       	 	if (!(block->visible_faces & (1 << i))) {
         	   continue;
        	}
		// HACK: Find out how to avoid these ugly casts.
		offset[0] = (float)(texture_data[block->type].face[i].offset_x);
		offset[1] = (float)(texture_data[block->type].face[i].offset_y);
		// HACK: Pass in shader or keep local shader variable?
		shader_set_uniform(shd, "offset", offset,
			SHADER_UNIFORM_TYPE_VEC2);
		shader_set_uniform(shd, "size", size,
			SHADER_UNIFORM_TYPE_VEC2);
		shader_set_uniform(shd, "block_pos", pos,
			SHADER_UNIFORM_TYPE_VEC3);
		mesh_draw(block_mesh, 6, i * 6); // bad name for elem count arg. should be NUM_ELEM_PER_FACE etc.
	}
}
