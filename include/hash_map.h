#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "types.h"

#define HASH_MAP_INSERT(map, key, val) hash_map_insert(map, key, (void *)(val))
#define HASH_MAP_AT(map, key, val) hash_map_at(map, key, (void *)&(val))
#define HASH_MAP_FOR_EACH(iter, key, val) \
	for (; hash_map_iter_next(iter, &(key), &(val)); )

struct hash_map *hash_map_create(void);
void hash_map_destroy(struct hash_map *map);
void hash_map_insert(struct hash_map *map, char *key, void *val);
int hash_map_at(struct hash_map *map, char *key, void **val);
uint64_t hash_map_length(struct hash_map *map);
uint64_t hash_map_capacity(struct hash_map *map);
struct hash_map_iter *hash_map_iter_create(struct hash_map *map);
void hash_map_iter_destroy(struct hash_map_iter *iter);
int hash_map_iter_next(struct hash_map_iter *iter, char **key, void **val);

#endif
