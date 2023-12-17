#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

#include <stddef.h>

struct chunk *chunk_create(int x, int z);
void chunk_destroy(struct chunk *chunk);
void chunk_draw(struct chunk *chunk);

#endif
