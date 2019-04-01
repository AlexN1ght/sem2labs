#include "stack.h"
#include "sort.h"

void stack_concatination(Stack *A, Stack *B)
{
	A->size = A->top + B->top + 1;
	A->data = realloc(A->data, A->size * sizeof(data_type));
	for(int i = 0; i + 1 <= B->top; i++)
	{
		A->data[A->top + i] = B->data[i];
	}
	A->top = A->top + B->top;
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
	stack_concatination(L, G);
	stack_concatination(A, L);
	stack_delete(&L);
	stack_delete(&G);
}
