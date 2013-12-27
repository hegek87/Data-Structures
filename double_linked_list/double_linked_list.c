#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "double_linked_list.h"


struct node *create_empty_node(void){
	struct node *temp = malloc(sizeof(struct node));
	temp->next = temp->prev = NULL;
	temp->data = NULL;
	return temp;
}

struct node *create_node(const void *key){
	void *copy = malloc(sizeof(void *));
	memcpy(copy, key, sizeof(key));
	struct node *temp = create_empty_node();
	temp->data = copy;
	temp->next = temp->prev = NULL;
	return temp;
}

void destroy_node(struct node *to_die){
	free(to_die->data);
	free(to_die);
}

struct dl_list *create_empty_list(void){
	struct dl_list *temp = malloc(sizeof(struct dl_list));
	temp->head = temp->tail = NULL;
	temp->size = 0;
	return temp;
}

struct node *search(struct dl_list *list, const void *key, comp eq){
	struct node *cur = list->head;
	while(cur && !eq(cur->data, key)){
		cur = cur->next;
	}
	return cur;
}

void insert_el_head(struct dl_list *list, const void *key){
	struct node *temp = create_node(key);
	insert_node_head(list, temp);
}

void insert_el_tail(struct dl_list *list, const void *key){
	struct node *temp = create_node(key);
	insert_node_tail(list, temp);
}
	
void insert_node_head(struct dl_list *list, struct node *temp){
	//is the list empty?
	if(is_empty(list)){
		list->head = list->tail = temp;
		++(list->size);
		return;
	}
	temp->next = list->head;
	list->head->prev = temp;
	list->head = temp;
	++(list->size);
}

void insert_node_tail(struct dl_list *list, struct node *temp){
	//is the list empty?
	if(is_empty(list)){
		list->head = list->tail = temp;
		++(list->size);
		return;
	}
	list->tail->next = temp;
	temp->prev = list->tail;
	list->tail = temp;
	++(list->size);
}
//if z>list->size, insert at tail;
void insert_el_at(struct dl_list *list, const void *key, int z){
	struct node *temp = create_node(key);
	insert_node_at(list, temp, z);
}
		
//insert in the z+1 position
void insert_node_at(struct dl_list *list, struct node *dat, int z){
	if(is_empty(list) || z == 0){
		insert_node_head(list, dat);
		return;
	}
	if(z >= list->size){
		insert_node_tail(list, dat);
		return;
	}
	//0<z<list->size
	struct node *cur = list->head;
	while(z-- > 0){
		cur = cur->next;
	}
	dat->next = cur->next;
	cur->next = dat;
	dat->next->prev = dat;
	dat->prev = cur;
	++(list->size);
}	

void delete_all(struct dl_list *list, const void *key, comp eq){
	//nothing to delete
	if(is_empty(list)){
		return;
	}
	//list not empty
	struct node *cur;
	struct node *temp;
	for(cur = list->head; cur != NULL; ){
		//Key found
		if(eq(cur->data, key)){
			//cur is head
			if(!cur->prev){
				destroy_node(delete_head(list));
				cur = list->head;
			}
			//cur is tail
			else if(!cur->next){
				destroy_node(delete_tail(list));
				cur = NULL;
			}
			else{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				temp = cur;
				cur = cur->next;
				destroy_node(temp);
				--(list->size);
			}
		}
		//key not found
		else{
			cur = cur->next;
		}
	}
}


struct node *delete_el(struct dl_list *list, void *key, comp eq){
	if(is_empty(list)){
		return NULL;
	}
	struct node *cur;
	//key not found
	if(!(cur=search(list, key, eq))){ return NULL; }
	//delete found key
	return delete_node(list, cur);
}

struct node *delete_head(struct dl_list *list){
	//empty list
	if(is_empty(list)){
		return NULL;
	}
	//singleton list
	if(list->size == 1){
		struct node *to_die = list->head;
		list->head = list->tail = NULL;
		--(list->size);
		return to_die;
	}
	//(*list)->size > 1
	struct node *to_die = list->head;
	list->head = list->head->next;
	list->head->prev = NULL;
	--(list->size);
	return to_die;
}

