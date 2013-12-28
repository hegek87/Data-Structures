#ifndef BST_H
#define BST_H
struct node{
	struct node *parent;
	struct node *left;
	struct node *right;
	int data;
};


struct node *create_empty_node(void);
struct node *create_node(const int);
void destroy_node(struct node *);

struct node *create_tree(const int);

void inorder_walk(struct node *);
void postorder_walk(struct node *);
void preorder_walk(struct node *);

struct node *tree_search(struct node *, const int);
struct node *iter_search(struct node *, const int);

struct node *max(struct node *);
struct node *min(struct node *);

struct node *successor(struct node *);
struct node *predecessor(struct node *);

void insert_node(struct node *, struct node *);
void insert_int(struct node *, const int);

struct node *delete_node(struct node *, struct node *);
struct node *delete_el(struct node *, const int);

void free_tree(struct node *);
#endif
