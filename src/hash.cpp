#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#define SIZE 6
#define T Hash_T

T *chain[SIZE];

void Hash_init() {
	int i;
	for (i = 0; i < SIZE; i++)
		chain[i] = NULL;
}
T *Hash_new(int val) {
	T *n = (T*)malloc(sizeof(T));
	n->next = NULL;
	n->val  = val;
	return n;
}
void Hash_insert(int val) {
	T *n = Hash_new(val);
	int key = val % SIZE;
	if (chain[key] == NULL)
		chain[key] = n;
	else
	{
		T *t = chain[key];
		while (t->next)
			t = t->next;
		t->next = Hash_new(val);
	}
}
void Hash_print() {
	int i;
	for (i = 0; i < SIZE; i++) {
		printf("chain[%d] ", i);
		T *t = chain[i];
		while (t) {
			printf("%d --> ", t->val);
			t = t->next;
		}
		printf("\n");
	}
	printf("\n");
}


int Hash_test() {
	printf("Hash testing [separate chaining]\n");
	Hash_init();

	int i;
	for (i = 0; i < 40; i++)
		Hash_insert(i);

	Hash_print();	
	printf("\n");
	return 0;
}
#undef T