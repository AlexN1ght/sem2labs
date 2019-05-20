#ifndef _BITREE_H_
#define _BITREE_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

typedef char* tree_data_type;

typedef struct BTNode{
    tree_data_type data;
    struct BTNode* left;
    struct BTNode* right;
} BTNode;

BTNode* createTree(tree_data_type value);
void copyTree(BTNode** out, BTNode* tree);
void addLeftTree(BTNode* tree, BTNode* in);
void addRightTree(BTNode* tree, BTNode* in);
void printTree(BTNode* tree, int deep);
void treeDestroy(BTNode** tree);
BTNode* getRightSon(BTNode* tree);
BTNode* getLeftSon(BTNode* tree);
tree_data_type getTreeValue(BTNode* tree);

#endif
