#include "chunk.h"
#include "common.h"
#include "cube.h"
#include "log.h"
#include "mesh.h"
#include "shader.h"

#include <glad/gl.h>
#include <stdlib.h>
#include <cglm/types.h>

#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 8
#define CHUNK_DEPTH 8
#define CHUNK_GEOM_MEM_SIZE 1048576 // One MB worth of vertices?

struct chunk {
	int x;
	int y;
	int z;
	struct block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
	struct {
		float *vertices;
		size_t vertices_size;
		size_t num_vertices;
		uint32_t *indices;
		size_t indices_size;
		size_t num_indices;
		uint32_t index;
	} geometry;
	struct mesh *mesh;
};

static void
add_block_face_to_geometry(struct chunk *chunk, int x, int y, int z, int face)
{
	int ofx;
	int ofy;

	block_get_sprite_offset(chunk->blocks[x][y][z].type, face, &ofx, &ofy);
	for (int i = 0; i < CUBE_NUM_VERTS_PER_FACE; i++) {
		int idx;

		idx = (i * CUBE_NUM_COMPS_PER_VERT)
			+ (face * CUBE_NUM_COMPS_PER_FACE);
		chunk->geometry.vertices[chunk->geometry.num_vertices++] =
			cube_vertices[idx] + (float)chunk->x
			* (float)CHUNK_WIDTH + (float)x;
		chunk->geometry.vertices[chunk->geometry.num_vertices++] =
			cube_vertices[idx + 1] + (float)chunk->y
			* (float)CHUNK_HEIGHT + (float)y;
		chunk->geometry.vertices[chunk->geometry.num_vertices++] =
			cube_vertices[idx + 2] + (float)chunk->z
			* (float)CHUNK_DEPTH + (float)z;
		chunk->geometry.vertices[chunk->geometry.num_vertices++] =
			cube_vertices[idx + 3] + (float)ofx;
		chunk->geometry.vertices[chunk->geometry.num_vertices++] =
			cube_vertices[idx + 4] + (float)ofy;
	}
	chunk->geometry.indices[chunk->geometry.num_indices++] =
		chunk->geometry.index;
	chunk->geometry.indices[chunk->geometry.num_indices++] =
		chunk->geometry.index + 1;
	chunk->geometry.indices[chunk->geometry.num_indices++] =
		chunk->geometry.index + 2;
	chunk->geometry.indices[chunk->geometry.num_indices++] =
		chunk->geometry.index + 2;
	chunk->geometry.indices[chunk->geometry.num_indices++] =
		chunk->geometry.index + 3;
	chunk->geometry.indices[chunk->geometry.num_indices++] =
		chunk->geometry.index;
	chunk->geometry.index += 4;
}

static void
construct_block_geometry(struct chunk *chunk, int x, int y, int z)
{
	 /// TERRIBLE CODE BUT THIS IS JUST PLACEHOLDER TO SEE IF IT WORKS.
	// TODO: This code is a hack, rewrite it!
	int left = 0;
	int right = 0;

	if (chunk->blocks[x][y][z].type == BLOCK_TYPE_AIR) {
		return;
	}
	if (x == 0) {
		add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_LEFT);
		left = 1;
	}
	if (x == CHUNK_WIDTH - 1) {
		add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_RIGHT);
		right = 1;
	}
	if (!left) {
		if (chunk->blocks[x - 1][y][z].type == BLOCK_TYPE_AIR) {
			add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_LEFT);
		}
	}
	if (!right) {
		if (chunk->blocks[x + 1][y][z].type == BLOCK_TYPE_AIR) {
			add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_RIGHT);
		}
	}
	left = 0;
	right = 0;
	if (y == 0) {
		add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_BOTTOM);
		left = 1;
	}
	if (y == CHUNK_HEIGHT - 1) {
		add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_TOP);
		right = 1;
	}
	if (!left) {
		if (chunk->blocks[x][y - 1][z].type == BLOCK_TYPE_AIR) {
			add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_BOTTOM);
		}
	}
	if (!right) {
		if (chunk->blocks[x][y + 1][z].type == BLOCK_TYPE_AIR) {
			add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_TOP);
		}
	}
	left = 0;
	right = 0;
	if (z == 0) {
		add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_BACK);
		left = 1;

	}
	if (z == CHUNK_DEPTH - 1) {
		add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_FRONT);
		right = 1;

	}
	if (!left) {
		if (chunk->blocks[x][y][z - 1].type == BLOCK_TYPE_AIR) {
			add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_BACK);
		}
	}
	if (!right) {
		if (chunk->blocks[x][y][z + 1].type == BLOCK_TYPE_AIR) {
			add_block_face_to_geometry(chunk, x, y, z, BLOCK_SIDE_FRONT);
		}
	}
}

struct chunk *
chunk_create(int pos_x, int pos_z)
{
	struct chunk *chunk;

	chunk = malloc(sizeof(struct chunk));
	if (!chunk) {
		return NULL;
	}
	chunk->x = pos_x;
	chunk->y = 0;
	chunk->z = pos_z;
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				struct block *block;
				int dx, dz;

				block = &chunk->blocks[x][y][z];
				dx = (x + chunk->x);
				dz = (z + chunk->z);
				block_init(block, dx, y, dz, rand() % 4);
			}
		}
	}
	chunk->geometry.vertices = malloc(sizeof(float) * CHUNK_GEOM_MEM_SIZE);
	if (!chunk->geometry.vertices) {
		return NULL;
	}
	chunk->geometry.vertices_size = sizeof(float) * CHUNK_GEOM_MEM_SIZE;
	chunk->geometry.num_vertices = 0;
	chunk->geometry.indices = malloc(sizeof(uint32_t) * CHUNK_GEOM_MEM_SIZE);
	if (!chunk->geometry.indices) {
		return NULL;
	}
	chunk->geometry.indices_size = sizeof(uint32_t) * CHUNK_GEOM_MEM_SIZE;
	chunk->geometry.num_indices = 0;
	chunk->geometry.index = 0;
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				struct block *block;

				block = &chunk->blocks[x][y][z];
				construct_block_geometry(chunk, block->x,
					block->y, block->z);
			}
		}
	}
	chunk->mesh = mesh_create(chunk->geometry.vertices,
		chunk->geometry.vertices_size, chunk->geometry.indices,
		chunk->geometry.indices_size);
	mesh_assign_attr(chunk->mesh, "pos_attr", 3);
	mesh_assign_attr(chunk->mesh, "tex_coord_attr", 2);
	mesh_process_attr_layout(chunk->mesh);
	LOG("%u", chunk->geometry.vertices_size);
	return chunk;
}

void
chunk_destroy(struct chunk *chunk)
{
	ASSERT(chunk);
	free(chunk->geometry.vertices);
	free(chunk->geometry.indices);
	mesh_destroy(chunk->mesh);
	free(chunk);
}

void
chunk_draw(struct chunk *chunk)
{
	if (!chunk) {
		return;
	}
	mesh_draw(chunk->mesh, true);
}
