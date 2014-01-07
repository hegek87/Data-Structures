#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "hash_table.h"

/*
	we will assume that elements in the table are integers
	for ease, however, the table is set up to work for any
	arbitrary data type.
	
	To set up a table for any arbitrary data type, we must
	specify a hash function for the data type, as well as
	constructing a comparison function for the search and
	delete functions.
*/

int int_hash(struct hash_table *table, const int *el){
	return *el % table->table_size;
}

struct hash_table *init_table(int size){
	struct hash_table *temp = malloc(sizeof(struct hash_table));
	temp->table_size = size;	
	temp->table = malloc(size * sizeof(struct dl_list));
	return temp;
}

void *hash_delete(struct hash_table *h_table, void *el, comp eq, hash h){
	struct node *temp = hash_search(h_table, el, eq, h);
	if(temp){
		void *retval = temp->data;
		delete_node(*(h_table->table + h(h_table, el)), temp);
		free(temp);
		return retval;
	}
	return NULL;
}
	
struct node *hash_search(struct hash_table *h_table, const void *el,
					 comp eq, hash h){
	int hash_val = h(h_table, el);
	if(!*(h_table->table+hash_val)){
		return NULL;
	}
	struct dl_list *temp = *(h_table->table+hash_val);
	struct node *cur_node = temp->head;
	while(cur_node){
		if(!eq(cur_node->data, el)){
			return cur_node;
		}
		cur_node = cur_node->next;
	}
	return NULL;
}
	
int hash_insert(struct hash_table *h_table, void *el, hash h){
	int hash_val = h(h_table, el);
	if(!*(h_table->table + hash_val)){
		*(h_table->table + hash_val) = create_empty_list();
	}
	insert_el_head(*(h_table->table+hash_val), el);
	return 0;
}

void display_hash_table(struct hash_table *h_table){
	int i;
	for(i = 0; i < h_table->table_size; ++i){
		printf("List in slot %d:\n", i);
		struct dl_list *temp = *(h_table->table + i);
		print_list(temp);
	}
}

int int_comp(int *x, int *y){
	return (*x < *y) ? -1 : (*x > *y) ? 1 : 0;
}

void destroy_table(struct hash_table *h_table){
	//free all lists
	int i = 0;
	while(i < h_table->table_size){
		free_list(*(h_table->table+i));
		++i;
	}
	free(h_table->table);
	free(h_table);
}

int main(void){
	struct hash_table *ht = init_table(15);
	comp c = (comp)int_comp;
	hash h = (hash)int_hash;
	int j = 32, i;
	int p[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	hash_insert(ht, (void *)&j, h);
	
	for(i = 0; i < 15; ++i){
		hash_insert(ht, (void *)&p[i], h);
	}
	
	int a = 48;
	hash_insert(ht, (void *)&a, h);
	
	display_hash_table(ht);
	
	struct node *test = hash_search(ht, &a, c, h);
	if(test){
		int *y = (int *)test->data;
		printf("We have found %d\n", *y);
	}
	void *m = hash_delete(ht, &a, c, h);
	display_hash_table(ht);
	if(m){
		printf("Data deleted: %d\n", *((int *)m));
	}
	int k = 3;
	hash_delete(ht, &k, c, h);
	display_hash_table(ht);
	
	destroy_table(ht);
	
	return 0;
}
