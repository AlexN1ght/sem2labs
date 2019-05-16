#include <stdio.h>
#include "Dayk.h"
#include "Stack.h"
#include "Bitree.h"
#include "Lin-2-list-barrier.h"

BTNode* RPNtoTree(List* list);

int main (void)
{
    char e[100];
    //char* e = "(3+6)*(8+298)/x^4+(-2)";
    scanf("%s", e);
    List* out = StrToRPN(e);
    list_print(out);
    BTNode* e1 = RPNtoTree(out);
    printTree(e1, 0);
    list_destroy(&out);
    treeDestroy(&e1);
    return 0;
}

BTNode* RPNtoTree(List* list)
{
    if (list != NULL) {
        Stack *stack = stack_create();
        BTNode* node;
        char* tmp;
        while(list_peak(list, 1) != NULL) {
            tmp = list_pop_back(list);
            if(is_op(tmp[0])) {
                node = createTree(tmp);
                addRightTree(node,stack_pop(stack));
                addLeftTree(node,stack_pop(stack));
                stack_push(stack, node);
            } else {
                stack_push(stack, createTree(tmp));
            }
            free(tmp);
        }
        node = stack_pop(stack);
        stack_delete (&stack);
        return node;
    } else {
        return NULL;
    }
}
