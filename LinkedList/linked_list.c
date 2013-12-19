#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "linked_list.h"

struct node *create_empty_node(){
	return (struct node *)malloc(sizeof(struct node *));
}
struct node *create_node(void * data){
	struct node *x = create_empty_node();
	x->data = data;
	return x;
}

void destroy_node(struct node *to_die){
	free(to_die);
}

struct node *search(struct node *list, void *key){
	struct node *x = list;
	while(x != NULL && x->data != key){
		x = x->next;
	}
	return x;
}

void insert_node(struct node **list, struct node *x){
	//create a copy of x
	struct node *temp = malloc(sizeof(struct node *));
	memcpy(temp, x, sizeof(struct node *));
	temp->next = *list;
	*list = temp;
	free(x);
}

void insert_el(struct node **list, void *data){
	struct node *to_insert = create_node(data);
	insert_node(list, to_insert);
}

void print_list(struct node *list){
	struct node *x = list;
	while(x != NULL){
		printf("%d ", *((int *)x->data));
		x = x->next;
	}
	printf("\n");
}
//deletes every appearance of key
void delete_all(struct node **list, void *key){
	//nothing to delete
	if(is_empty(*list)){
		return;
	}
	struct node *previous = (struct node *)malloc(sizeof(struct node *));
	struct node *current = (struct node *)malloc(sizeof(struct node *));
	current = *list;
	while(!is_empty(current)){
		if((*list)->data == key){
			*list = (*list)->next;
		}
		if(current->data == key){
			previous->next = current->next;
			current = current->next;
		}
		else{
			previous = current;
			current = current->next;
		}
	}
}

//deletes the first appearance of key
void delete_el(struct node **list, void *key){
	if(is_empty(*list)){
		return;
	}
	if((*list)->data == key){
		*list = (*list)->next;
		return;
	}
	struct node *prev = (struct node *)malloc(sizeof(struct node *));
	struct node *cur = (struct node *)malloc(sizeof(struct node *));
	cur = *list;
	prev = *list;
	//find key
	while(cur->data != key && !is_empty(cur)){
		prev = cur;
		cur = cur->next;
	}
	//key not found
	if(is_empty(cur)){
		return;
	}
	//delete key
	prev->next = cur->next;
	cur = cur->next;
}

void delete_head(struct node **list){
	//nothing to delete
	if(is_empty(*list)){
		return;
	}
	*list=(*list)->next;
}

int is_empty(struct node *list){ return list == NULL; }

int main(){ 
	int *p = (int *)malloc(sizeof(int *));
	*p = 10;
	int x = 1, y=2, z=5, a=7;
	struct node *head = create_node((void *)p);
	insert_el(&head, (void *)&x);
	insert_el(&head, (void *)&y);
	insert_el(&head, (void *)&z);
	insert_el(&head, (void *)&a);
	insert_el(&head, (void *)&z);
	insert_el(&head, (void *)&a);
	insert_el(&head, (void *)&z);
	insert_el(&head, (void *)&a);
	insert_el(&head, (void *)&z);
	insert_el(&head, (void *)&a);
	insert_el(&head, (void *)&y);
	insert_el(&head, (void *)&y);
	insert_el(&head, (void *)&y);
	insert_el(&head, (void *)&y);
	
	
	//printf("%d\n", *((int *)(head->next->data)));
	print_list(head);
	delete_all(&head, (void *)&y);
	print_list(head);
	delete_el(&head, (void *)&a);
	print_list(head);
	
	/*
	head->data = (void *) 9;
	head->next = create_node();
	head->next->data = (void *) 16;
	head->next->next = create_node();
	head->next->next->data = (void *) 4;
	
	*/
	//struct node *x = search(head, (void *) 16);
	//printf("%d\n", x->data);
	/*
	int *y = (int *)malloc(sizeof(int *));
	*y = 5;
	struct node *x = create_node((void *)y);
	printf("%d\n", *((int *)x->data));
	return 0;
	*/
	return 0;
}
