#ifndef BINHEAP_INCLUDED
#define BINHEAP_INCLUDED

typedef struct node {
	int data;
	struct node *left, *right;
} node_t;

typedef struct heap {
	int capac;
	int size;
	node_t **arr;
} heap_t;



void heap_push(heap_t *heap, int data);
node_t *heap_pop(heap_t *heap);
node_t *heap_extractmin(heap_t *heap);
void heap_arrshow(heap_t *heap);
int binheap_test();


#endif