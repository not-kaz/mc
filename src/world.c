#include "block.h"
#include "common.h"
#include "world.h"
#include "log.h"

#include <math.h>

#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 1
#define CHUNK_DEPTH 8
#define MAX_NUM_CHUNKS 512 // Temporary value for amount of chunks possible.
#define DRAW_DISTANCE 4 // TODO: Make this customizable.
#define INIT_DRAW_DISTANCE 8

enum chunk_state {
	CHUNK_STATE_UNDEFINED = 0,
	CHUNK_STATE_GENERATED,
	CHUNK_STATE_ALTERED
};

struct chunk {
	struct block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
	int x;
	int z;
	enum chunk_state state;
};

static struct chunk world[MAX_NUM_CHUNKS];

static int calc_index(vec2 pos)
{
	int tmp;

	// IMPROVE: Find a better hash, this one has has too many collisions.
	tmp = ((int)(pos[1]) * 1 + (((int)(pos[0]) * 1 + 1) / 2 ));
	tmp = tmp * tmp;
	tmp += ((int)(pos[0]) * 1);
	return (tmp % MAX_NUM_CHUNKS);
}

static struct chunk *chunk_get(vec2 pos)
{
	struct chunk *chunk;
	int idx;

	chunk = world;
	idx = abs(calc_index(pos));
	while (chunk[idx].state == CHUNK_STATE_GENERATED) {
		if (chunk[idx].x == (int)(pos[0])
				&& chunk[idx].z == (int)(pos[1])) {
			break;
		}
		idx++;
		if (idx >= MAX_NUM_CHUNKS) {
			idx = 0;
		}
	}
	return &chunk[idx];
}

static void chunk_generate(struct chunk *chunk, vec2 pos, enum block_type type)
{
	int idx;

	if (!chunk) {
		return;
	}
	idx = abs(calc_index(pos));
	while (chunk[idx].state == CHUNK_STATE_GENERATED) {
		if (chunk[idx].x == (int)(pos[0])
				&& chunk[idx].z == (int)(pos[1])) {
			return;
		}
		idx++;
		// HACK: This will hang the program if all indices are occupied.
		// 	 Will be avoided with dynamic allocation?
		if (idx >= MAX_NUM_CHUNKS) {
			idx = 0;
		}
	}
	chunk[idx].x = (int)(pos[0]);
	chunk[idx].z = (int)(pos[1]);
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				int px, pz;
				int dx, dy, dz;
				struct block *block;

				px = (int)pos[0];
				pz = (int)pos[1];
				dx = (x + px) * BLOCK_SIZE;
				dy = y * BLOCK_SIZE;
				dz = (z + pz) * BLOCK_SIZE;
				block = &chunk[idx].blocks[x][y][z];
				block_init(block, dx, dy, dz, type);

			}
		}
	}
	chunk[idx].state = CHUNK_STATE_GENERATED;
}

static void chunk_draw(struct chunk *chunk, unsigned int shd)
{
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				block_draw(&chunk->blocks[x][y][z], shd);
			}
		}
	}
}

void world_init(void)
{
	FOR_RANGE(dx, INIT_DRAW_DISTANCE) {
		FOR_RANGE(dz, INIT_DRAW_DISTANCE) {
			vec2 pos;

			pos[0] = (0.0f + (float)dx * CHUNK_WIDTH);
			pos[1] = (0.0f + (float)dz * CHUNK_DEPTH);
			chunk_generate(world, pos, 1);
		}
	}
}

void world_draw(vec2 origin, unsigned int shd)
{
	struct chunk *chunk;

	origin[0] = floorf((origin[0] + (float)(BLOCK_SIZE / 2)) / CHUNK_WIDTH)
		* CHUNK_WIDTH;
	origin[1] = floorf((origin[1] + (float)(BLOCK_SIZE / 2)) / CHUNK_DEPTH)
		* CHUNK_DEPTH;
	FOR_RANGE(dx, DRAW_DISTANCE) {
		FOR_RANGE(dz, DRAW_DISTANCE) {
			vec2 pos;

			pos[0] = (origin[0] + (float)(dx) * CHUNK_WIDTH);
			pos[1] = (origin[1] + (float)(dz) * CHUNK_DEPTH);
			chunk = chunk_get(pos);
			if (chunk->state != CHUNK_STATE_GENERATED) {
				continue;
			}
			chunk_draw(chunk, shd);
		}
	}
}
