#ifndef HEAP_H
#define HEAP_H
#define HEAP_TYPE MIN
#define MAX >
#define MIN <

#define PARENT(X) ( (X) >> 1)
#define LEFT(X) ((X) << 1)
#define RIGHT(X) (((X) << 1) + 0x1)

struct heap{
	int heap_size;
	int *data;
};

int max(int, int, int);

void max_heapify(int *, int);
struct heap *build_max_heap(int *, int);
void max_heap_insert();
int heap_extract_max(struct heap *);
void heap_increase_key(struct heap *, int, int);
int heap_max(struct heap *);

#endif
