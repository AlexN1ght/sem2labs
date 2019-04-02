#include "stack.h"
#include "sort.h"

void stack_concatenation(Stack *A, Stack *B)
{
	Stack *T = stack_create();
	while(!stack_is_empty(B)) {
		stack_push(T, stack_pop(B));
	}
	while(!stack_is_empty(T)) {
		stack_push(A, stack_pop(T));
	}
	stack_delete(&T);
}


void sort(Stack *A)
{
	int a;
	int key = stack_pop(A);
	Stack *L = stack_create();
	Stack *G = stack_create();
	while(!stack_is_empty(A)) {
		a = stack_pop(A);
		if ( a < key) {
			stack_push(L, a);
		} else {
			stack_push(G, a);
		}
	}
	if (stack_size(L) > 1) {
		sort(L);
	}
	if (stack_size(G) > 1) {
		sort(G);
	}
	stack_push(L, key);
	stack_concatenation(L, G);
	stack_concatenation(A, L);
	stack_delete(&L);
	stack_delete(&G);
}
