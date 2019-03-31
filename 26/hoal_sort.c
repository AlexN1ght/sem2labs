#include<stdio.h>

#include"stack.h"

void sort(Stack *A);

int main(void)
{
	int a;
	Stack *A = stack_create();
	while(scanf("%d", &a) == 1) {
		stack_push(A, a);
	}
	puts("-------------------------");
	stack_print(A);
	puts("-------------------------");
	sort(A);
	stack_print(A);
	return 0;	
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
