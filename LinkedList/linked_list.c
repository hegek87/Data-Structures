#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "linked_list.h"

struct node *create_empty_node(void){
	return malloc(sizeof(struct node));
}
struct node *create_node(const void *data){
	void *copy_data = malloc(sizeof(void *));
	memcpy(copy_data, data, sizeof(void *));
	struct node *temp = create_empty_node();
	temp->data = copy_data;
	return temp;
}

struct slist *create_empty_list(void){
	struct slist = malloc(sizeof(struct slist));
	slist->size = 0;
	slist->head = NULL;
	return slist;
}

void destroy_node(struct node *to_die){
	free(to_die->data);
	free(to_die);
}

struct node *search(struct slist *list, const void *key, comp eq){
	while(!is_empty(list) && !eq(list->data, key)){
		list = list->next;
	}
	return list;
}

void insert_node_head(struct slist *list, struct node *x){
	x->next = list->head;
	list->head = x;
	++(list->size);
}

void insert_el_head(struct slist *list, const void *data){
	struct node *to_insert = create_node(data);
	insert_node_head(list, to_insert);
}

//inserts after the zth node in the list or if list.size < z, insert at tail
void insert_el_at(struct slist *list, const void *key, int z){
	struct node *x = create_node(key);
	insert_node_at(list, x, z);
}

void insert_node_at(struct slist *list, struct node *x, int z){
	if(is_empty(list) || z == 0){
		insert_node_head(list, x);
		return;
	}
	struct node *temp = list->head;
	while(--z > 0 && temp){
		temp = temp->next;
	}
	
	x->next = temp->next;
	temp->next = x;
	++(list->size);
} 

void print_list(const struct slist *list){
	struct node *runner;
	int i;
	for(runner = list->head, i = 0; i < list->size; list = list->next){
		printf("%d ", *((int *)list->data));
	}
	printf("\n");
}

//deletes every appearance of key
void delete_all(struct slist *list, const void *key, comp eq){
	//nothing to delete
	if(is_empty(list)){
		return;
	}
	struct node *cur = list;
	struct node *prev = cur;
	while(!is_empty(cur)){
		// key found
		if(eq(cur->data, key)){
			//cur is the head
			if(!cur->prev){
				destroy_node(delete_head(list));
				cur = prev = list->head;
			}
			else{
				prev->next = cur->next;	
				destroy_node(cur);
				cur = prev->next;
				--(list->size);
			}
		}
		//key not found
		else{
			prev = cur;
			cur = cur->next;
		}
	}
}

//deletes the first appearance of key
struct node *delete_el(struct slist *list, const void *key){
	if(is_empty(list)){
		return NULL;
	}
	//head == key
	if(eq(list->head->data, key){
		return delete_head(list);
	}
	struct node *prev;
	struct node *cur = list;
	//find key
	while(!eq(cur->data, key) && cur){
		prev = cur;
		cur = cur->next;
	}
	//key not found
	if(!cur){
		return NULL;
	}
	//delete key
	prev->next = cur->next;
	--(list->size);
	return cur;
}

struct node *delete_head(struct slist *list){
	//nothing to delete
	if(is_empty(list)){
		return NULL;
	}
	struct node *temp = list->head;
	list->head=list->head->next;
	--(list->size);
	return temp;
}

struct node *delete_tail(struct slist *list){
	struct node *cur = list->head;
	struct node *prev = cur;
	while(cur->next){
		prev = cur;
		cur = cur->next;
	}
	prev->next = NULL;
	--(list->size);
	return cur;
}

//if i > list.size, we delete the last element
//delete element i where the head is i=0
struct node *delete_at(struct node *list, int i){
	//nothing to delete
	if(is_empty(list)){
		return NULL;
	}
	if(i == 0){
		return delete_head(list);
	}
	if(i >= list->size){
		return delete_tail(list);
	}
	struct node *cur = list->head;
	struct node *prev = cur;
	//find ith element
	while(cur && i-- > 0){
		prev = cur;
		cur = cur->next;
	}
	//0<i<list.size
	prev->next = cur->next;
	--(list->size);
	return cur;
}

int size(const struct node *list){ return list->size; }
		

void clear_list(struct node *list){ 
	list->size = 0;
	struct node *temp;
	struct node *cur;
	for(cur = list->head; cur; cur = temp){
		temp = cur->next;
		destory_node(cur);
	}
	free(list);
}

int is_empty(struct node *list){ return !size(list); }

int main(){ 
	int *p = (int *)malloc(sizeof(int *));
	*p = 10;
	int x = 1, y=2, z=5, a=7, m = 100;
	
	/*
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
	
	struct node *temp = search(head, (void *)&z);
	printf("is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	temp = search(head, (void *)&m);
	printf("Is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	
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
	*/
}
