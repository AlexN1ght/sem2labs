#include "Dayk.h"

int is_num(char a);
int is_alpha(char a);
int is_op(char a);
int is_left_a(char a);
int is_right_a(char a);
int op_prior(char a);

List* StrToRPN(const char* str)
{
	List* out = list_create();
	List* stack = list_create();
	char tmp[20];
	char c;
	int min = 0;
	int num_itr = 0;
	for(int i = 0; i < strlen(str) || min == 1; i++) {
		c = str[i];
		if(is_num(c)) {
			tmp[num_itr] = c;
			num_itr++;
			continue;
		}else if (num_itr != 0) {
			tmp[num_itr] = '\0';
			num_itr = 0;
			list_push_front(out, tmp);
			if(min == 1) {
				c = ')';
				i--;
				min = 0;
			}
		}
		if(is_alpha(c)){
			if (i == 0) {
				tmp[0] = c;
				tmp[1] = '\0';
				list_push_front(out, tmp);
			} else if (is_op(str[i-1]) || str[i-1] == '(') {
				tmp[0] = c;
				tmp[1] = '\0';
				list_push_front(out, tmp);
			} else {
				list_destroy(&stack);
				list_destroy(&out);
				return NULL;
			}
			if(min == 1) {
				c = ')';
				min = 0;
			}
		}
		if(c == '(') {
			tmp[0] = c;
			tmp[1] = '\0';
			list_push_front(stack, tmp);
		} else if(c == ')') {
			while(list_peak(stack, -1)[0] != '(') {
				if(list_peak(stack, -1) != NULL) {
					list_push_front(out, list_pop_front(stack));
				} else {
					list_destroy(&stack);
					list_destroy(&out);
					return NULL;
				}
			}
			list_pop_front(stack);

		} else if(is_op(c)) {
			if(c == '-'){
				if(i == 0){
					tmp[0] = '(';
					tmp[1] = '\0';
					list_push_front(stack, tmp);
					tmp[0] = '0';
					tmp[1] = '\0';
					list_push_front(out, tmp);
					min = 1;
				} else if (str[i-1] == '(' || str[i-1] == '^') {
					tmp[0] = '(';
					tmp[1] = '\0';
					list_push_front(stack, tmp);
					tmp[0] = '0';
					tmp[1] = '\0';
					list_push_front(out, tmp);
					min = 1;
				}
			}
			if(list_peak(stack, -1) != NULL) {
				while(is_op(list_peak(stack, -1)[0]) &&\
						list_peak(stack, -1)[0] != c &&\
						((is_left_a(c) && op_prior(c) <= op_prior(list_peak(stack, -1)[0])) ||\
						(is_right_a(c) && op_prior(c) < op_prior(list_peak(stack, -1)[0]) ))) 
				{
					list_push_front(out, list_pop_front(stack));
					if(list_peak(stack, -1) == NULL) {
						break;
					}
				}
			}
			tmp[0] = c;
			tmp[1] = '\0';
			list_push_front(stack, tmp);
		}

	}
	if (num_itr != 0) {
		tmp[num_itr] = '\0';
		num_itr = 0;
		list_push_front(out, tmp);
	}
	if(list_peak(stack, -1) != NULL) {
		while(list_peak(stack, -1)[0] != '(' && list_peak(stack, -1)[0] != ')') {
			list_push_front(out, list_pop_front(stack));
			if(list_peak(stack, -1) == NULL) {
				break;
			}
		}
	}
	list_destroy(&stack);
	return out;
}

int is_num(char a)
{
	return ((a - '0') >= 0 && (a - '0') <= 9) ? 1 : 0;
}
int is_alpha(char a)
{
	return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') ? 1 : 0;
}
int is_op(char a)
{
	return a == '+' || a == '-' || a == '*' || a == '/' || a == '^' ? 1 : 0;
}
int is_left_a(char a)
{
	return a == '+' || a == '-' || a == '*' || a == '/' ? 1 : 0;
}
int is_right_a(char a)
{
	return a == '^' ? 1 : 0;
}
int op_prior(char a)
{
	if(a == '+' || a == '-') {
		return 1;
	} else if(a == '*' || a == '/') {
		return 2;
	} else if(a == '^') {
		return 3;
	}
	return 0;
}