#ifndef BST_H
#define BST_H
struct node{
	struct node *parent;
	struct node *left;
	struct node *right;
	int data;
};

struct bs_tree{
	struct node *root;
	int size;
};


struct node *create_empty_node(void);
struct node *create_node(const int);
void destroy_node(struct node *);

struct bs_tree *create_tree(const int);
struct bs_tree *create_empty_tree(void);

void inorder(struct bs_tree *);
void postorder(struct bs_tree *);
void preorder(struct bs_tree *);

void inorder_walk(struct node *);
void postorder_walk(struct node *);
void preorder_walk(struct node *);

struct node *tree_search(struct bs_tree *, const int);
struct node *node_search(struct node *, const int);
struct node *iter_search(struct bs_tree *, const int);
struct node *iter_search_node(struct node *, const int);

struct node *tree_max(struct bs_tree *);
struct node *tree_min(struct bs_tree *);
struct node *max(struct node *);
struct node *min(struct node *);

struct node *tree_successor(struct bs_tree *);
struct node *tree_predecessor(struct bs_tree *);
struct node *successor(struct node *);
struct node *predecessor(struct node *);

void tree_insert_node(struct bs_tree *, struct node *);
void insert_int(struct bs_tree *, const int);

void insert_node(struct node *, struct node *);

struct node *delete_node(struct node *, struct node *);
struct node *delete_el(struct node *, const int);

struct node *delete_root(struct node *);

void free_tree(struct bs_tree *);
void free_tree_node(struct node *);
#endif