struct node *delete_tail(struct dl_list *list){
	//empty list
	if(is_empty(list)){
		return NULL;
	}
	//singleton list
	if(list->size == 1){
		struct node *to_die = list->head;
		list->head = list->tail = NULL;
		--(list->size);
		return to_die;
	}
	//(*list)->size > 1
	struct node *to_die = list->tail;
	list->tail = list->tail->prev;
	list->tail->next = NULL;
	--(list->size);
	return to_die;
}

//delete tail if input is larger than list size
//delete the element immediately after the zth node
struct node *delete_at(struct dl_list *list, int z){
	if(is_empty(list)){
		//nothing to delete
		return NULL;
	}
	else if(z == 0){
		return delete_head(list);
	}
	else if(z >= list->size){
		return delete_tail(list);
	}
	else{
		struct node *temp = list->head;
		while(z-- > 0){
			temp = temp->next;
		}
		return delete_node(list, temp);
	}
}

struct node *delete_node(struct dl_list *list, struct node *to_die){
	if(!to_die->next){
		//data == list->tail
		return delete_tail(list);
	}
	else if(!to_die->prev){
		//data == list->head		
		return delete_head(list);
	}
	else{
		to_die->prev->next = to_die->next;
		to_die->next->prev = to_die->prev;
		--(list->size);
		to_die->next = to_die->prev = NULL;
		return to_die;
	}
}

struct node *delete_int(struct dl_list *list, int z){
	return delete_el(list, (void *)&z, (comp)numcmp);
}
	

void print_list(const struct dl_list *list){
	if(list->size == 0){
		return;
	}
	int i = 0;
	struct node *cur = list->head;
	while(i++ < list->size){
		printf("%d ", *((int *)cur->data));
		cur = cur->next;
	}
	printf("\n");
}

int is_empty(const struct dl_list *list){ return list == NULL || list->size == 0; }

void clear_list(struct dl_list *list){
	list->size = 0;
	struct node *cur;
	struct node *temp;
	for(cur = list->head; cur != NULL; cur = temp){
		temp = cur->next;
		destroy_node(cur);
	}
}
int size(const struct dl_list *list){
	return list->size;
}

void free_list(struct dl_list *list){
	clear_list(list);
	free(list);
}

int numcmp(const int *x, const int *y){
	return *x == *y;
}

/*
int main(){
	int *p = malloc(sizeof(int *));
    int x = 1, y=2, z=5, a=7, m = 100;
	*p = m;
	struct dl_list *head = create_empty_list();
	insert_el_head(head, (void *)p);
	insert_el_head(head, (void *)&x);
	insert_el_head(head, (void *)&y);
	print_list(head);
	insert_el_head(head, (void *)&z);
	insert_el_head(head, (void *)&a);
	insert_el_head(head, (void *)&z);
	insert_el_head(head, (void *)&a);
	print_list(head);
	insert_el_tail(head, (void *)&z);
	insert_el_tail(head, (void *)&a);
	insert_el_tail(head, (void *)&z);
	insert_el_tail(head, (void *)&a);
	insert_el_tail(head, (void *)&y);
	insert_el_tail(head, (void *)&y);
	insert_el_tail(head, (void *)&y);
	insert_el_tail(head, (void *)&y);

	print_list(head);
	destroy_node(delete_int(head, x));
	print_list(head);
	delete_all(head, (void *)&a, (comp)numcmp);
	print_list(head);

	struct node *temp = search(head, (void *)&z, (comp)numcmp);
	printf("is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));

	temp = search(head, (void *)&m, (comp)numcmp);
	printf("Is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));

	print_list(head);

	print_list(head);
	printf("Deleting head\n");
	destroy_node(delete_head(head));
	print_list(head);
	printf("Deleting tail\n");
	destroy_node(delete_tail(head));
	print_list(head);


	printf("Deleting: %d\n", *((int *)&x));
	printf("Null? %d\n", delete_el(head, (void *)&x, (comp)numcmp)==NULL);
	print_list(head);
	printf("Freeing p\n");
	free(p);
	print_list(head);

	printf("Inserting %d at position %d\n", *((int *)&y), 5);
	insert_el_at(head, (void *)&y, 4);
	print_list(head);
	destroy_node(delete_at(head, 10000));

	print_list(head);
	printf("Size: %d\n", size(head));
	free_list(head);


	return 0;
}
*/

