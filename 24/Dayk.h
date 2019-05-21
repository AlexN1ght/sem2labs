#ifndef _DAYK_H_
#define _DAYK_H_

#include <string.h>
#include "Lin-2-list-barrier.h"

List* StrToRPN(const char*);
int is_op(char a);
int is_num(char a);
int is_alpha(char a);

#endif
