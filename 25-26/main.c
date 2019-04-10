#include <stdio.h>
#include "stack.h"
#include "sort.h"

int main(void)
{
	char c;
	int st;
	int val;
	Stack *A[10];
	for (int i = 0; i < 10; i++) {
		A[i] = NULL;
	}
	while (1){
		scanf("%c", &c);
		switch (c) {
			case 'c':
				scanf("%d", &st);
				getchar();
				A[st] = stack_create();
				break;
			case 'd':
				scanf("%d", &st);
				getchar();
				if (A[st] != NULL) {
					stack_delete(&A[st]);
				} else {
					printf("Stack dose not exist\n");
				}
				break;
			case 'i':
				scanf("%d", &st);
				if (A[st] == NULL) {
					printf("?\n");
					break;
				}
				while (scanf("%d", &val) == 1) {
					stack_push(A[st], val);
					if (getchar() == '\n') {
						break;
					}
				}
				break;
			case 'o':
				scanf("%d", &st);
				if (A[st] == NULL) {
					printf("?\n");
					break;
				}
				getchar();
				if (!stack_is_empty(A[st])) {
					stack_pop(A[st]);
				} else {
					printf("The stack is empty\n");
				}
				break;
			case 's':
				scanf("%d", &st);
				if (A[st] == NULL) {
					printf("?\n");
					break;
				}
				getchar();
				sort(A[st]);
				break;
			case 'p':
				scanf("%d", &st);
				if (A[st] == NULL) {
					printf("?\n");
					break;
				}
				getchar();
				stack_print(A[st]);
				break;
			case 'q':
				for (int i = 0; i < 10; i++) {
					if (A[i] != NULL) {
						stack_delete(&A[i]);
					}
				}
				return 0;
				break;
			default:
				printf("Unknown command\n");
				break;
		}
		//getchar();
	}	
}
