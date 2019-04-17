#include<stdio.h>
#include"GTree.h"

enum state {
	space,
	add_path,
	print,
	other,
	delete_node,
	quit,
	deep_of_max_i
};

int is_space(char c) 
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int main(void)
{
	enum state st = space;
	char comm[20];
	char c = 0;
	int root = 0;
	int a = 0;
	GTnode *tree;
	while (c != EOF) {
	c = getchar();
		switch (st) {
			case space:
				if (c == '+') {
					st = add_path;
				} else if (c == '-') {
					st = delete_node;
				} else if (c == 'p') {
					st = print;
				} else if (is_space(c)) {
					st = space;
				} else if (c == 'q') {
					st = quit;
				} else if (c == 'd') {
					st = deep_of_max_i;
				} else {
					st = other;
				}
				break;
			case add_path:
				if (c == 's' || c == 'b') {
					comm[a] = c;
					a++;
				} else if (c == 'r' && !root) {
					comm[a] = c;
					a++;
					root = 1;
				} else if (is_space(c)) {
					comm[a] = '\0';
					if (root) {
						if (add_node(&tree, comm) == NULL) {
							puts("?");
						}
					}
					a = 0;
					st = space;
				} else {
					st = other;
					a = 0;
				}
				break;
			case delete_node:
				if (c == 's' || c == 'b' || c == 'r') {
					comm[a] = c;
					a++;
				} else if (is_space(c)) {
					comm[a] = '\0';
					if (root) {
						switch (del_node(&tree, comm)){
							case 0:
								puts("?");
								break;
							case -1:
								root = 0;
								break;
						}
					} else {
						puts("?");
					}
					a = 0;
					st = space;
				} else {
					st = other;
					a = 0;
				}
				break;
			case print:
				if (is_space(c)) {
					if (root) {
						print_gtree(tree);
					} else {
						puts("?");
					}
					st = space;
				} else {
					st = other;
				}
				break;
			case deep_of_max_i:
				if (is_space(c)) {
					if (root) {
						printf("%d\n", max_i_deep(tree));
					}
					st = space;
				} else {
					st = other;
				}
				break;
				break;
			case quit:
				del_node(&tree, "r");
				return 0;
				break;
			case other:
				if (is_space(c)) {
					puts("?");
					st = space;
				}
				break;
		}
	}
}
