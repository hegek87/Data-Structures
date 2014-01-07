#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "bst.h"

/*
	Binary search tree which has arbitrary data in the nodes,
	in order to use the implementation, the user must supply
	a comparison function to compare two nodes data element,
	and a function which can print a void pointer in some way.
	
	We must have: 	eq(a,b)  <  0 if a <  b
				eq(a,b)  == 0 if a == b
				eq(a,b)  >  0 if a >  b
				
	where eq is our comp function.
*/

struct node *create_empty_node(void){
	struct node *temp = malloc(sizeof(struct node));
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

struct node *create_node(void *key){
	struct node *temp = create_empty_node();
	temp->data = key;
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

void destroy_node(struct node *to_die){
	free(to_die);
}

struct bs_tree *create_tree(void *x){
	struct bs_tree *temp = create_empty_tree();
	temp->size = 1;
	temp->root = create_node(x);
	return temp;
}

struct bs_tree *create_empty_tree(void){
	return malloc(sizeof(struct bs_tree));
}

void inorder(struct bs_tree *tree, print pr){
	inorder_walk(tree->root, pr);
	printf("\n");
}

void inorder_walk(struct node *root, print pr){
	if(root){
		inorder_walk(root->left, pr);
		pr(root->data);
		inorder_walk(root->right, pr);
	}
}

void postorder(struct bs_tree *tree, print pr){
	postorder_walk(tree->root, pr);
	printf("\n");
}

void postorder_walk(struct node *root, print pr){
	if(root){
		postorder_walk(root->left, pr);
		postorder_walk(root->right, pr);
		pr(root->data);
	}
}

void preorder(struct bs_tree *tree, print pr){
	preorder_walk(tree->root, pr);
	printf("\n");
}

void preorder_walk(struct node *root, print pr){
	if(root){
		pr(root->data);
		preorder_walk(root->left, pr);
		preorder_walk(root->right, pr);
	}
}

struct node *node_search(struct node *root, void *key, comp eq){
	if(!root || root->data == key){
		return root;
	}
	else if(eq(root->data, key) < 0){
		return node_search(root->right, key, eq);
	}
	else{
		return node_search(root->left, key, eq);
	}
}

struct node *tree_search(struct bs_tree *tree, void *key, comp eq){
	return node_search(tree->root, key, eq);
}
	
struct node *iter_search(struct bs_tree *tree, void *key, comp eq){
	return iter_search_node(tree->root, key, eq);
}

struct node *iter_search_node(struct node *root, void *key, comp eq){
	struct node *temp = root;
	while(temp && key != temp->data){
		if(eq(temp->data, key) < 0){
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

void tree_insert_node(struct bs_tree *tree, struct node *key, comp eq){
	insert_node(tree->root, key, eq);
	++(tree->size);
}

void insert_el(struct bs_tree *tree, void *el, comp eq){
	tree_insert_node(tree, create_node(el), eq);
}

void insert_int(struct bs_tree *tree, int *x){
	insert_el(tree, (void *)x, (comp)int_comp);
}


void insert_node(struct node *root, struct node *key, comp eq){
	struct node *x = root;
	struct node *y = NULL;
	while(x){
		y = x;
		if(eq(x->data, key->data) < 0){
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
	else if(eq(key->data, y->data) < 0){
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

struct node *delete_node(struct bs_tree *tree, struct node *key, comp eq){
	if(!key->left){
		transplant(tree, key, key->right);
	}
	else if(!key->right){
		transplant(tree, key, key->left);
	}
	else{
		struct node *y = min(key->right);
		if(eq(y->parent, key)){
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

struct node *delete_el(struct bs_tree *tree, void *x, comp eq){
	return delete_node(tree, iter_search(tree, x, eq), eq);
}

struct node *delete_int(struct bs_tree *tree, int x){
	comp eq = (comp)int_comp;
	return delete_el(tree, iter_search(tree, (void *)&x, eq), eq);
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

int int_comp(int *x, int *y){
	return (*x < *y) ? -1 : (*x > *y) ? 1 : 0;
}

void int_print(int *x){
	printf("%d ", *x);
}


int main(void){
	int arr[19] = {50,65,60,55,30,20,40,5,22,25,
				72,95,35,75,47,78,34,76,32};
	int i=0;
	struct bs_tree *root = create_tree((void *)&arr[i++]);
	
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	insert_int(root, &arr[i++]);
	inorder(root, (print)int_print);
	
	struct node *temp, *t1;
	for(temp = tree_min(root); temp; temp = t1){
		t1 = successor(temp);
		destroy_node(delete_node(root, temp, (comp)int_comp));
		inorder(root, (print)int_print);
	}
	
	free_tree(root);
	
	return 0;
}
