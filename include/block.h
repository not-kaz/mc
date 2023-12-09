#ifndef BLOCK_H
#define BLOCK_H

#include "types.h"

#define BLOCK_SIZE 1 // Size of a block in world unit terms.

enum block_type {
	BLOCK_TYPE_AIR = 0,
	BLOCK_TYPE_DIRT,
	BLOCK_TYPE_GRASS,
	BLOCK_TYPE_COBBLE,
	NUM_BLOCK_TYPES
};

enum block_face {
	BLOCK_FACE_NONE = 0,
	BLOCK_FACE_FRONT = 1 << 0,  // 1
	BLOCK_FACE_BACK = 1 << 1,  // 2
	BLOCK_FACE_LEFT = 1 << 2,  // 4
	BLOCK_FACE_RIGHT = 1 << 3,  // 8
	BLOCK_FACE_TOP = 1 << 4,  // 16
	BLOCK_FACE_BOTTOM = 1 << 5,  // 32
	BLOCK_FACE_ALL = (1 << 6) - 1,
	NUM_BLOCK_FACES = 6
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
void block_set_visible_face(struct block *block, int flag);

#endif
