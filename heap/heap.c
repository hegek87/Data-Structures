#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "heap.h"

int max(int a, int b, int c){
	int temp = a > b ? a : b;
	return temp > c ? temp : c;
}

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

void heapify(int *heap_data, int initial, int heap_size){
	int left = LEFT(initial), right = RIGHT(initial);
	int temp = *(heap_data + initial);
	int left_key = *(heap_data+left), right_key = *(heap_data+right);
	int largest = (left_key HEAP_TYPE temp) ? left : initial;
	largest = (*(heap_data + largest)HEAP_TYPE right_key) ? largest :right;
	if(largest > heap_size) return;
	if(largest != initial){
		swap((heap_data + initial), (heap_data + largest));
		heapify(heap_data, largest, heap_size);
	}
}

struct heap *build_heap(int *heap_data, int heap_size){
	struct heap *new_heap = malloc(sizeof(struct heap));
	new_heap->heap_size = new_heap->data_length = heap_size;
	int i = heap_size / 2;
	while(i >= 0){
		//printf("hapify(heap_data, %d, %d);\n", i, heap_size);
		heapify(heap_data, i, heap_size);
		--i;
	}
	new_heap->data = heap_data;
	return new_heap;
}

void heap_insert(struct heap *heap, int key){
	if(heap->heap_size >= heap->data_length){
		int *temp = calloc(2*heap->heap_size, sizeof(int));
		memcpy(temp, heap->data, sizeof(int));
		heap->data = temp;
	}
	
	heap->heap_size += 1;
	*((heap->data)+(heap->heap_size)) = MIN_INT;
	if(!heap_modify_key(heap, heap->heap_size, key)){
		return;
	}
	*((heap->data)+(heap->heap_size)) = MAX_INT;
	heap_modify_key(heap, heap->heap_size, key);
	return;
	
}

int heap_extract_top(struct heap *h){
	if(h->heap_size < 0){
		perror("Heap underflow\n");
	}
	int max = *(h->data);
	*(h->data) = *(h->data + h->heap_size);
	h->heap_size -= 1;
	heapify(h->data, 0, h->heap_size);
	return max;
}

//returns 0 if successful, -1 if error occurs
int heap_modify_key(struct heap *heap, int i, int key){
	if(key HEAP_TYPE *((heap->data)+i)){
		return -1;
	}
	*((heap->data)+i) = key;
	int p = PARENT(i);
	while(i > 0 && *((heap->data+p)) HEAP_TYPE *((heap->data)+i)){
		swap(heap->data+p, heap->data+i);
		i = p;
	}
	return 0;
}

int heap_top(struct heap *heap){
	return *(heap->data);
}

void print_heap(struct heap *heap){
	int *p = heap->data, i = 0;
	for( ; i++ <= heap->heap_size; ++p){
		printf("%d ", *p);
	}
	printf("\n");
}

void heapsort(int to_sort[], int length){
	struct heap *h = build_heap(to_sort, length-1);
	int i = h->heap_size+1;
	while(i >= 1){
		swap(h->data, (h->data + i-1));
		h->heap_size -= 1;
		heapify(h->data, 0, h->heap_size);
		--i;
	}
}

int main(void){
	int *x;
	int arr[13] = {5,2, 4,12,42,5,25,63,2,6,24,13,2};
	x=arr;
	struct heap *h = build_heap(x, 12);
	print_heap(h);
	//heap_insert(h, 1700);
	int i = h->heap_size+1;
	while(i > 0){
		printf("%d ", heap_extract_top(h));
		--i;
	}
	printf("\n");
	/*
	int i = 0;
	for(i = 0; i < 13; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
	struct heap *t = build_heap(x, 12);
	print_heap(t);
	printf("Top element: %d\n", heap_top(t));
	int arr1[10] = {10,9,8,7,6,5,4,3,2,1};
	struct heap *t1 = build_heap(arr1, 9);
	//heapsort(arr1, 10);
	
	for(i = t1->heap_size;i >= 0; --i){
		printf("%d\n", heap_extract_top(t1));
	}
	//printf("\n");
	*/
	return 0;
}
