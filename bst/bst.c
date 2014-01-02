#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "bst.h"

struct node *create_empty_node(void){
	struct node *temp = malloc(sizeof(struct node));
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

struct node *create_node(const int key){
	struct node *temp = create_empty_node();
	temp->data = key;
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

void destroy_node(struct node *to_die){
	free(to_die);
}

struct bs_tree *create_tree(const int x){
	struct bs_tree *temp = create_empty_tree();
	temp->size = 1;
	temp->root = create_node(x);
	return temp;
}

struct bs_tree *create_empty_tree(void){
	return malloc(sizeof(struct bs_tree));
}

void inorder(struct bs_tree *tree){
	inorder_walk(tree->root);
	printf("\n");
}

void inorder_walk(struct node *root){
	if(root){
		inorder_walk(root->left);
		printf("%d ", root->data);
		inorder_walk(root->right);
	}
}

void postorder(struct bs_tree *tree){
	postorder_walk(tree->root);
	printf("\n");
}

void postorder_walk(struct node *root){
	if(root){
		postorder_walk(root->left);
		postorder_walk(root->right);
		printf("%d ", root->data);
	}
}

void preorder(struct bs_tree *tree){
	preorder_walk(tree->root);
	printf("\n");
}

void preorder_walk(struct node *root){
	if(root){
		printf("%d ", root->data);
		preorder_walk(root->left);
		preorder_walk(root->right);
	}
}

struct node *node_search(struct node *root, const int key){
	if(!root || root->data == key){
		return root;
	}
	else if(root->data < key){
		return node_search(root->right, key);
	}
	else{
		return node_search(root->left, key);
	}
}

struct node *tree_search(struct bs_tree *tree, const int key){
	return node_search(tree->root, key);
}
	
struct node *iter_search(struct bs_tree *tree, const int key){
	return iter_search_node(tree->root, key);
}

struct node *iter_search_node(struct node *root, const int key){
	struct node *temp = root;
	while(temp && key != temp->data){
		if(temp->data < key){
			temp = temp->right;
		}
		else{
			temp = temp->left;
		}
	}
	return temp;
}

struct node *tree_max(struct bs_tree *tree){
	return max(tree->root);
}

struct node *tree_min(struct bs_tree *tree){
	return min(tree->root);
}

struct node *max(struct node *root){
	struct node *temp = root;
	while(temp->right){
		temp = temp->right;
	}
	return temp;
}

struct node *min(struct node *root){
	struct node *temp = root;
	while(temp->left){
		temp = temp->left;
	}
	return temp;
}

struct node *successor(struct node *root){
	struct node *temp = root;
	if(temp->right){
		return min(temp->right);
	}
	struct node *t1 = temp->parent;
	while(t1 && t1->right == temp){
		temp = t1;
		t1 = t1->parent;
	}
	return t1;
}

struct node *predecessor(struct node *root){
	struct node *temp = root;
	if(temp->left){
		return max(temp->left);
	}
	struct node *t1 = temp->parent;
	while(t1 && temp == t1->left){
		temp = t1;
		t1 = t1->parent;
	}
	return t1;
}

void tree_insert_node(struct bs_tree *tree, struct node *key){
	insert_node(tree->root, key);
	++(tree->size);
}

void insert_int(struct bs_tree *tree, const int x){
	tree_insert_node(tree, create_node(x));
}


void insert_node(struct node *root, struct node *key){
	struct node *x = root;
	struct node *y = NULL;
	while(x){
		y = x;
		if(x->data < key->data){
			x = x->right;
		}
		else{
			x = x->left;
		}
	}
	key->parent = y;
	if(!y){
		root = key;
	}
	else if(key->data < y->data){
		y->left = key;
	}
	else{
		y->right = key;
	}
}

static void transplant(struct bs_tree *tree, struct node *u, struct node *v){
	if(!u->parent){
		tree->root = v;
	}
	else if(u->parent->left == u){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	if(v){
		v->parent = u->parent;
	}
}

struct node *delete_node(struct bs_tree *tree, struct node *key){
	if(!key->left){
		transplant(tree, key, key->right);
	}
	else if(!key->right){
		transplant(tree, key, key->left);
	}
	else{
		struct node *y = min(key->right);
		if(y->parent != key){
			transplant(tree, y, y->right);
			y->right = key->right;
			y->right->parent = y;
		}
		transplant(tree, key, y);
		y->left = key->left;
		y->left->parent = y;
	}
	--(tree->size);
	return key;
}

struct node *delete_el(struct bs_tree *tree, const int x){
	return delete_node(tree, iter_search(tree, x));
}

void free_tree(struct bs_tree *tree){
	free_tree_node(tree->root);
	free(tree);
}

void free_tree_node(struct node *root){
	if(root){
		struct node *temp = root;
		free_tree_node(temp->left);
		free_tree_node(temp->right);
		free(temp);
	}
}


int main(void){
	struct bs_tree *root = create_tree(50);
	//insert_int(root, 47);
	insert_int(root, 65);
	insert_int(root, 60);
	insert_int(root, 55);
	insert_int(root, 30);
	insert_int(root, 20);
	insert_int(root, 40);
	insert_int(root, 5);
	insert_int(root, 22);
	insert_int(root, 25);
	insert_int(root, 72);
	insert_int(root, 95);
	insert_int(root, 35);
	insert_int(root, 75);
	insert_int(root, 47);
	insert_int(root, 78);
	insert_int(root, 34);
	insert_int(root, 76);
	insert_int(root, 32);
	inorder(root);
	//printf("ROOT: %d\n", root->root->data);
	
	struct node *temp, *t1;
	for(temp = tree_min(root); temp; temp = t1){
		t1 = successor(temp);
		//printf("Deleting %d\n", temp->data);
		delete_node(root, temp);
		//printf("ROOT: %d\n", root->root->data);
		inorder(root);
	}
	//inorder(root);
	
	//delete_node(root, t1);
	//inorder(root);
	
	return 0;
}
