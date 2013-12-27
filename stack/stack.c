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

void push_key(struct stack *st, const void *key){ 
	return push_node(st, create_node(key)); 
}

struct node *pop(struct stack *st){ return delete_head(st->top); }

struct node *peek(struct stack *st){
	struct node *temp = pop(st);
	if(!temp){ return NULL; }
	void *copy_data = malloc(sizeof(void *));
	memcpy(copy_data, temp->data, sizeof(void *));
	//create a copy to return
	struct node *copy = malloc(sizeof(struct node));
	memcpy(copy, temp, sizeof(struct node));
	copy->data = copy_data;
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

int main(){
	int x = 2, y =63, z = 145, m = 357;
	struct stack *st = create_stack();
	push_key(st, (void *)&x);
	struct node *temp = peek(st);
	destroy_node(temp);
	
	
	struct node *t1 = create_node((void *)&x);
	printf("Stack empty? %d\n", is_stack_empty(st));	
	printf("Stack size: %d\n", stack_size(st));	
	push_node(st, t1);
	push_key(st, (void *)&x);
	push_key(st, (void *)&y);
	push_key(st, (void *)&z);
	push_key(st, (void *)&m);
	push_key(st, (void *)&x);
	push_key(st, (void *)&x);
	push_key(st, (void *)&y);
	push_key(st, (void *)&m);
	struct node *t2 = peek(st);
	destroy_node(t2);
	printf("Stack empty? %d\n", is_stack_empty(st));
	printf("Stack size: %d\n", stack_size(st));	
	while((temp = pop(st))){
		printf("Key: %d\n", *((int *)temp->data));
		if(temp){ destroy_node(temp); }
	}
	printf("Stack empty? %d\n", is_stack_empty(st));
	printf("Stack size: %d\n", stack_size(st));	
	
	destroy_stack(st);
	return 0;
}
