#ifndef LINKED_LIST_H
#define LINKED_LIST_H
struct node{
	void *data;
	struct node *next;
};

struct node *create_empty_node();
struct node *create_node(void *);
void destroy_node(struct node *);
struct node *search(struct node *, void *);
void insert_node(struct node **, struct node *);
void insert_el(struct node **, void *);
void print_list(struct node *);
int is_empty(struct node *);
void delete_el(struct node **, void *);
#endif
