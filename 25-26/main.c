#include <stdio.h>
#include "stack.h"
#include "sort.h"

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
