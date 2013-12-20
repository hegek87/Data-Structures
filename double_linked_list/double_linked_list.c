#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "double_linked_list.h"


struct node *create_empty_node();
struct node *create_node(void *);
void destroy_node(struct node *);
struct node *search(struct node *, void *);
void insert_el(struct node **, void *);
void insert_node(struct node **, struct node *);
void insert_el_at(struct node **, void *);
void insert_node_at(struct node **, struct node *);
void delete_all(struct node **, void *);
void delete_el(struct node **, void *);
void delete_head(struct node **);
void delete_at(struct node **, int);
void print_list(struct node *);
int is_empty(struct node *);
void clear_list(struct node **);
int size(struct node **);

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
