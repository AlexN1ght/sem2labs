#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

typedef int data_type;

typedef struct {
    data_type *data;
    size_t size;
    size_t top;
} Stack;

Stack* stack_create(void);
void stack_delete (Stack **stack);
int stack_is_empty(Stack *stack);
void stack_push(Stack *stack, data_type value);
data_type stack_pop(Stack *stack);
void stack_print(Stack *stack);
size_t stack_size(Stack *stack);

#endif
