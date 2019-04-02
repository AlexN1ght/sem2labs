#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

typedef int data_type;

typedef struct {
    data_type *data;
    size_t size;
    size_t top;
} Stack;

<<<<<<< HEAD
Stack* stack_create(void)
{
    Stack *out = NULL;
    out = malloc(sizeof(Stack));
    if (out == NULL) {
        exit(OUT_OF_MEMORY);
    }
    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(data_type));
    if (out->data == NULL) {
        free(out);
        exit(OUT_OF_MEMORY);
    }
    out->top = 0;
    return out;
}

void stack_delete (Stack **stack) {
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}

void resize(Stack *stack) {
    stack->size *= MULTIPLIER;
    stack->data = realloc(stack->data, stack->size * sizeof(data_type));
    if (stack->data == NULL) {
        exit(STACK_OVERFLOW);
    }
}

int stack_is_empty(Stack *stack)
{
return stack->top == 0;
}

void stack_push(Stack *stack, data_type value)
{
	if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

data_type stack_pop(Stack *stack)
{
	if (stack->top == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    return stack->data[stack->top];
}

data_type peek(Stack *stack) {
    if (stack->top <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->top - 1];
}

void stack_print(Stack *stack)
{
	for(int i = 0; i + 1 <= stack->top; i++)
	{
		printf("%d\n", stack->data[i]);
	}
}

size_t stack_size(Stack *stack)
{
	return stack->top;
}

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
=======
Stack* stack_create(void);
void stack_delete (Stack **stack);
int stack_is_empty(Stack *stack);
void stack_push(Stack *stack, data_type value);
data_type stack_pop(Stack *stack);
void stack_print(Stack *stack);
size_t stack_size(Stack *stack);
>>>>>>> 299ed6d8af1eed78c2eca853f330ecda7be48410

#endif
