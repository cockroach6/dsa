#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

/*
	implement min heap tree saved in array
	+ push
	+ pop
	+ excract min
*/

static void heap_errmsg(const char *msg) {
	fprintf(stderr, "Error: heap tree %s\n", msg);
}

static void heap_swap(node_t *a, node_t *b) {
	node_t tmp = *a;
	*a = *b;
	*b = tmp;
}

static node_t *heap_node(int data) {
	node_t *node = (node_t*)malloc(sizeof(node_t));
	node->data   = data;
	node->left   = node->right = NULL;
	return node;
}

static heap_t *heap_make(int capac) {
	heap_t *heap = (heap_t*)malloc(sizeof(heap_t));
	heap->capac	 = capac;
	heap->size   = 0;
	heap->arr    = (node_t**)malloc(sizeof(node_t*) * capac);
	return heap;
}

static void heap_minheapify(heap_t *heap, int i) {
	if (heap->size + 1 >= heap->capac) 
		heap_errmsg("overflow");

	int small= i;
	int size = heap->size;
	int l    = 2 * i + 1;
	int r    = 2 * i + 2;

	if (l < size && heap->arr[l] < heap->arr[small])
		small = l;
	if (r < size && heap->arr[r] < heap->arr[small])
		small = r;
	if (small != i) {
		heap_swap(heap->arr[i], heap->arr[small]);
		heap_minheapify(heap, small);
	}
}

static void heap_struct(heap_t *heap) {
	int size = heap->size;
	int i = size / 2 - 1;
	for ( ; i >= 0; i--)
		heap_minheapify(heap, i);
}

void heap_push(heap_t *heap, int data) {
	if (heap->size + 1 > heap->capac)
		heap_errmsg("overflow");

	node_t *node = heap_node(data);
	heap->arr[heap->size] = node;
	heap->size++;
	heap_struct(heap);
}

node_t *heap_pop(heap_t *heap) {
	int size = --heap->size;
	node_t *node = heap->arr[size];
	return node;	
}

node_t *heap_extractmin(heap_t *heap) {
	int size = --heap->size;
	node_t *tmp  = heap->arr[0];
	heap->arr[0] = heap->arr[size];
	heap_struct(heap);

	return tmp;
}

void heap_arrshow(heap_t *heap) {
	int size = heap->size;
	for (int i = 0; i < size; i++)
		printf("%d ", heap->arr[i]->data);
	printf("\n");
}

int binheap_test()
{
	int capac = 10;
	heap_t *heap = heap_make(capac);	
	heap_push(heap, 13);
	heap_push(heap, 2);
	heap_push(heap, 7);
	heap_push(heap, 21);
	heap_push(heap, 38);
	heap_push(heap, 8);


	printf("\n\nBinary Heap Tree:\n");
	heap_arrshow(heap);

	printf("\npush one:\n");
	heap_push(heap, 34);
	heap_arrshow(heap);

	printf("\npop one:\n");
	heap_pop(heap);
	heap_arrshow(heap);


	printf("\noverflow defense:\n");
	heap_push(heap, 56);
	heap_push(heap, 4);
	heap_push(heap, 0);
	printf("\n");
	return 0;
}