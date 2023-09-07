#include "p_queue.h"

#include "log.h"

#include <stdlib.h>

#define P_QUEUE_DEFAULT_SIZE 4
#define P_QUEUE_MULTIPLY_FACTOR 2

/* OPTIMIZE: Current implementation of prority queue is a heap object. *
 * This could lead to performance issues with constant mem allocating. *
 * However, this allows us to have a hidden implementation w/ interface. */

/* HACK: Push and pop functions is copied from rosettacode.org. *
 * Write a clean version and try to understand what is happening. */

/* TODO: Add graceful error handling and logging. */

struct node {
	void *data;
	uint32_t priority;
};

struct p_queue {
	struct node *nodes;
	size_t len;
	size_t size;
};

struct p_queue *p_queue_create(void)
{
	struct p_queue *q;

	q = calloc(1, sizeof(struct p_queue));
	if (!q) {
		return NULL;
	}
	q->nodes = calloc(P_QUEUE_DEFAULT_SIZE, sizeof(struct node));
	if (!q->nodes) {
		return NULL;
	}
	q->len = 0;
	q->size = P_QUEUE_DEFAULT_SIZE;
	return q;
}

void p_queue_destroy(struct p_queue *q)
{
	free(q->nodes);
	free(q);
}

void p_queue_push(struct p_queue *q, void *data, uint32_t priority)
{
	size_t i, j;

	if (q->len + 1 >= q->size) {
		q->size = q->size * P_QUEUE_MULTIPLY_FACTOR;
		q->nodes = realloc(q->nodes, q->size * sizeof(struct node));
	}
	i = q->len + 1;
	j = i / 2;
	while (i > 1 && q->nodes[j].priority > priority) {
		q->nodes[i] = q->nodes[j];
		i = j;
		j = j / 2;
	}
	q->nodes[i].priority = priority;
	q->nodes[i].data = data;
	q->len++;
}

void *p_queue_pop(struct p_queue *q)
{
	size_t i, j, k;
	void *data;

	if (!q->len) {
		return NULL;
	}
	data = q->nodes[1].data;
	q->nodes[1] = q->nodes[q->len];
	q->len--;
	i = 1;
	while (i != q->len + 1) {
		k = q->len + 1;
		j = 2 * i;
		if (j <= q->len && q->nodes[j].priority
				< q->nodes[k].priority) {
			k = j;
		}
		if (j + 1 <= q->len && q->nodes[j + 1].priority
				< q->nodes[k].priority) {
			k = j + 1;
		}
		q->nodes[i] = q->nodes[k];
		i = k;
	}
	return data;
}

bool p_queue_is_empty(struct p_queue *q)
{
	return (q->len ? false : true);
}
