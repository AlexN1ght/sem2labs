#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include "Bitree.h"

typedef BTNode* stack_data_type;

typedef struct {
    stack_data_type *data;
    size_t size;
    size_t top;
} Stack;

Stack* stack_create(void);
void stack_delete (Stack **stack);
int stack_is_empty(Stack *stack);
void stack_push(Stack *stack, stack_data_type value);
stack_data_type stack_pop(Stack *stack);
void stack_print(Stack *stack);
size_t stack_size(Stack *stack);

#endif
