#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "double_linked_list.h"


struct node *create_empty_node(){
	return (struct node *) malloc(sizeof(struct node *));
}

struct node *create_node(void *key){
	struct node *temp = create_empty_node();
	temp->data = key;
	temp->next = temp->prev = NULL;
	return temp;
}

void destroy_node(struct node *to_die){
	free(to_die);
}

struct dl_list *create_empty_list(){
	return (struct dl_list *)malloc(sizeof(struct dl_list *));
}

struct node *search(struct dl_list *, void *);

void insert_el_head(struct dl_list **, void *);
void insert_el_tail(struct dl_list **, void *);
void insert_node_head(struct dl_list **, struct node *);
void insert_node_tail(struct dl_list **, struct node *);
void insert_el_at(struct dl_list **, void *);
void insert_node_at(struct dl_list **, struct node *);

void delete_all(struct dl_list **, void *);
void delete_el(struct dl_list **, void *);
void delete_head(struct dl_list **);
void delete_tail(struct dl_list **);
void delete_at(struct node **, int);

void print_list(struct dl_list *);
int is_empty(struct dl_list *);
void clear_list(struct dl_list **);
int size(struct dl_list *);

int main(){
	/*
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
	printf("Size: %d\n", size(&head));
	clear_list(&head);
	print_list(head);
	printf("Size: %d\n", size(&head));
	insert_el(&head, (void *)&x);
	print_list(head);
	printf("Size: %d\n", size(&head));
	*/
	return 0;
}
