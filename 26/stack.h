#define INIT_SIZE 10

#ifndef _STACK_H_
#define _STACK_H_

typedef int data_type;

typedef struct {
    data_type *data;
    size_t size
    size_t top
} Stack

void stack_create(Stack *out)
{
    *out = NULL;
    out = malloc(sizeof(Stack))
    if (out == NULL) {
        puts(OUT OF MEMORY);
    }
    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(data_type))
    if (out->data == NULL) {
        free(out);
        exit(OUT OF MEMORY);
    }
    out->top = 0;
}
void stack_push(Stack *stack, data_type value)
{
    stack->data[stack->top] = value;
    stack->top++;
}

data_type stack_pop(Stack *stack)
{
    stack->top--;
    return stack->data[stack->top];
}

#endif
