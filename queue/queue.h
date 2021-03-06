#ifndef QUEUE_H
#define QUEUE_H
#include "../double_linked_list/double_linked_list.h"
struct queue{
	struct dl_list* list;
};

struct queue *create_queue(void);
void enqueue_key(struct queue *, const void *);
void enqueue_node(struct queue *, struct node *);

struct node *dequeue(struct queue *);
struct node *peek(struct queue *);

int queue_size(const struct queue *);
int is_queue_empty(const struct queue *);

void destroy_queue(struct queue *);
#endif
