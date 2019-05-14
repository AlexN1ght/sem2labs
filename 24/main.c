#include<stdio.h>
#include"Dayk.h"
#include"Lin-2-list-barrier.h"

int main (void)
{
    char* e = "-2*(-7)";
    List* out = StrToRPN(e);
    list_print(out);
    return 0;
}
