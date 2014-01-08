#ifndef HEAP_H
#define HEAP_H
#define HEAP_TYPE MAX
#define MAX >
#define MIN <

#define MAX_INT 0x7FFF
#define MIN_INT -0x7FFF

#define PARENT(X) ( ((X)-0x1) >> 1)
#define LEFT(X) ((X) << 1) + 0x1
#define RIGHT(X) (((X) << 1) + 0x2)

//0<=heap_size<=data_length
struct heap{
	int heap_size;
	int data_length;
	void *data;
};

typedef int (*comp)(void *, void *);
typedef void (*print)(void *);

int max(int, int, int);

void heapify(int *, int, int, comp);
struct heap *build_heap(int *, int, comp);
void insert(struct heap *, int);
int heap_extract_top(struct heap *, comp);
int heap_modify_key(struct heap *, int, int);
int heap_top(struct heap *);
void print_heap(struct heap *, print);

void heapsort(int[], int, comp);

#endif
