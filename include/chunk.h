#ifndef CHUNK_H
#define CHUNK_H

struct chunk;

struct chunk *chunk_create(int origin_x, int origin_y);
void chunk_draw(struct chunk *chnk, unsigned int shd);

#endif
