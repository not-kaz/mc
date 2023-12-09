#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

#include <stddef.h>

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256
#define CHUNK_DEPTH 16

enum chunk_state {
	CHUNK_STATE_UNDEFINED,
	CHUNK_STATE_INITALIZED,
	CHUNK_STATE_ALTERED
};

struct chunk {
	int x;
	int y;
	int z;
	struct mesh *mesh;
	float *vertices;
	size_t num_vertices;
	int vertex_idx;
	unsigned int *elements;
	size_t num_elements;
	int element_len;
	int element_idx;
	enum chunk_state state;
	struct block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
};

void chunk_init(struct chunk *chunk, int x, int z);
void chunk_build_mesh(struct chunk *chunk);
void chunk_finish(struct chunk *chunk);
void chunk_draw(struct chunk *chunk);

#endif
