#include "mesh.h"

#include "common.h"
#include "log.h"

#include <glad/gl.h>

/* TODO: Add an OpenGL index buffer and handle drawing with indices. */

void mesh_init(struct mesh *mesh, float *vertices, size_t size)
{
	if (!mesh || !vertices || !size) {
		return;
	}
	mesh->buffer.data = vertices;
	mesh->buffer.size = size;
	mesh->buffer.stride = 0;
	mesh->buffer.index = 0;
	for (int i = 0; i < MAX_NUM_BUFFER_ATTRIBUTES; i++) {
		mesh->buffer.attrs[i].name = NULL;
		mesh->buffer.attrs[i].offset = 0;
		mesh->buffer.attrs[i].num_components = 0;
	}
	glGenVertexArrays(1, &mesh->attr_binding_id);
	glBindVertexArray(mesh->attr_binding_id);
	glGenBuffers(1, &mesh->buffer.id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer.id);
	glBufferData(GL_ARRAY_BUFFER, (int64_t)(size), vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mesh_finish(struct mesh *mesh)
{
	UNUSED(mesh); // TODO: Implement if necessary.
}

void mesh_assign_attr(struct mesh *mesh, const char *name, int num_components)
{
	if (!mesh || !name || !num_components) {
		return;
	}
	mesh->buffer.attrs[mesh->buffer.index].name = name;
	mesh->buffer.attrs[mesh->buffer.index].num_components = num_components;
	mesh->buffer.index++;
}

void mesh_process_attr_layout(struct mesh *mesh)
{
	int offset;
	struct _vertex_attribute *attr;

	if (!mesh) {
		return;
	}
	offset = 0;
	mesh->buffer.stride = 0;
	for (unsigned int i = 0; i < mesh->buffer.index; i++) {
		attr = &mesh->buffer.attrs[i];
		attr->offset = offset;
		offset += attr->num_components;
		mesh->buffer.stride += attr->num_components;
	}
	glBindVertexArray(mesh->attr_binding_id);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer.id);
	for (unsigned int i = 0; i < mesh->buffer.index && mesh; i++) {
		attr = &mesh->buffer.attrs[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attr->num_components, GL_FLOAT,
			GL_FALSE, sizeof(float) * (size_t)(mesh->buffer.stride),
			(void *)(sizeof(float) * (size_t)(attr->offset)));
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mesh_bind(struct mesh *mesh)
{
	if (!mesh) {
		return;
	}
	glBindVertexArray(mesh->attr_binding_id);
}

void mesh_unbind(void)
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // HACK: Is this necessary?
}

void mesh_draw(struct mesh *mesh)
{
	if (!mesh || !mesh->buffer.size || !mesh->buffer.stride) {
		return;
	}
	glDrawArrays(GL_TRIANGLES, 0,
		(int)(mesh->buffer.size) / mesh->buffer.stride);
}
