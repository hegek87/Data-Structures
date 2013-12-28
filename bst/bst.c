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
	temp->left = temp->right = NULL;
	return temp;
}

void destroy_node(struct node *to_die){
	//free(to_die->data);
	free(to_die);
}


struct node *create_tree(const int x){
	return create_node(x);
}

void inorder_walk(struct node *root){
	if(root){
		inorder_walk(root->left);
		printf("%d ", root->data);
		inorder_walk(root->right);
	}
}

void postorder_walk(struct node *root){
	if(root){
		postorder_walk(root->left);
		postorder_walk(root->right);
		printf("%d ", root->data);
	}
}

void preorder_walk(struct node *root){
	if(root){
		printf("%d ", root->data);
		preorder_walk(root->left);
		preorder_walk(root->right);
	}
}

struct node *tree_search(struct node *root, const int key){
	if(root->data == key || !root){
		return root;
	}
	else if(root->data < key){
		return tree_search(root->right, key);
	}
	else{
		return tree_search(root->left, key);
	}
}
	
struct node *iter_search(struct node *root, const int key){
	struct node *temp = root;
	while(key != temp->data && temp){
		if(temp->data < key){
			temp = temp->right;
		}
		else{
			temp = temp->left;
		}
	}
	return temp;
}

struct node *max(struct node *root){
	if(!root->right){
		return root;
	}
	return root->right;
}

struct node *min(struct node *root){
	if(!root->left){
		return root;
	}
	return root->left;
}

//TEST
struct node *successor(struct node *root);
struct node *predecessor(struct node *root);


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
		
			
void insert_int(struct node *root, const int x){
	insert_node(root, create_node(x));
}


struct node *delete_node(struct node *root, struct node *key);
struct node *delete_el(struct node *root, const int x);

void free_tree(struct node *root){
	if(root){
		struct node *temp = root;
		free_tree(temp->left);
		free_tree(temp->right);
		free(temp);
	}
}


int main(void){
	struct node *root = create_tree(50);
	insert_int(root, 10);
	insert_int(root, 76);
	insert_int(root, 45);
	insert_int(root, 72);
	insert_int(root, 0);
	insert_int(root, 91);
	insert_int(root, 42);
	insert_int(root, 64);
	
	
	inorder_walk(root);
	printf("\n");
	free_tree(root);
	return 0;
}
