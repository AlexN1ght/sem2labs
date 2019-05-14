#include "Dayk.h"

enum state {
	number;
	space;
};

List* StrToRPN(const char* str)

{
	List* out = list_create();
	List* stack = list_create();
	enum state State = space;
	char tmp[20];
	int tmp_itr = 0;
	for(int i = 0; i < strlen(str); i++) {
		c = str[i];
		switch (State) {
			case number:
				if(is_num(c)) {
					tmp[tmp_itr] = c;
					tmp_itr++;
					break;
				} else if(is_bracket(c)) {
					
				} else if(is_op1) {
					
				} else if(is_op2) {
				
				}
				tmp[tmp_itr] = '\0';
				tmp_itr = 0;
				list_push_front(out, tmp);
				break;
			case space:
				if(is_num(c)) {
					tmp[tmp_itr] = c;
					tmp_itr++;
					break;
				} else if(is_alpha(c)) {
				
				} else if(is_bracket(c)) {
					
				} else if(is_op1) {
					
				} else if(is_op2) {
				
				}
				break;
			case number:
				break;
		}
	}
}
