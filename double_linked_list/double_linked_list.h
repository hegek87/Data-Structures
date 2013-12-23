#ifndef DLL_H
#define DLL_H
struct node{
	void *data;
	struct node *next;
	struct node *prev;
};

struct dl_list{
	struct node *head;
	struct node *tail;
	int size;
};

struct node *create_empty_node();
struct node *create_node(void *);
void destroy_node(struct node *);

struct dl_list *create_empty_list();

struct node *search(struct dl_list *, void *, int (*comp)(void *,void *));

void insert_el_head(struct dl_list **, void *);
void insert_el_tail(struct dl_list **, void *);
void insert_node_head(struct dl_list **, struct node *);
void insert_node_tail(struct dl_list **, struct node *);
void insert_el_at(struct dl_list **, void *, int);
void insert_node_at(struct dl_list **, struct node *, int);

void delete_all(struct dl_list **, void *, int(*com)(void*,void*));
struct node *delete_el(struct dl_list **, void *, int (*comp)(void *, void *));
struct node *delete_head(struct dl_list **);
struct node *delete_tail(struct dl_list **);
struct node *delete_at(struct dl_list **, int);
struct node *delete_node(struct dl_list **, struct node *);

//uses delete_el, assuming comp == numcmp
struct node *delete_int(struct dl_list **, int);

void print_list(struct dl_list *);
int is_empty(struct dl_list *);
void clear_list(struct dl_list *);
void free_list(struct dl_list *);
int size(struct dl_list *);

//comparison functions
int numcmp(int *x, int *y);
#endif
