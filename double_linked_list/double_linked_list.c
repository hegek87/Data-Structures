#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "double_linked_list.h"


struct node *create_empty_node(){
	struct node *temp = (struct node *) malloc(sizeof(struct node));
	temp->next = temp->prev = NULL;
	temp->data = NULL;
	return temp;
}

struct node *create_node(void *key){
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

struct dl_list *create_empty_list(){
	struct dl_list *temp = (struct dl_list *)malloc(sizeof(struct dl_list));
	temp->head = temp->tail = NULL;
	temp->size = 0;
	return temp;
}

//for now assume data is int
struct node *search(struct dl_list *list, 
		void *key, int (*comp)(void *,void *)){
	struct node *cur = list->head;
	while(cur && !(*comp)(cur->data, key)){
		cur = cur->next;
	}
	return cur;
}

void insert_el_head(struct dl_list **list, void *key){
	struct node *temp = create_node(key);
	insert_node_head(list, temp);
}

void insert_el_tail(struct dl_list **list, void *key){
	struct node *temp = create_node(key);
	insert_node_tail(list, temp);
}
	
void insert_node_head(struct dl_list **list, struct node *temp){
	//is the list empty?
	if(is_empty(*list)){
		(*list)->head = (*list)->tail = temp;
		++(*list)->size;
		return;
	}
	temp->next = (*list)->head;
	((*list)->head)->prev = temp;
	(*list)->head = temp;
	++(*list)->size;
}
void insert_node_tail(struct dl_list **list, struct node *temp){
	//is the list empty?
	if(is_empty(*list)){
		(*list)->head = (*list)->tail = temp;
		++(*list)->size;
		return;
	}
	(*list)->tail->next = temp;
	temp->prev = (*list)->tail;
	(*list)->tail = temp;
	++(*list)->size;
}
//if z>list->size, insert at tail;
void insert_el_at(struct dl_list **list, void *key, int z){
	struct node *temp = create_node(key);
	insert_node_at(list, temp, z);
}
		
//insert in the z+1 position
void insert_node_at(struct dl_list **list, struct node *dat, int z){
	if(is_empty(*list) || z == 0){
		insert_node_head(list, dat);
		return;
	}
	if(z >= (*list)->size){
		insert_node_tail(list, dat);
		return;
	}
	//0<z<list->size
	struct node *cur = (*list)->head;
	while(z-- > 0){
		cur = cur->next;
	}
	dat->next = cur->next;
	cur->next = dat;
	dat->next->prev = dat;
	dat->prev = cur;
	++(*list)->size;
}	

/*
void delete_all(struct dl_list **list, void *key){
	if(is_empty(*list)){
		return;
	}
	struct node *cur = (*list)->head;
	while(cur->next != NULL){
		//first element is a key
		if((*list)->head->data == key){
			struct node *to_die = (*list)->head;
			(*list)->head = (*list)->head->next;
			to_die->next = NULL;
			(*list)->head->prev = NULL;
			destroy_node(to_die);
			--(*list)->size;
		}
		//match found, delete
		else if(cur->data == key){
			struct node *to_die = cur;
			cur->prev = cur->next;
			cur->next = cur->prev;
			cur = cur->next;
			destroy_node(to_die);
			--(*list)->size;
		}
		//no match found
		else{
			cur=cur->next;
		}
	}
}
*/

void delete_el(struct dl_list **list, void *key, int (*comp)(void*,void*)){
	if(is_empty(*list)){
		return;
	}
	struct node *cur;
	//key not found
	if(!(cur = search(*list, key, comp))){ return; }
	
	//delete found key
	
	//cur is neither tail nor 
	
	if(cur->next && cur->prev){
	/*
	c -> c -> c
	u    u    u
	r <- r <- r
	p         n
	*/
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		destroy_node(cur);
	/*
	c ------> c
	u         u
	r <------ r
	p <- c -> n
	     u
	     r
	*/
	}
	
	else if(cur->next == NULL){
		//cur == (*list)->tail
		delete_tail(list);
	}
	else{
		//cur == (*list)->head
		delete_head(list);
	}
}

void delete_head(struct dl_list **list){
	//empty list
	if(is_empty(*list)){
		return;
	}
	//singleton list
	if((*list)->size == 1){
		struct node *to_die = (*list)->head;
		(*list)->head = (*list)->tail = NULL;
		destroy_node(to_die);
		--(*list)->size;
		destroy_node(to_die);
		return;
	}
	//(*list)->size > 1
	struct node *to_die = (*list)->head;
	(*list)->head = (*list)->head->next;
	(*list)->head->prev = NULL;
	--(*list)->size;
	destroy_node(to_die);
}

void delete_tail(struct dl_list **list){
	//empty list
	if(is_empty(*list)){
		return;
	}
	//singleton list
	//possibly use clear_list instead
	if((*list)->size == 1){
		struct node *to_die = (*list)->head;
		(*list)->head = (*list)->tail = NULL;
		destroy_node(to_die);
		--(*list)->size;
		return;
	}
	//(*list)->size > 1
	struct node *to_die = (*list)->tail;
	(*list)->tail = (*list)->tail->prev;
	(*list)->tail->next = NULL;
	--(*list)->size;
	destroy_node(to_die);
}

void delete_at(struct node **, int);

void print_list(struct dl_list *list){
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

int is_empty(struct dl_list *list){ return list == NULL || list->size == 0; }
void clear_list(struct dl_list **list){
	(*list)->size = 0;
	(*list)->head = (*list)->tail = NULL;
}
int size(struct dl_list *list){
	return list->size;
}

void free_list(struct dl_list *list){
	struct node *cur;
	struct node *temp;
	for(cur = list->head; cur != NULL; cur = temp){
		temp = cur->next;
		destroy_node(cur);
	}
	free(list);
}

int numcmp(int *x, int *y){
	return *x == *y;
}

int main(){
	int *p = (int *)malloc(sizeof(int *));
	//printf("%d %d\n", sizeof(int), sizeof(int *));
	int x = 1, y=2, z=5, a=7, m = 100;
	*p = m;
	struct dl_list *head = create_empty_list();
	insert_el_head(&head, (void *)p);
	insert_el_head(&head, (void *)&x);
	insert_el_head(&head, (void *)&y);
	print_list(head);
	printf("Deleting: %d\n", *((int *)&x));
	delete_el(&head, (void *)&x, (int(*)(void*,void*))numcmp);
	print_list(head);
	/*
	insert_el_head(&head, (void *)&z);
	insert_el_head(&head, (void *)&a);
	insert_el_head(&head, (void *)&z);
	insert_el_head(&head, (void *)&a);
	print_list(head);
	insert_el_tail(&head, (void *)&z);
	insert_el_tail(&head, (void *)&a);
	insert_el_tail(&head, (void *)&z);
	insert_el_tail(&head, (void *)&a);
	insert_el_tail(&head, (void *)&y);
	insert_el_tail(&head, (void *)&y);
	insert_el_tail(&head, (void *)&y);
	insert_el_tail(&head, (void *)&y);
	*/
	
	/*
	struct node *temp = search(head, (void *)&z, 
		(int (*)(void *,void *))numcmp);
	printf("is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	
	temp = search(head, (void *)&m, (int (*)(void *,void *))numcmp);
	printf("Is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	
	print_list(head);
	*/
	//free(temp);
	
	

	/*
	print_list(head);
	printf("Deleting head\n");
	delete_head(&head);
	print_list(head);
	printf("Deleting tail\n");
	delete_tail(&head);
	print_list(head);
	*/
	/*
	printf("Deleting: %d\n", *((int *)&x));
	delete_el(&head, (void *)&x, (int(*)(void*,void*))numcmp);
	print_list(head);
	*/
		
	
	//print_list(head);
	free(p);
	//print_list(head);
	free_list(head);
	
	/*
	print_list(head);
	insert_el_at(&head, (void *)&z, 0);
	print_list(head);
	
	struct node *temp = search(head, (void *)&z);
	printf("is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	temp = search(head, (void *)&m);
	printf("Is it found? %d\n", (temp == NULL) ? 0 : *((int *)temp->data));
	print_list(head);
	delete_el(&head, (void *)&y);
	print_list(head);
	delete_tail(&head);
	print_list(head);
	*/
	/*
	print_list(head);
	delete_all(&head, (void *)&y);
	print_list(head);
	*/
	/*
	delete_el(&head, (void *)&x);
	
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
	*/
	return 0;
}
