#ifndef _SORT_H_
#define _SORT_H_

typedef int GTdata;

typedef struct GTnode {
	GTdata data;
	struct GTnode *son;
	struct GTnode *brother;
} GTnode;

void print_gtree(GTnode *n);
GTnode *create_node(int a);
GTnode* add_node(GTnode **node, const char *a);
void del_node_supp(GTnode **n);
int del_node(GTnode **n, const char* comm);
GTnode** node_path(GTnode** node, const char* a);
int max_i_deep(GTnode *n);

#endif
