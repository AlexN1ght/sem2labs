#include <stdio.h>
#include "Stack.h"

#define INIT_SIZE 10
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102
#define MULTIPLIER 2

Stack* stack_create(void)
{
    Stack *out = NULL;
    out = malloc(sizeof(Stack));
    if (out == NULL) {
        exit(OUT_OF_MEMORY);
    }
    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(stack_data_type));
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
    stack->data = realloc(stack->data, stack->size * sizeof(stack_data_type));
    if (stack->data == NULL) {
        exit(STACK_OVERFLOW);
    }
}

int stack_is_empty(Stack *stack)
{
return stack->top == 0;
}

void stack_push(Stack *stack, stack_data_type value)
{
	if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

stack_data_type stack_pop(Stack *stack)
{
	if (stack->top == 0) {
        return NULL;
    }
    stack->top--;
    return stack->data[stack->top];
}

void stack_print(Stack *stack)
{
	for(int i = 0; i + 1 <= stack->top; i++)
	{
		printTree(stack->data[i], 0);
	}
}

size_t stack_size(Stack *stack)
{
	return stack->top;
}
