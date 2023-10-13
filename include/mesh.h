#ifndef MESH_H
#define MESH_H

#include "types.h"

struct mesh *mesh_create(float *vertices, size_t size);
void mesh_destroy(struct mesh *mesh);
void mesh_assign_attr(struct mesh *mesh, const char *name, int num_components);
void mesh_process_attr_layout(struct mesh *mesh);
void mesh_bind(struct mesh *mesh);
void mesh_unbind(void);
void mesh_draw(struct mesh *mesh);

#endif
