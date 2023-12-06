#include "block.h"
#include "common.h"
#include "world.h"
#include "log.h"

#include <math.h>

#define CHUNK_WIDTH 1
#define CHUNK_HEIGHT 1
#define CHUNK_DEPTH 1
#define MAX_NUM_CHUNKS 1024 // Temporary value for amount of chunks possible.
#define DRAW_DISTANCE 1 // TODO: Make this customizable. Radius from center chunk in all directionds.
#define INIT_DRAW_DISTANCE 1 // 1 Center row/col + X on each side (1 + X * 2)

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
static const float HALF_BLOCK = (BLOCK_SIZE / 2.0f);

static int calc_index(ivec2 pos)
{
	int tmp;

	// IMPROVE: Find a better hash, this one has has too many collisions.
	tmp = (pos[1] * 1 + ((pos[0] * 1 + 1) / 2 ));
	tmp = tmp * tmp;
	tmp += (pos[0] * 1);
	return (tmp % MAX_NUM_CHUNKS);
}

static struct chunk *find_chunk(ivec2 pos)
{
	struct chunk *chunk;
	int idx;

	chunk = world;
	idx = abs(calc_index(pos));
	while (chunk[idx].state == CHUNK_STATE_GENERATED) {
		if (chunk[idx].x == pos[0] && chunk[idx].z == pos[1]) {
			break;
		}
		idx++;
		if (idx >= MAX_NUM_CHUNKS) {
			idx = 0;
		}
	}
	return &chunk[idx];
}

static void generate_chunk(ivec2 pos, enum block_type type)
{
	int idx;

	idx = abs(calc_index(pos));
	while (world[idx].state == CHUNK_STATE_GENERATED) {
		if (world[idx].x == pos[0] && world[idx].z == pos[1]) {
			return;
		}
		idx++;
		// HACK: This will hang the program if all indices are occupied.
		// 	 Will be avoided with dynamic allocation?
		if (idx >= MAX_NUM_CHUNKS) {
			idx = 0;
		}
	}
	world[idx].x = pos[0];
	world[idx].z = pos[1];
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				int dx, dy, dz;
				struct block *block;
				int faces;

				dx = (x + pos[0]) * BLOCK_SIZE;
				dy = y * BLOCK_SIZE;
				dz = (z + pos[1]) * BLOCK_SIZE;
				block = &world[idx].blocks[x][y][z];
				faces = BLOCK_FACE_TOP | BLOCK_FACE_BOTTOM;
				// TODO: Check neighbour blocks for face culling.
				// Now we only check for chunk edges as test.
				// We should do this on second pass after init? After all chunks were generated.
				// This will allow us to compare edge blocks to the neighbouring chunk aswell.
				if ((z == CHUNK_DEPTH - 1)) {
					faces = faces | BLOCK_FACE_FRONT;
				}
				if (z == 0) {
					faces = faces | BLOCK_FACE_BACK;
				}
				if (x == 0) {
					faces = faces | BLOCK_FACE_LEFT;
				}
				if (x == CHUNK_WIDTH - 1) {
					faces = faces | BLOCK_FACE_RIGHT;
				}
				block_init(block, dx, dy, dz, type);
				block_set_visible_face(block, faces);
			}
		}
	}
	world[idx].state = CHUNK_STATE_GENERATED;
}

static void draw_chunk(struct chunk *chunk, unsigned int shd)
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
	for (int dx = -INIT_DRAW_DISTANCE; dx <= INIT_DRAW_DISTANCE; dx++) {
		for (int dz = -INIT_DRAW_DISTANCE; dz <= INIT_DRAW_DISTANCE; dz++) {
			ivec2 pos;

			pos[0] = (dx * CHUNK_WIDTH);
			pos[1] = (dz * CHUNK_DEPTH);
			generate_chunk(pos, 1);
		}
	}
}

void world_draw(vec2 origin, unsigned int shd)
{
	int x;
	int y;

	x = (int)(floorf((origin[0] + HALF_BLOCK) / CHUNK_WIDTH) * CHUNK_WIDTH);
	y = (int)(floorf((origin[1] + HALF_BLOCK) / CHUNK_DEPTH) * CHUNK_DEPTH);
	for (int dx = -DRAW_DISTANCE; dx <= DRAW_DISTANCE; dx++) {
		for (int dz = -DRAW_DISTANCE; dz <= DRAW_DISTANCE; dz++) {
			ivec2 pos;
			struct chunk *chunk;

			pos[0] = (x + dx * CHUNK_WIDTH);
			pos[1] = (y + dz * CHUNK_DEPTH);
			chunk = find_chunk(pos);
			if (chunk->state != CHUNK_STATE_GENERATED) {
				continue;
			}
			draw_chunk(chunk, shd);
		}
	}
}
