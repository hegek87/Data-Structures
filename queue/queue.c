#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "queue.h"

struct queue *create_queue(void){
	struct queue *q = malloc(sizeof(struct queue));
	q->list = create_empty_list();
	return q;
};

void enqueue_key(struct queue *q, const void *key){
	enqueue_node(q, create_node(key));
}
void enqueue_node(struct queue *q, struct node *key){
	insert_node_tail(q->list, key);
}

struct node *dequeue(struct queue *q){
	return delete_head(q->list);
}

struct node *peek(struct queue *q){
	struct node *temp = dequeue(q);
	//underflow
	if(!temp){ return NULL; }
	struct node *copy = malloc(sizeof(struct node));
	memcpy(copy, temp, sizeof(struct node));
	void *copy_data = malloc(sizeof(void *));
	memcpy(copy_data, temp->data, sizeof(void *));
	copy->data = copy_data;
	insert_node_head(q->list, temp);
	return copy;
}
	

int queue_size(const struct queue *q){ return q->list->size; }
int is_queue_empty(const struct queue *q){ return !queue_size(q); }

void destroy_queue(struct queue *q){
	free_list(q->list);
	free(q);
}

int main(){
	struct queue *q = create_queue();
	int x=1,y=2,z=6,m=14;
	printf("Is queue Empty? %d\n", is_queue_empty(q));
	printf("Queue size: %d\n", queue_size(q));
	enqueue_key(q, (void *)&x);
	enqueue_key(q, (void *)&y);
	enqueue_key(q, (void *)&z);
	enqueue_key(q, (void *)&m);
	enqueue_key(q, (void *)&y);
	enqueue_key(q, (void *)&x);
	enqueue_key(q, (void *)&z);
	enqueue_key(q, (void *)&m);
	struct node *t1 = peek(q);
	printf("Front element: %d\n", *((int *)t1->data));
	destroy_node(t1);
	printf("Is queue Empty? %d\n", is_queue_empty(q));
	printf("Queue size: %d\n", queue_size(q));
	struct node *temp;
	while((temp = dequeue(q))){
		printf("Key: %d\n", *((int *)temp->data));
		if(temp){ destroy_node(temp); }
	}
	
	
	printf("Is queue Empty? %d\n", is_queue_empty(q));
	printf("Queue size: %d\n", queue_size(q));
	
	destroy_queue(q);
	
	return 0;
}
