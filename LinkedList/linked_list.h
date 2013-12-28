#ifndef LINKED_LIST_H
#define LINKED_LIST_H
struct node{
	void *data;
	struct node *next;
};

struct slist{
	struct node *head;
	int size;
};

typedef int (* comp)(const void *, const void *);

struct node *create_empty_node(void);
struct node *create_node(const void *);
struct slist *create_empty_list(void);
void destroy_node(struct node *);
struct node *search(struct slist *, const void *, comp);
void insert_node_head(struct slist *, struct node *);
void insert_el_head(struct slist *, const void *);
//if the index given is larger than list length, we insert at tail
void insert_el_at(struct slist *, const void *, int);
void insert_node_at(struct slist *, struct node *, int);
void print_list(const struct slist *);
int is_empty(const struct slist *);
void delete_all(struct slist *, const void *, comp);
struct node *delete_el(struct slist *, const void *, comp);
struct node *delete_head(struct slist *);
struct node *delete_tail(struct slist *);
struct node *delete_at(struct slist *, int);
void clear_list(struct slist *);
int size(const struct slist *);

int numcmp(const int *, const int *);
#endif
