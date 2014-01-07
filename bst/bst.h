#ifndef BST_H
#define BST_H
struct node{
	struct node *parent;
	struct node *left;
	struct node *right;
	void *data;
};

struct bs_tree{
	struct node *root;
	int size;
};

typedef int (*comp)(void *, void *);
typedef void (*print)(void *);


struct node *create_empty_node(void);
struct node *create_node(void *);
void destroy_node(struct node *);

struct bs_tree *create_tree(void *);
struct bs_tree *create_empty_tree(void);

void inorder(struct bs_tree *, print);
void postorder(struct bs_tree *, print);
void preorder(struct bs_tree *, print);

void inorder_walk(struct node *, print);
void postorder_walk(struct node *, print);
void preorder_walk(struct node *, print);

struct node *tree_search(struct bs_tree *, void *, comp);
struct node *node_search(struct node *, void *, comp);
struct node *iter_search(struct bs_tree *, void *, comp);
struct node *iter_search_node(struct node *, void *, comp);

struct node *tree_max(struct bs_tree *);
struct node *tree_min(struct bs_tree *);
struct node *max(struct node *);
struct node *min(struct node *);

struct node *successor(struct node *);
struct node *predecessor(struct node *);

void tree_insert_node(struct bs_tree *, struct node *, comp);
void insert_el(struct bs_tree *, void *, comp);
void insert_int(struct bs_tree *, int *);

void insert_node(struct node *, struct node *, comp);

struct node *delete_node(struct bs_tree *, struct node *, comp);
struct node *delete_el(struct bs_tree *, void *, comp);

struct node *delete_int(struct bs_tree *, int);

static void transplant(struct bs_tree *, struct node *, struct node *);

void free_tree(struct bs_tree *);
void free_tree_node(struct node *);

int int_comp(int *, int *);
void int_print(int *);
#endif
