#ifndef HASH_H
#define HASH_H
#include "../double_linked_list/double_linked_list.h"

struct hash_table{
	struct dl_list *table;
	int table_size;
};

typedef int (*comp)(const void *, const void *);

struct hash_table *init_table(int);
int hash(struct hash_table *, void *, comp);
void *hash_delete(struct hash_table *, void *);
void *hash_search(struct hash_table *, const void *, comp);
int hash_insert(struct hash_table *, void *)

#endif
