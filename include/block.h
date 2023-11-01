#ifndef BLOCK_H
#define BLOCK_H

#include "types.h"

enum block_type {
	BLOCK_TYPE_DIRT = 0,
	BLOCK_TYPE_COBBLE,
	BLOCK_TYPE_PLANK,
	NUM_BLOCK_TYPES
};

struct block {
	float x;
	float y;
	float z;
	flag_t visible_faces;
	enum block_type type;
};

void block_init(struct block *block, float x, float y, float z, enum block_type type);
void block_build_shared_mesh(void);
void block_draw(struct block *block, unsigned int shd);

#endif
