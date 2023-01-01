#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "llist.h"
#define T List_T

T *List_init(int val) {
	T *head = (T *)malloc(sizeof (T));
	head->val  = val;
	head->next = NULL;
	return head;
}
T *List_new(int val) {
	T *node = (T *)malloc(sizeof (T));
	node->val = val;
	node->next = NULL;
	return node;
}
void List_push(T **head, int val) {
	if (*head == NULL)
		return ;
	T *node = List_new(val);
	node->next = (*head);
	(*head) = node;	
}
int List_pop(T **head) {
	assert(head != NULL);
	T *prev = (*head)->next;
	int retval;
	retval = (*head)->val;
	free(*head);
	*head = prev;
	return retval;
}
void List_append(T *head, int val) {
	T *cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = List_new(val);
}
void List_print(T *head) {
	T *cur = head;
	while (cur) {
		printf("%d ", cur->val);
		cur = cur->next;
	}
	printf("\n");
}
void List_rprint(T *head) {
	T *cur = head;
	if (head->next != NULL)
		List_rprint(cur->next);
	printf("%d ", cur->val);
}

int List_test()
{
	printf("List testing [display]\n");
	T *head = List_init(1);
	List_push(&head, 2);
	List_push(&head, 3);
	List_pop(&head);
	List_append(head, 4);
	List_append(head, 5);
	List_push(&head, 10);

	printf("simple:\t\t");
	List_rprint(head);
	printf("\nrecursive:\t");
	List_print(head);
	return 0;
}
#undef T

