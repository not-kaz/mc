#include "hash_map.h"

#include <stdlib.h>
#include <string.h>

#define FNV_OFFSET 0xcbf29ce484222325
#define FNV_PRIME 0x00000100000001b3
#define INITIAL_CAPACITY 32
#define LOAD_FACTOR 0.75f

struct map_entry {
	char *key;
	void *val;
};

struct hash_map {
	struct map_entry *set;
	uint64_t length;
	uint64_t capacity;
};

struct hash_map_iter {
	struct hash_map *map;
	uint64_t index;
};

static char *str_duplicate(const char *str)
{
	size_t len;
	void *new;

	len = strlen(str) + 1;
	new = malloc(len);
	if (!new) {
		return NULL;
	}
	return memcpy(new, str, len);
}

static uint64_t hash(char *key)
{
	uint64_t hash;

	hash = FNV_OFFSET;
	for (char *ch = key; *ch; ch++) {
		hash ^= (uint8_t)(*ch);
		hash *= FNV_PRIME;
	}
	return hash;
}

static uint64_t calc_index(char *key, uint64_t capacity)
{
	return (uint64_t)(hash(key) & (capacity - 1));
}

static struct map_entry *create_map_set(uint64_t capacity)
{
	struct map_entry *set;

	set = malloc(sizeof(struct map_entry) * capacity);
	if (!set) {
		return NULL;
	}
	for (uint64_t i = 0; i < capacity; i++) {
		set[i].key = NULL;
		set[i].val = NULL;
	}
	return set;
}

static void set_map_entry(struct map_entry *set, uint64_t capacity, char *key,
		void *val)
{
	uint64_t index;

	index = calc_index(key, capacity);
	while (set[index].key != NULL) {
		if (strcmp(set[index].key, key) == 0) {
			set[index].val = val;
			return;
		}
		index++;
		if (index >= capacity) {
			index = 0;
		}
	}
	key = str_duplicate(key);
	if (!key) {
		return;
	}
	set[index].key = key;
	set[index].val = val;
}

static void expand_map_set(struct map_entry **set, uint64_t *capacity)
{
	struct map_entry *new_set;
	uint64_t new_cap;

	new_cap = (*capacity) * 2;
	new_set = create_map_set(new_cap);
	if (!new_set) {
		return;
	}
	for (uint64_t i = 0; i < (*capacity); i++) {
		if ((*set)[i].key == NULL) {
			continue;
		}
		set_map_entry(new_set, new_cap, (*set)[i].key, (*set)[i].val);
	}
	free((*set));
	(*set) = new_set;
	(*capacity) = new_cap;
}

struct hash_map *hash_map_create(void)
{
	struct hash_map *map;

	map = malloc(sizeof(struct hash_map));
	if (!map) {
		return NULL;
	}
	map->set = create_map_set(INITIAL_CAPACITY);
	if (!map->set) {
		free(map);
		return NULL;
	}
	map->length = 0;
	map->capacity = INITIAL_CAPACITY;
	return map;
}

void hash_map_destroy(struct hash_map *map)
{
	for (uint64_t i = 0; i < map->capacity; i++) {
		free(map->set[i].key);
	}
	free(map->set);
	free(map);
}

void hash_map_insert(struct hash_map *map, char *key, void *val)
{
	if (!map || !key) {
		return;
	}
	if ((float)(map->length) / (float)(map->capacity) >= LOAD_FACTOR) {
		expand_map_set(&map->set, &map->capacity);
	}
	set_map_entry(map->set, map->capacity, key, val);
	map->length++;
}

int hash_map_at(struct hash_map *map, char *key, void **val)
{
	uint64_t index;

	index = calc_index(key, map->capacity);
	while (map->set[index].key != NULL) {
		if (strcmp(key, map->set[index].key) == 0) {
			(*val) = map->set[index].val;
			return 1;
		}
		index++;
		if (index >= map->capacity) {
			index = 0;
		}
	}
	return 0;
}

uint64_t hash_map_length(struct hash_map *map)
{
	return map->length;
}

uint64_t hash_map_capacity(struct hash_map *map)
{
	return map->capacity;
}

struct hash_map_iter *hash_map_iter_create(struct hash_map *map)
{
	struct hash_map_iter *iter;

	iter = malloc(sizeof(struct hash_map_iter));
	if (!iter) {
		return NULL;
	}
	iter->map = map;
	iter->index = 0;
	return iter;
}

void hash_map_iter_destroy(struct hash_map_iter *iter)
{
	free(iter);
}

int hash_map_iter_next(struct hash_map_iter *iter, char **key, void **val)
{
	while (iter->index < iter->map->capacity) {
		if (iter->map->set[iter->index].key != NULL) {
			*key = iter->map->set[iter->index].key;
			*val = iter->map->set[iter->index].val;
			iter->index++;
			return 1;
		}
		iter->index++;
	}
	return 0;
}
