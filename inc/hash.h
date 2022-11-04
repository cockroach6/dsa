#ifndef HASH_INCLUDED
#define HASH_INCLUDED
#define T Hash_T

typedef struct T {
	struct T *next;
	int val;
} T;

void Hash_init();
T *Hash_new(int val);
void Hash_insert(int val);
void Hash_print();
int Hash_test();

#undef T
#endif