#ifndef LLIST_INCLUDED
#define LLIST_INCLUDED
#define T List_T
typedef struct T {
	struct T *next;
	int val;
} T;

T *List_init(int val);
T *List_new(int val);
void List_push(T **head, int val);
int List_pop(T **head);
void List_append(T *head, int val);
void List_print(T *head);
void List_rprint(T *head);
int List_test();

#undef T
#endif