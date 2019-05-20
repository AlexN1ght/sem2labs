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
    //puts("PRINT");
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

void copyTree(BTNode** out, BTNode* tree)
{   
    if(*out != NULL) {
        treeDestroy(out);
    }
    if(tree != NULL) {
        *out = createTree(tree->data);
        copyTree(&(*out)->right, tree->right);
        copyTree(&(*out)->left, tree->left);
    }
}

BTNode* getRightSon(BTNode* tree)
{
    return tree->right;
}

BTNode* getLeftSon(BTNode* tree)
{
    return tree->left;
}

tree_data_type getTreeValue(BTNode* tree)
{
    return tree->data;
}
