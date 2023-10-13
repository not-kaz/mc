#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

struct list *list_create(void);
void list_destroy(struct list *list);
void list_push_back(struct list *list, void *data);
void *list_pop_front(struct list *list);
bool list_contains(struct list *list, void *data);
bool list_is_empty(struct list *list);

#endif
