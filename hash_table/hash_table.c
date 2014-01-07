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

int hash(struct hash_table *table, void *el){
	int *x = (int *)el;
	return *el % table->size;
}

struct hash_table *init_table(int size){
	struct hash_table *temp = malloc(sizeof(hash_table));
	temp->table_size = size;	
	temp->table = malloc(size * sizeof(struct dl_list));
	return temp;
}

void *hash_delete(struct hash_table *h_table, void *el, comp eq){
	struct node *temp = hash_search(h_table, el, eq);
	if(!temp){
		void *retval = temp->data;
		delete_node((h_table->table + hash(h_table, el)), temp);
		free(temp);
		return retval;
	}
	return NULL;
}
	
struct node *hash_search(struct hash_table *h_table, const void *el, comp eq){
	int hash_val = hash(h_table, el);
	if(!(h_table->table+hash_val)){
		return NULL;
	}
	struct node *cur_node = (h_table->table+hash_val)->head;
	while(cur_node){
		if(eq(cur_node->data, el)){
			return cur_node;
		}
		cur_node = cur_node->next;
	}
	return NULL;
}
	
int hash_insert(struct hash_table *h_table, void *el)
	int hash_val = hash(h_table, el);
	if(!(h_table->table + hash_val)){
		h_table->table+hash_val = create_empty_list();
	}
	insert_el_head(h_table->table+hash_val, el);
	return 0;
}

int main(void){
	printf("HI\n");
	return 0;
}
