#ifndef STACK_H
#define STACK_H
#include "double_linked_list.h"
//#include "../double_linked_list/double_linked_list.h"
struct stack{
	struct dl_list *top;
	int size;
};

struct stack *create_stack();
void push_node(struct stack **, struct node *);
void push_key(struct stack **, void *);
struct node *pop(struct stack *);
struct node *peek(struct stack *);
int is_stack_empty(struct stack *);
#endif
