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
<<<<<<< HEAD:26/hoar_sort.c
	putchar('\n');
	puts("-------------------------");
	stack_print(A);
	puts("-------------------------");
	sort(A);
	stack_print(A);
	return 0;	
=======
	A->top = A->top + B->top;
>>>>>>> 299ed6d8af1eed78c2eca853f330ecda7be48410:26/sort.c
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
