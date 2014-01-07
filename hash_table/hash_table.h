#ifndef HASH_H
#define HASH_H
#include "../double_linked_list/double_linked_list.h"

struct hash_table{
	struct dl_list **table;
	int table_size;
};

//returns 0 on equality, <0 if first el < second el, >0 otherwise
typedef int (*comp)(const void *, const void *);
typedef int (*hash)(struct hash_table *, const void *);

struct hash_table *init_table(int);
void *hash_delete(struct hash_table *, void *, comp, hash);
struct node *hash_search(struct hash_table *, const void *, comp, hash);
int hash_insert(struct hash_table *, void *, hash);

int int_hash(struct hash_table *, const int *);
int int_comp(int *x, int *y);

void display_hash_table(struct hash_table *);

void destroy_table(struct hash_table *h_table);

#endif
