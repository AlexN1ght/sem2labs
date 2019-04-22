#include"GTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

GTnode *create_node(int a)
{
  GTnode *node = (GTnode *)malloc(sizeof(GTnode));
  node->data = a;
  node->son = NULL;
  node->brother = NULL;
  return node;
}

GTnode* to_son(GTnode *n)
{
	return n->son;
}

GTnode* to_brother(GTnode *n)
{
	return n->brother;
}

GTnode* last_son(GTnode *n)
{
	n = n->son;
	while (n->brother) {
		n = n->brother;
	}
	return n;
}

GTnode* add_node(GTnode **node, const char *a) {
  GTnode* t = *node;
  int value;
  scanf("%d", &value);
  getchar();
  int i = -1;
      while (a[++i] != '\0') {
        if (a[i] == 'r') {
            *node = create_node(value);
            return *node;
          }
        if (a[i] == 's') {
        	t = to_son(t);
        	if (t) {
            	continue;
          	}
          	return NULL;
        }
        if (a[i] == 'b') {
        	t = to_brother(t);
        	if (t) {
          		continue;
          	}
          	return NULL;
        }
    }
    if (t->son != NULL) {
    	t = last_son(t);
    	t->brother = create_node(value);
    	return t->brother;
    } else {
     	t->son = create_node(value);
     	return t->son;
    }
}

GTnode** node_path(GTnode** tree, const char* a)
{
	GTnode **node = tree;
	int i = -1;
      while (a[++i] != '\0') {
      	if (a[i] == 'r') {
      		return tree;
      	}
        if (a[i] == 's') {
        	node = &((*node)->son);
        	if (*node == NULL) {
            	return NULL;
          	}
        }
        if (a[i] == 'b') {
        	node = &((*node)->brother);
        	if (*node == NULL) {
            	return NULL;
          	}
        }
	}
	return node;
}

void del_node_supp(GTnode **n)
{	
	if ((*n)->son != NULL) {
		del_node_supp(&((*n)->son));
	}
	if ((*n)->brother != NULL) {
		del_node_supp(&((*n)->brother));
	}
	free(*n);
	*n = NULL;
}

int del_node(GTnode **tree, const char* comm)
{
	
	GTnode **n = node_path(tree, comm);
	if (n == NULL || tree == NULL) {
		return 0;
	}
	if ((*n)->son) {
		del_node_supp(&((*n)->son));
	}
	if ((*n)->brother) {
		GTnode *tmpdel = *n;
		*n = (*n)->brother;
		free(tmpdel);
	} else {
		if (n == tree) {
			free(*n);
			*n = NULL;
			return -1;
		}
		free(*n);
		*n = NULL;
	}
	return 1;
}

void print_gtree_supp(GTnode *n, int deep)
{	
	for (int i = 0; i < deep; i++) {
		putchar('\t');
	}
	printf("%d\n", n->data);  
	if (n->son != NULL) {
		print_gtree_supp(n->son, deep + 1);
	}
	if (n->brother != NULL) {
		print_gtree_supp(n->brother, deep);
	}
}

void print_gtree(GTnode *n)
{
	print_gtree_supp(n, 0);
}


void max_i_deep_supp(GTnode *n, int deep, int *max_deep, GTdata *max)
{	
	if (*max <= n->data) {
		*max = n->data;
		*max_deep = deep;
	}
	if (n->son != NULL) {
		max_i_deep_supp(n->son, deep + 1, max_deep, max);
	}
	if (n->brother != NULL) {
		max_i_deep_supp(n->brother, deep, max_deep, max);
	}
}

int max_i_deep(GTnode *n)
{
	int max_deep = 0;
	GTdata max = INT_MIN;
	max_i_deep_supp(n, 0, &max_deep, &max);
	return max_deep;
}
