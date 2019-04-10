#include <stdio.h>
#include "stack.h"
#include "sort.h"

int main(void)
{
	char c;
	int st;
	int val;
	Stack *A[10];
	while (1){
	scanf("%c %d", &c, &st);
	switch (c) {
		case 'c':
			A[st] = stack_create();
			break;
		case 'd':
			stack_delete(&A[st]);
			break;
		case 'i':
			scanf("%d", &val);
			stack_push(A[st], val);
			break;
		case 'o':
			stack_pop(A[st]);
			break;
		case 's':
			sort(A[st]);
			break;
		case 'p':
			stack_print(A[st]);
			break;
		default:
			printf("Wrong syntax\n");
			break;
	}
	getchar();
	}
	return 0;	
}
