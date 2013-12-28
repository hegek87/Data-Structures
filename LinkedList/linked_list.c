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
	struct slist *temp = malloc(sizeof(struct slist));
	temp->size = 0;
	temp->head = NULL;
	return temp;
}

void destroy_node(struct node *to_die){
	free(to_die->data);
	free(to_die);
}

struct node *search(struct slist *list, const void *key, comp eq){
	struct node *cur = list->head;
	while(cur && !eq(cur->data, key)){
		cur = cur->next;
	}
	return cur;
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
	struct node *cur;
	int i;
	for(cur = list->head, i=0; i < list->size; cur=cur->next, ++i){
		printf("%d ", *((int *)cur->data));
	}
	printf("\n");
}

//deletes every appearance of key
void delete_all(struct slist *list, const void *key, comp eq){
	//nothing to delete
	if(is_empty(list)){
		return;
	}
	struct node *cur = list->head;
	struct node *prev = cur;
	while(cur){
		// key found
		if(eq(cur->data, key)){
			//cur is the head
			if(list->head == cur){
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
struct node *delete_el(struct slist *list, const void *key, comp eq){
	if(is_empty(list)){
		return NULL;
	}
	//head == key
	if(eq(list->head->data, key)){
		return delete_head(list);
	}
	struct node *prev;
	struct node *cur = list->head;
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
struct node *delete_at(struct slist *list, int i){
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

int size(const struct slist *list){ return list->size; }
		

void clear_list(struct slist *list){ 
	list->size = 0;
	struct node *temp;
	struct node *cur;
	for(cur = list->head; cur; cur = temp){
		temp = cur->next;
		destroy_node(cur);
	}
}

void free_list(struct slist *list){
	clear_list(list);
	free(list);
}

int is_empty(const struct slist *list){ return !size(list); }
int numcmp(const int *x, const int *y){ return *x == *y; }

int main(){ 
	int *p = (int *)malloc(sizeof(int *));
	*p = 10;
	int x = 1, y=2, z=5, a=7, m = 100;
	
	struct slist *head = create_empty_list();
	insert_el_head(head, (void *)&x);
	insert_el_head(head, (void *)&y);
	insert_el_head(head, (void *)&z);
	insert_el_head(head, (void *)&a);
	insert_el_head(head, (void *)&z);
	insert_el_head(head, (void *)&a);
	insert_el_head(head, (void *)&z);
	insert_el_head(head, (void *)&a);
	insert_el_head(head, (void *)&z);
	insert_el_head(head, (void *)&a);
	insert_el_head(head, (void *)&y);
	insert_el_head(head, (void *)&y);
	insert_el_head(head, (void *)&y);
	insert_el_head(head, (void *)&y);
	//insert_el_head(head, (void *)&m);
	print_list(head);
	
	
	struct node *temp = search(head, (void *)&z, (comp)numcmp);
	printf("is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	temp = search(head, (void *)&m, (comp)numcmp);
	printf("Is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	
	free(p);
	print_list(head);
	delete_all(head, (void *)&y, (comp)numcmp);
	print_list(head);
	destroy_node(delete_el(head, (void *)&x, (comp)numcmp));
	print_list(head);
	destroy_node(delete_head(head));
	print_list(head);
	insert_el_at(head, (void *)&y, 4);
	print_list(head);
	destroy_node(delete_at(head, 4));
	print_list(head);
	printf("Size: %d\n", size(head));
	destroy_node(delete_tail(head));
	print_list(head);
	destroy_node(delete_el(head, (void *)&z, (comp)numcmp));
	print_list(head);
	free_list(head);
	
	
	return 0;
}
