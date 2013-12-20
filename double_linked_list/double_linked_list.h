#ifndef DLL_H
#define DLL_H
struct node{
	void *data;
	struct node *next;
	struct node *prev;
};

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
#endif
