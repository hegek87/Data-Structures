#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "stack.h"


struct stack *create_stack(void){
	struct stack *temp = malloc(sizeof(struct stack));
	temp->top = create_empty_list();
	return temp;
}

void push_node(struct stack *st, struct node *key){
	insert_node_head(st->top, key);
}

void push_key(struct stack *st, void *key){ 
	return push_node(st, create_node(key)); 
}

struct node *pop(struct stack *st){ return delete_head(st->top); }

struct node *peek(struct stack *st){
	struct node *temp = pop(st);
	if(!temp){ return NULL; }
	//create a copy to return
	struct node *copy = malloc(sizeof(struct node));
	memcpy(copy, temp, sizeof(struct node));
	copy->data = temp->data;
	push_node(st, temp);
	return copy;
}

int is_stack_empty(const struct stack *st){ 
	return (st->top->size == 0 || st == NULL); 
}

int stack_size(const struct stack *st){ return st->top->size; }

void destroy_stack(struct stack *st){
	free_list(st->top);
	free(st);
}

/*
int main(void){
	char *x = "./abcdefghijklmnopqrstuvwxyz";
	struct stack *st = create_stack();
	push_key(st, x);
	char *z = (char *)(peek(st)->data);
	printf("Before: %s\n", x);
	printf("After:  %s\n", z);
	
	return 0;
}*/


