#ifndef HEAP_H
#define HEAP_H
#define HEAP_TYPE MAX
#define MAX >
#define MIN <

#define PARENT(X) ( ((X)-0x1) >> 1)
#define LEFT(X) ((X) << 1) + 0x1
#define RIGHT(X) (((X) << 1) + 0x2)

//0<=heap_size<=data_length
struct heap{
	int heap_size;
	int data_length;
	int *data;
};

int max(int, int, int);

void heapify(int *, int, int);
struct heap *build_heap(int *, int);
void max_heap_insert();
int heap_extract_max(struct heap *);
void heap_increase_key(struct heap *, int, int);
int heap_max(struct heap *);
void print_heap(struct heap *);

void heapsort(int[], int);

#endif
