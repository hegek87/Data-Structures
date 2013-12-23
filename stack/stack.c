#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "stack.h"


struct stack *create_stack(){
	struct stack *temp = (struct stack *)malloc(sizeof(struct stack));
	temp->top = (struct dl_list *)malloc(sizeof(struct dl_list));
	//temp->top = create_empty_list();
	//temp->size = temp->top->size;
	temp->size = 0;
	return temp;
}

void push_node(struct stack **st, struct node *key){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	memcpy(temp, key, sizeof(struct node));
	insert_node_head(&((*st)->top), key);
}
struct node *pop(struct stack *st);
struct node *peek(struct stack *st);
int is_stack_empty(struct stack *st);

int main(){
	return 0;
}
