#include "block.h"
#include "chunk.h"
#include "common.h"
#include "cube.h"
#include "log.h"
#include "mesh.h"

#include <stdlib.h>

#define INITIAL_NUM_VERTICES 10000000
#define INITIAL_NUM_ELEMENTS 10000000

// TODO: It works but needs to be tidier and it requires proper mem. allocation.

static void
init_chunk_blocks(struct chunk *chunk, int origin_x, int origin_z)
{
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				struct block *block;
				int dx, dy, dz;

				block = &chunk->blocks[x][y][z];
				dx = (x + origin_x) * BLOCK_SIZE;
				dy = y * BLOCK_SIZE;
				dz = (z + origin_z) * BLOCK_SIZE;
				//LOG("%d %d %d", dx, dy, dz);
				block_init(block, dx, dy, dz, 1);
			}
		}
	}
}

static void
add_vertices_to_chunk_mesh(struct chunk *chunk, int x, int y, int z, int face)
{

	for (int i = 0; i < 4; i++) { // 4faces
		int idx;

		idx  = i * CUBE_VERTEX_STRIDE + (face * 20); // 20 vertex pts per face
		chunk->vertices[chunk->vertex_idx++] = cube_vertices[idx] + (float)chunk->x * (float)CHUNK_WIDTH + (float)x;
		chunk->vertices[chunk->vertex_idx++] = cube_vertices[idx + 1] + (float)chunk->y * (float)CHUNK_HEIGHT + (float)y;
		chunk->vertices[chunk->vertex_idx++] = cube_vertices[idx + 2] + (float)chunk->z * (float)CHUNK_DEPTH + (float)z;
		chunk->vertices[chunk->vertex_idx++] = 0.5f;
		chunk->vertices[chunk->vertex_idx++] =  0.5f;
		//LOG("%f", ((float)i * (1.0f / 4.0f)))
	}
	chunk->elements[chunk->element_len++] = chunk->element_idx;
	chunk->elements[chunk->element_len++] = chunk->element_idx + 1;
	chunk->elements[chunk->element_len++] = chunk->element_idx + 2;
	chunk->elements[chunk->element_len++] = chunk->element_idx + 2;
	chunk->elements[chunk->element_len++] = chunk->element_idx + 3;
	chunk->elements[chunk->element_len++] = chunk->element_idx;
	chunk->element_idx += 4;
}

static void
process_chunk_block_faces(struct chunk *chunk, int x, int y, int z)
{
	if (x == 0) {
		add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_LEFT);
	} else if (x == CHUNK_WIDTH - 1) {
		add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_RIGHT);
	} else {
		if (chunk->blocks[x - 1][y][z].type == BLOCK_TYPE_AIR) {
			add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_LEFT);
		}
		if (chunk->blocks[x + 1][y][z].type == BLOCK_TYPE_AIR) {
			add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_RIGHT);
		}
	}
	if (y == 0) {
		add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_BOTTOM);
	} else if (y == CHUNK_HEIGHT - 1) {
		add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_TOP);
	} else {
		if (chunk->blocks[x][y - 1][z].type == BLOCK_TYPE_AIR) {
			add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_BOTTOM);
		}
		if (chunk->blocks[x][y + 1][z].type == BLOCK_TYPE_AIR) {
			add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_TOP);
		}
	}
	if (z == 0) {
		add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_BACK);
	} else if (z == CHUNK_DEPTH - 1) {
		add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_FRONT);
	} else {
		if (chunk->blocks[x][y][z - 1].type == BLOCK_TYPE_AIR) {
			add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_FRONT);
		}
		if (chunk->blocks[x][y][z + 1].type == BLOCK_TYPE_AIR) {
			add_vertices_to_chunk_mesh(chunk, x, y, z, CUBE_FACE_BACK);
		}
	}
}

void
chunk_init(struct chunk *chunk, int x, int z)
{
	ASSERT(chunk);
	chunk->x = x;
	chunk->y = 0;
	chunk->z = z;
	chunk->mesh = NULL;
	chunk->vertices = malloc(sizeof(float) * INITIAL_NUM_VERTICES);
	chunk->num_vertices = INITIAL_NUM_VERTICES;
	chunk->vertex_idx = 0;
	chunk->elements = malloc(sizeof(float) * INITIAL_NUM_ELEMENTS);
	chunk->num_elements = INITIAL_NUM_ELEMENTS;
	chunk->element_idx = 0;
	chunk->element_len = 0;
	chunk->state = CHUNK_STATE_INITALIZED;
	init_chunk_blocks(chunk, x, z);
}

void
chunk_build_mesh(struct chunk *chunk)
{
	ASSERT(chunk);
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				struct block *block;

				block = &chunk->blocks[x][y][z];
				process_chunk_block_faces(chunk, block->x, block->y, block->z);
			}
		}
	}
	chunk->mesh = mesh_create(chunk->vertices,
		chunk->vertex_idx * sizeof(float), chunk->elements,
		chunk->element_len * sizeof(unsigned int));
	if (!chunk->mesh) {
		LOG("HALLOL");
	}
	mesh_assign_attr(chunk->mesh, "pos_attr", 3);
	mesh_assign_attr(chunk->mesh, "tex_coord_attr", 2);
	mesh_process_attr_layout(chunk->mesh);
	LOG("VERTEX COUNT: %d", chunk->vertex_idx);
	LOG("FACE COUNT: %d", chunk->element_len);
	sizeof(chunk);
}

void
chunk_finish(struct chunk *chunk)
{
	ASSERT(chunk);
	free(chunk->mesh);
	free(chunk->vertices);
	free(chunk->elements);
	chunk->state = CHUNK_STATE_UNDEFINED;
}

void
chunk_draw(struct chunk *chunk)
{
	mesh_draw(chunk->mesh, chunk->num_elements, 0);
}
