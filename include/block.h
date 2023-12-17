#ifndef BLOCK_H
#define BLOCK_H

enum block_type {
	BLOCK_TYPE_AIR = 0,
	BLOCK_TYPE_DIRT,
	BLOCK_TYPE_GRASS,
	BLOCK_TYPE_COBBLE,
	NUM_BLOCK_TYPES
};

enum block_side {
	BLOCK_SIDE_FRONT = 0,
	BLOCK_SIDE_BACK,
	BLOCK_SIDE_LEFT,
	BLOCK_SIDE_RIGHT,
	BLOCK_SIDE_TOP,
	BLOCK_SIDE_BOTTOM,
	NUM_BLOCK_SIDE
};

struct block {
	int x;
	int y;
	int z;
	enum block_type type;
};

void block_init(struct block *block, int x, int y, int z, enum block_type type);
void block_get_sprite_offset(enum block_type type, enum block_side side,
	int *off_x, int *off_y);

#endif
