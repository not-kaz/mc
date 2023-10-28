#include "mesh.h"

#include "common.h"
#include "log.h"

#include <stdlib.h>

#include <glad/gl.h>

#define MAX_NUM_BUFFER_ATTRIBUTES 32

struct vertex_attribute {
	const char *name;
	int offset;
	int num_comps;
};

struct vertex_buffer {
	float *data;
	size_t size;
	int vert_count;
	struct vertex_attribute attrs[MAX_NUM_BUFFER_ATTRIBUTES];
	int stride;
	unsigned int attr_idx;
	unsigned int id;
};

struct index_buffer {
	unsigned int *data;
	size_t size;
	int elem_count;
	unsigned int id;
};

struct mesh {
	struct vertex_buffer vert_buf;
	struct index_buffer idx_buf;
	unsigned int gl_id;
};

static void setup_gl_buffers(struct mesh *mesh)
{
	glGenVertexArrays(1, &mesh->gl_id);
	glGenBuffers(1, &mesh->vert_buf.id);
	glGenBuffers(1, &mesh->idx_buf.id);
	glBindVertexArray(mesh->gl_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vert_buf.id);
   	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mesh->vert_buf.size),
   		mesh->vert_buf.data, GL_STATIC_DRAW);
   	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->idx_buf.id);
   	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(mesh->idx_buf.size),
   		mesh->idx_buf.data, GL_STATIC_DRAW);
}

struct mesh *mesh_create(float *vertices, size_t vertices_size,
		unsigned int *indices, size_t indices_size)
{
	struct mesh *mesh;

	if (!vertices || !vertices_size || !indices || !indices_size) {
		return NULL;
	}
	mesh = malloc(sizeof(struct mesh));
	if (!mesh) {
		return NULL;
	}
	mesh->vert_buf.data = vertices;
	mesh->vert_buf.size = vertices_size;
	mesh->vert_buf.vert_count = (int)((vertices_size / sizeof(float)));
	mesh->vert_buf.stride = 0;
	mesh->vert_buf.id = 0;
	mesh->idx_buf.data = indices;
	mesh->idx_buf.size = indices_size;
	mesh->idx_buf.elem_count = (int)((indices_size / sizeof(unsigned int)));
	mesh->idx_buf.id = 0;
	for (int i = 0; i < MAX_NUM_vert_buf_ATTRIBUTES; i++) {
		mesh->vert_buf.attrs[i].name = NULL;
		mesh->vert_buf.attrs[i].offset = 0;
		mesh->vert_buf.attrs[i].num_comps = 0;
	}
	setup_gl_buffers(mesh);
	return mesh;
}

void mesh_destroy(struct mesh *mesh)
{
	free(mesh);
}

void mesh_assign_attr(struct mesh *mesh, const char *name, int num_comps)
{
	if (!mesh || !name || !num_comps) {
		return;
	}
	mesh->vert_buf.attrs[mesh->vert_buf.attr_idx].name = name;
	mesh->vert_buf.attrs[mesh->vert_buf.attr_idx].num_comps = num_comps;
	mesh->vert_buf.attr_idx++;
}

void mesh_process_attr_layout(struct mesh *mesh)
{
	int offset;
	struct vertex_attribute *attr;

	if (!mesh) {
		return;
	}
	offset = 0;
	mesh->vert_buf.stride = 0;
	for (unsigned int i = 0; i < mesh->vert_buf.attr_idx; i++) {
		attr = &mesh->vert_buf.attrs[i];
		attr->offset = offset;
		offset += attr->num_comps;
		mesh->vert_buf.stride += attr->num_comps;
	}
	glBindVertexArray(mesh->gl_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vert_buf.id);
	for (unsigned int i = 0; i < mesh->vert_buf.attr_idx && mesh; i++) {
		attr = &mesh->vert_buf.attrs[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attr->num_comps, GL_FLOAT,
			GL_FALSE, sizeof(float)
			* (size_t)(mesh->vert_buf.stride),
			(void *)(sizeof(float) * (size_t)(attr->offset)));
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mesh_draw(struct mesh *mesh, int elem_count, unsigned int idx_offset)
{
	if (!mesh) {
		return;
	}
	elem_count = (elem_count ? elem_count : mesh->idx_buf.elem_count);
	glBindVertexArray(mesh->gl_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vert_buf.id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->idx_buf.id);
	glDrawElements(GL_TRIANGLES, elem_count, GL_UNSIGNED_INT,
		(void *)(sizeof(unsigned int) * (idx_offset * elem_count)));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // HACK: Is this necessary?
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // HACK: Is this necessary?
}

/*void mesh_draw(struct mesh *mesh)
{
	if (!mesh || !mesh->vert_buf.size || !mesh->vert_buf.stride) {
		return;
	}
	glBindVertexArray(mesh->gl_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vert_buf.id);
	glDrawArrays(GL_TRIANGLES, 0, 3); // this will only draw 3 vertices
	LOG("%llu %llu", mesh->vert_buf.size, mesh->vert_buf.stride);
}*/
