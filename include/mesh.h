#ifndef MESH_H
#define MESH_H

#include <stddef.h>

#define MAX_NUM_BUFFER_ATTRIBUTES 32

struct _vertex_attribute {
	const char *name;
	int offset;
	int num_components;
};

struct _vertex_buffer {
	float *data;
	size_t size;
	struct _vertex_attribute attrs[MAX_NUM_BUFFER_ATTRIBUTES];
	int stride;
	unsigned int index;
	unsigned int id;
};

struct mesh {
	struct _vertex_buffer buffer;
	unsigned int attr_binding_id;
};

void mesh_init(struct mesh *mesh, float *vertices, size_t size);
void mesh_finish(struct mesh *mesh);
void mesh_assign_attr(struct mesh *mesh, const char *name, int num_components);
void mesh_process_attr_layout(struct mesh *mesh);
void mesh_bind(struct mesh *mesh);
void mesh_unbind(void);
void mesh_draw(struct mesh *mesh);

#endif
