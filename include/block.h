#ifndef BLOCK_H
#define BLOCK_H

#include "types.h"

#define BLOCK_SIZE 1 // Size of a block in world unit terms.

enum block_type {
	BLOCK_TYPE_DIRT = 0,
	BLOCK_TYPE_GRASS,
	BLOCK_TYPE_COBBLE,
	NUM_BLOCK_TYPES
};

struct block {
	int x;
	int y;
	int z;
	flag_t visible_faces;
	enum block_type type;
};

void block_init(struct block *block, int x, int y, int z, enum block_type type);
void block_build_shared_mesh(void);
void block_draw(struct block *block, unsigned int shd);

#endif
