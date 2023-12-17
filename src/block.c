#include "block.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include <stdlib.h>

#include <cglm/types.h>

#define NUM_BLOCK_SIDES 6

struct block_texture_data {
	enum block_type block_type;
	struct {
		int offset_x;
		int offset_y;
	} side[NUM_BLOCK_SIDES];
};

struct block_texture_data texture_data[] = {
	/*     TYPE         FRONT   BACK    LEFT    RIGHT   TOP    BOTTOM */
	{BLOCK_TYPE_AIR, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{BLOCK_TYPE_DIRT, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
	{BLOCK_TYPE_GRASS, {{1, 0}, {1, 0}, {1, 0}, {1, 0}, {2, 0}, {0, 0}}},
	{BLOCK_TYPE_COBBLE, {{3, 0}, {3, 0}, {3, 0}, {3, 0}, {3, 0}, {3, 0}}}
};

void
block_init(struct block *block, int x, int y, int z, enum block_type type)
{
	if (!block) {
		return;
	}
	block->x = x;
	block->y = y;
	block->z = z;
	block->type = type;
}

void
block_get_sprite_offset(enum block_type type, enum block_side side,
		int *off_x, int *off_y)
{
	*off_x = texture_data[type].side[side].offset_x;
	*off_y = texture_data[type].side[side].offset_y;
}
