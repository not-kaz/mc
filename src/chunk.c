#include "chunk.h"

#include "block.h"
#include "common.h"

#include <stdlib.h>

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

struct chunk {
	struct block blocks[CHUNK_WIDTH][CHUNK_HEIGHT];
	int origin_x;
	int origin_y;
};

struct chunk *chunk_create(int origin_x, int origin_y)
{
	struct chunk *chunk;

	UNUSED(origin_x);
	UNUSED(origin_y);
	chunk = malloc(sizeof(struct chunk));
	if (!chunk) {
		return NULL;
	}
	for (int i = 0, t = 0; i < CHUNK_WIDTH; i++, t++) {
		if (t == 2) {
			t = 0;
		}
		for (int j = 0; j < CHUNK_HEIGHT; j++) {
			block_init(&chunk->blocks[i][j],
				(float)(i) * 2.0f, 0, (float)(j) * 2.0f, t);
		}
	}
	return chunk;
}

void chunk_draw(struct chunk *chnk, unsigned int shd)
{
	for (int i = 0; i < CHUNK_WIDTH; i++) {
		for (int j = 0; j < CHUNK_HEIGHT; j++) {
			block_draw(&chnk->blocks[i][j], shd);
		}
	}
}
