#ifndef P_QUEUE_H
#define P_QUEUE_H

#include "types.h"

struct p_queue *p_queue_create(void);
void p_queue_destroy(struct p_queue *q);
void p_queue_push(struct p_queue *q, void *data, uint32_t priority);
void *p_queue_pop(struct p_queue *q);
bool p_queue_is_empty(struct p_queue *q);

#endif
