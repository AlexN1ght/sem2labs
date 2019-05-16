#include "Bitree.h"

BTNode* createTree(tree_data_type value)
{
    BTNode* out = (BTNode*)malloc(sizeof(BTNode));
    out->data = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(out->data, value);
    out->left = NULL;
    out->right = NULL;
    return out;
}

void addLeftTree(BTNode* tree, BTNode* in)
{
    tree->left = in;
}

void addRightTree(BTNode* tree, BTNode* in)
{
    tree->right = in;
}

void printTree(BTNode* tree, int deep)
{
    if (tree != NULL) {
        for(int i = 0; i < deep; i ++) putchar('\t');
        printf("%s\n", tree->data);
        printTree(tree->right, deep + 1);
        printTree(tree->left, deep + 1);
    }
}

void treeDestroy(BTNode** tree)
{
    if (*tree != NULL) {
        free((*tree)->data);
        treeDestroy(&((*tree)->right));
        treeDestroy(&((*tree)->left));
        free(*tree);
        *tree = NULL;
    }
}
