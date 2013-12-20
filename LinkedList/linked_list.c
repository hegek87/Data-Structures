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

//inserts after the zth node in the list or if list.size < z, insert at tail
void insert_el_at(struct node **list, void *key, int z){
	struct node *x = create_node(key);
	insert_node_at(list, x, z);
}

void insert_node_at(struct node **list, struct node *x, int z){
	if(is_empty(*list) || z == 0){
		insert_node(list, x);
		return;
	}
	struct node *temp = *list;
	while(--z > 0 && !is_empty(temp->next)){
		temp = temp->next;
	}
	
	x->next = temp->next;
	temp->next = x;
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
	struct node *current = *list;
	struct node *previous = current;
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
	struct node *prev;// = (struct node *)malloc(sizeof(struct node *));
	struct node *cur = *list;
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
}

void delete_head(struct node **list){
	//nothing to delete
	if(is_empty(*list)){
		return;
	}
	*list=(*list)->next;
}



//if i > list.size, we delete the last element
//delete element i where the head is i=0
void delete_at(struct node **list, int i){
	//nothing to delete
	if(is_empty(*list)){
		return;
	}
	if(i == 0){
		delete_head(list);
	}
	struct node *cur = *list;
	struct node *prev = cur;
	//find ith element
	while(!is_empty(cur->next) && i-- > 0){
		prev = cur;
		cur = cur->next;
	}
	//i > list.size
	if(is_empty(cur->next)){
		prev->next = NULL;
		return;
	}
	//0<=i<list.size
	prev->next = cur->next;
}

int size(struct node *list){
	if(is_empty(list)){
		return 0;
	}
	int i = 1;
	struct node *cur = list;
	while(!is_empty(cur->next)){
		++i;
		cur = cur->next;
	}
	return i;
}
		

void clear_list(struct node **list){ *list = NULL; }
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
	
	print_list(head);
	delete_all(&head, (void *)&y);
	print_list(head);
	delete_el(&head, (void *)&x);
	print_list(head);
	delete_head(&head);
	print_list(head);
	insert_el_at(&head, (void *)&y, 4);
	print_list(head);
	delete_at(&head, 10000);
	print_list(head);
	printf("Size: %d\n", size(head));
	clear_list(&head);
	print_list(head);
	printf("Size: %d\n", size(head));
	insert_el(&head, (void *)&x);
	print_list(head);
	printf("Size: %d\n", size(head));
	return 0;
}
