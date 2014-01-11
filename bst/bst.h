#ifndef BST_H
#define BST_H
struct t_node{
	struct t_node *parent;
	struct t_node *left;
	struct t_node *right;
	void *data;
};

struct bs_tree{
	struct t_node *root;
	int size;
};

typedef int (*comp)(void *, void *);
typedef void (*print)(void *);


struct t_node *create_empty_node(void);
struct t_node *create_node(void *);
void destroy_node(struct t_node *);

struct bs_tree *create_tree(void *);
struct bs_tree *create_empty_tree(void);

void inorder(struct bs_tree *, print);
void postorder(struct bs_tree *, print);
void preorder(struct bs_tree *, print);

void inorder_walk(struct t_node *, print);
void postorder_walk(struct t_node *, print);
void preorder_walk(struct t_node *, print);

struct t_node *tree_search(struct bs_tree *, void *, comp);
struct t_node *node_search(struct t_node *, void *, comp);
struct t_node *iter_search(struct bs_tree *, void *, comp);
struct t_node *iter_search_node(struct t_node *, void *, comp);

struct t_node *tree_max(struct bs_tree *);
struct t_node *tree_min(struct bs_tree *);
struct t_node *max(struct t_node *);
struct t_node *min(struct t_node *);

struct t_node *successor(struct t_node *);
struct t_node *predecessor(struct t_node *);

void tree_insert_node(struct bs_tree *, struct t_node *, comp);
void insert_el(struct bs_tree *, void *, comp);
void insert_int(struct bs_tree *, int *);

void insert_node(struct t_node *, struct t_node *, comp);

struct t_node *delete_node(struct bs_tree *, struct t_node *, comp);
struct t_node *delete_el(struct bs_tree *, void *, comp);

struct t_node *delete_int(struct bs_tree *, int);


void free_tree(struct bs_tree *);
void free_tree_node(struct t_node *);

int int_comp(int *, int *);
void int_print(int *);
#endif
