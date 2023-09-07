#include "list.h"

#include "log.h"
#include "types.h"

#include <stdlib.h>

struct node {
	void *data;
	struct node *next;
	struct node *prev;
};

struct list {
	struct node *head;
	struct node *tail;
};

struct list *list_create(void)
{
	struct list *list;

	list = malloc(sizeof(struct list));
	if (!list) {
		return NULL;
	}
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void list_destroy(struct list *list)
{
	struct node *tmp;

	while (list->head) {
		tmp = list->head->next;
		free(list->head);
		list->head = tmp;
	}
	free(list);
}

void list_push_back(struct list *list, void *data)
{
	struct node *n;

	if (!list) {
		return;
	}
	n = malloc(sizeof(struct node));
	if (!n) {
		return;
	}
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	if (!list->head && !list->tail) {
		list->head = n;
		list->tail = n;
	} else {
		list->tail->next = n;
		n->prev = list->tail;
		list->tail = n;
	}
}

void *list_pop_front(struct list *list)
{
	struct node *tmp = NULL;
	void *data = NULL;

	if (!list->head) {
		if (list->tail) {
			LOG("Ther eis tail??");
		}
		LOG("No head");
		return NULL;
	}
	data = list->head->data;
	if (list->head->next) {
		list->head->next->prev = NULL;
	} else {
		list->tail = NULL;
	}
	tmp = list->head->next;
	free(list->head);
	list->head = tmp;
	return data;

	/*if (!list->head) {
		return NULL;
	}
	if (!list->head->next) {
		data = list->head->data;
		free(list->head);
		list->head = NULL;
		return data;
	}
	tmp = list->head->next;
	tmp->prev = NULL;
	list->head->prev = NULL;
	list->head->next = NULL;
	data = list->head->data;
	free(list->head);
	list->head = tmp;
	return data;*/
}

bool list_contains(struct list *list, void *data)
{
	struct node *tmp;

	tmp = list->head;
	while (tmp) {
		if (tmp->data == data) {
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

bool list_is_empty(struct list *list)
{
	if (!list->head && !list->tail) {
		return true;
	} else {
		return false;
	}
}
