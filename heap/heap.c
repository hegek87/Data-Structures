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

void max_heapify(int *heap_data, int initial){
	int left = LEFT(initial), right = RIGHT(initial);
	int temp = *(heap_data + initial);
	int left_key = *(heap_data+left), right_key = *(heap_data+right);
	int largest = (left_key HEAP_TYPE temp) ? left : initial;
	largest = (*(heap_data + largest)HEAP_TYPE right_key) ? largest : right;
	//BAD TEMP FIX FOR THE NIGHT (WILL FIX TOMORROW)
	if(largest > 4) return;
	if(largest != initial){
		swap((heap_data + initial), (heap_data + largest));
		max_heapify(heap_data, largest);
	}
}

struct heap *build_max_heap(int *heap_data, int heap_size);
void max_heap_insert();
int heap_extract_max(struct heap *);
void heap_increase_key(struct heap *, int, int);
int heap_max(struct heap *);

int main(void){
	int *x = calloc(sizeof(int), 4);
	//malloc(4 * sizeof(int));
	int a = 10, b = 14, c = 9;
	*(x+1) = a, *(x+2) = b, *(x+3) = c;
	printf("Heap data:\n\tPARENT: %d\n\tLEFT: %d\n\tRIGHT: %d\n",
		*(x+1), *(x+2), *(x+3));
	max_heapify(x, 1);
	printf("Heap data:\n\tPARENT: %d\n\tLEFT: %d\n\tRIGHT: %d\n",
		*(x+1), *(x+2), *(x+3));
	return 0;
}
