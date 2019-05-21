#include <stdio.h>
#include <stdlib.h>
#include "Dayk.h"
#include "Stack.h"
#include "Bitree.h"
#include "Lin-2-list-barrier.h"

void itoa(int n, char* s);
void reverse(char* s);
void reduceCh(BTNode** polynomial,char ch);
void reduceNum(BTNode** polynomial,int min);
BTNode** findNumInFactorsNE(BTNode** tree, BTNode* eq);

BTNode* pop1addend(BTNode** tree)
{
    puts("pop1addend");
    if(*tree != NULL) {
        BTNode* tmpTreeR;
        BTNode* tmpTreeL;
        char* tmpStr = getTreeValue(*tree);
        if(tmpStr[0] == '+') {
            tmpTreeL = getLeftSon(*tree);
            tmpStr = getTreeValue(tmpTreeL);
            if(tmpStr[0] != '+' && tmpStr[0] != '-') {
                tmpTreeR = getRightSon(*tree);
                free(getTreeValue(*tree));
                free(*tree);
                *tree = tmpTreeR;
                return tmpTreeL;
        	} else {
        		tmpTreeR = getRightSon(*tree);
            	tmpStr = getTreeValue(tmpTreeR);
            	if(tmpStr[0] != '+' && tmpStr[0] != '-') {
                	tmpTreeL = getLeftSon(*tree);
                	free(getTreeValue(*tree));
                	free(*tree);
                	*tree = tmpTreeL;
                	return tmpTreeR;
        		} else {
            		tmpTreeR = pop1addend(&((*tree)->right));
            		if(tmpTreeR) {
            			return tmpTreeR;
            		}
            		tmpTreeL = pop1addend(&((*tree)->left));
            		if(tmpTreeL) {
            			return tmpTreeL;
            		}
        		}
        	}
        } else if(tmpStr[0] == '-') {
            tmpTreeR = getRightSon(*tree);
            tmpStr = getTreeValue(tmpTreeR);
            if(tmpStr[0] != '+' && tmpStr[0] != '-') {
                tmpTreeL = getLeftSon(*tree);
                addRightTree(*tree, NULL);
                addLeftTree(*tree, NULL);
                treeDestroy(tree);
                *tree = tmpTreeL;
                tmpTreeL = createTree("~");
                addRightTree(tmpTreeL, tmpTreeR);
                return tmpTreeL;
        	} else {
        		tmpTreeL = getLeftSon(*tree);
            	tmpStr = getTreeValue(tmpTreeL);
        		if(tmpStr[0] != '+' && tmpStr[0] != '-') {
                	tmpTreeR = getRightSon(*tree);
                	addLeftTree(*tree, NULL);
                	addRightTree(*tree, NULL);
                	treeDestroy(tree);
                	*tree = createTree("~");
                	addRightTree(*tree, tmpTreeR);
                return tmpTreeL;
                } else {
            		tmpTreeR = pop1addend(&((*tree)->right));
            		if(tmpTreeR) {
            			return tmpTreeR;
            		}
            		tmpTreeL = pop1addend(&((*tree)->left));
            		if(tmpTreeL) {
            			return tmpTreeL;
            		}
            	}
        	}  
        } else {
            BTNode* tmpTree = *tree;
            *tree = NULL;
            return tmpTree;
        }
    } else {
        return NULL;
    }
    return NULL;
}

void CutOne(BTNode** tree) {
	puts("CutOne");
    char* tmpStr = getTreeValue(*tree);
    BTNode* tmpT;
    if(tmpStr[0] == '*') {
        tmpStr = getTreeValue(getRightSon(*tree));
        if(strcmp(tmpStr, "1") == 0) {
            tmpT = *tree;
            *tree = getLeftSon(*tree);
            addLeftTree(tmpT, NULL);
            treeDestroy(&tmpT);
        } else {
            CutOne(&((*tree)->right));
        }
        tmpStr = getTreeValue(getLeftSon(*tree));
        if(strcmp(tmpStr, "1") == 0) {
            tmpT = *tree;
            *tree = getRightSon(*tree);
            addRightTree(tmpT, NULL);
            treeDestroy(&tmpT);
        } else {
            CutOne(&((*tree)->left));
        }
    } else if(tmpStr[0] == '~') {
        CutOne(&((*tree)->right));
    }
}

int GetPowCh(BTNode* tree, char ch)
{
	puts("GetPowCh");
    char* tmpStr = getTreeValue(tree);
    if(tmpStr[0] == '*') {
        int out;
        out = GetPowCh(tree->left, ch);
        if(out) {
            return out;
        }
        out = GetPowCh(tree->right, ch);
        if(out) {
            return out;
        }
    } else if(tmpStr[0] == ch) {
        return 1;
    } else if(tmpStr[0] == '~') {
        tmpStr = getTreeValue(getRightSon(tree));
        if(tmpStr[0] == ch)
            return 1;
        int out = GetPowCh(getRightSon(tree), ch);
        if(out) {
            return out;
        }
    } else if(tmpStr[0] == '^') {
        BTNode* tmpTree;
        tmpTree = getLeftSon(tree);
        tmpStr = getTreeValue(getLeftSon(tree));
        if(tmpStr[0] == ch) {
            tmpStr = getTreeValue(getRightSon(tree));
            if(tmpStr[0] == '~')
                return -atoi(getTreeValue(getRightSon(getRightSon(tree))));
            return atoi(getTreeValue(getRightSon(tree)));
        }
        if(tmpStr[0] == ch) {
            tmpStr = getTreeValue(getLeftSon(getRightSon(tree)));
            if(tmpStr[0] == ch) {
                tmpStr = getTreeValue(getRightSon(tree));
                if(tmpStr[0] == '~')
                    return -atoi(getTreeValue(getRightSon(getRightSon(tree))));
                return atoi(getTreeValue(getRightSon(tree)));
            }
        }
    } else  {
        return 0;
    }
    return 0;
}

BTNode* addPolynomials(BTNode** polynomial1, BTNode** polynomial2)
{
    puts("addPolynomials");
    int min = 1;
    int min1 = 1;
    int min2 = 1;
    int num1;
    int num2;
    int k = 1;
    int is_same;
    char* tmpStr;
    BTNode* out = NULL;
    BTNode* pop1;
    BTNode* pop2;
    BTNode** tmpPop1;
    BTNode** tmpPop2;
    Stack* pol11 = stack_create();
    Stack* pol12 = stack_create();
    Stack* pol21 = stack_create();
    Stack* pol22 = stack_create();
    BTNode* tmpT;
    pop1 = pop1addend(polynomial1);
   
    while(pop1) {
        stack_push(pol11, pop1);
        pop1 = pop1addend(polynomial1);
    }
    pop2 = pop1addend(polynomial2);
    while(pop2) {
        stack_push(pol21, pop2);
        pop2 = pop1addend(polynomial2);
    }
    pop1 = stack_pop(pol11);
    while(pop1) {
    	puts("w1");
        if(k == 1)
            pop2 = stack_pop(pol21);
        if(k == -1)
            pop2 = stack_pop(pol22);
        while(pop2) {
        	puts("w2");
            is_same = 1;
            for (int i = 97; i <= 122; i++) {
                if(GetPowCh(pop1, i) != GetPowCh(pop2, i)) {
                    is_same = 0;
                    break;
                }
            }
            if(is_same) {
                tmpStr = getTreeValue(pop1);
                if(tmpStr[0] == '~') {
                    min1 *= -1;
                    tmpT = getRightSon(pop1);
                    addRightTree(pop1, NULL);
                    treeDestroy(&pop1);
                    pop1 = tmpT;
                }

                tmpStr = getTreeValue(pop2);
                if(tmpStr[0] == '~') {
                    min2 *= -1;
                    tmpT = getRightSon(pop2);
                    addRightTree(pop2, NULL);
                    treeDestroy(&pop2);
                    pop2 = tmpT;
                } 
                tmpPop1 = findNumInFactorsNE(&pop1, NULL);
                if(tmpPop1 == NULL) {
                    tmpT = createTree("*");
                    addRightTree(tmpT, pop1);
                    addLeftTree(tmpT, createTree("1"));
                    pop1 = tmpT;
                }
                tmpPop1 = findNumInFactorsNE(&pop1, NULL);
                tmpStr = getTreeValue(*tmpPop1);
                if(tmpStr[0] == '~') {
                    min1 *= -1;
                    tmpT = getRightSon(*tmpPop1);
                    addRightTree(*tmpPop1, NULL);
                    treeDestroy(tmpPop1);
                    *tmpPop1 = tmpT;
                }

                tmpPop2 = findNumInFactorsNE(&pop2, NULL);
                if(tmpPop2 == NULL) {
                    tmpT = createTree("*");
                    addRightTree(tmpT, pop2);
                    addLeftTree(tmpT, createTree("1"));
                    pop2 = tmpT;
                }
                tmpPop2 = findNumInFactorsNE(&pop2, NULL);
                tmpT = *(tmpPop2);
                *tmpPop2 = NULL;
                treeDestroy(&pop2);
                pop2 = tmpT;

                if(tmpStr[0] == '~') {
                    min2 *= -1;
                    tmpT = getRightSon(pop2);
                    addRightTree(pop2, NULL);
                    treeDestroy(&pop2);
                    pop2 = tmpT;
                } 



                num1 = atoi(getTreeValue(*tmpPop1));
                num2 = atoi(getTreeValue(pop2));
                
                char p[17];
                int tmpRes = num1 * min1 + num2 * min2;
                if(tmpRes < 0) {
                    tmpRes = -tmpRes;
                    min = -1;
                }
                itoa(tmpRes, p);
                (*tmpPop1)->data = (char*)realloc((*tmpPop1)->data, sizeof(char) * (strlen(p) + 1));
                strcpy(getTreeValue(*tmpPop1), p);

                if(min == -1) {
                    tmpT = createTree("~");
                    addRightTree(tmpT, pop1);
                    pop1 = tmpT;
                }
                min1 = 1;
                min2 = 1;
                min = 1;
                        
            } else {
                if(k == 1)
                    stack_push(pol22, pop2);
                if(k == -1)
                    stack_push(pol21, pop2);
            }
            if(k == 1)
                pop2 = stack_pop(pol21);
            if(k == -1)
                pop2 = stack_pop(pol22);
        }
        k *= -1;
        if(findNumInFactorsNE(&pop1, NULL)) {
            tmpStr = getTreeValue(*findNumInFactorsNE(&pop1, NULL));
            if(tmpStr[0] == '0') {
                treeDestroy(&pop1);
            } else if(tmpStr[0] == '1') {
                CutOne(&pop1);
                stack_push(pol12, pop1);
            } else {
                stack_push(pol12, pop1);
            }
        } else {
            stack_push(pol12, pop1);
        }
        pop1 = stack_pop(pol11);
    }
    out = stack_pop(pol12);
    if(out == NULL) {
        if(k == 1)
            out = stack_pop(pol21);
        if(k == -1)
            out = stack_pop(pol22);
    }
    pop2 = stack_pop(pol12);
    if(pop2 == NULL) {
        if(k == 1)
            pop2 = stack_pop(pol21);
        if(k == -1)
            pop2 = stack_pop(pol22);
    }
    while(pop2) {
        tmpStr = getTreeValue(pop2);
        if(tmpStr[0] == '~') {
            tmpT = createTree("-");
            addLeftTree(tmpT, out);
            addRightTree(tmpT, getRightSon(pop2));
            addRightTree(pop2, NULL);
            treeDestroy(&pop2);
        } else {
            tmpT = createTree("+");
            addLeftTree(tmpT, out);
            addRightTree(tmpT, pop2);
        }
        out = tmpT;
        pop2 = stack_pop(pol12);
        if(pop2 == NULL) {
            if(k == 1)
                pop2 = stack_pop(pol21);
            if(k == -1)
                pop2 = stack_pop(pol22);
        }
    }
    stack_delete (&pol11);
    stack_delete (&pol12);
    stack_delete (&pol21);
    stack_delete (&pol22);
    return out;
}

void reverse(char* s)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char* s)
{
    int i, sign;

    if ((sign = n) < 0)  
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int extractNode(BTNode** tree, BTNode* eq)
{
	puts("extractNode");
	//puts("--------------------------------");
    //printTree(*tree, 0);
    //puts("--------------------------------");
    if(*tree != NULL) {
        if(*tree == eq) {
            treeDestroy(tree);
            return -1;
        } else {
            if (extractNode(&((*tree)->left), eq) == -1) {
                BTNode* tmpR = (*tree)->right;
                free((*tree)->data);
                free(*tree);
                *tree = tmpR;
            } else if (extractNode(&((*tree)->right), eq) == -1) {
                BTNode* tmpL = (*tree)->left;
                free((*tree)->data);
                free(*tree);
                *tree = tmpL;
            } else if (extractNode(&((*tree)->right), eq) == 0 || extractNode(&((*tree)->left), eq) == 0 ){
                return 0;
            } else {
                return 1;
            }
        }
    } 
    return 1;
}

BTNode** findChPowInFactorsNE(BTNode** tree,BTNode* eq, char ch)
{
	puts("findChPowInFactorsNE");

    char* tmpStr = getTreeValue(*tree);
    if(tmpStr[0] == '*') {
        BTNode** tmpTree;
        tmpTree = findChPowInFactorsNE(&((*tree)->left), eq, ch);
        if(tmpTree) {
            return tmpTree;
        }
        tmpTree =findChPowInFactorsNE(&((*tree)->right), eq, ch);
        if(tmpTree) {
            return tmpTree;
        }
    } else if(tmpStr[0] == ch && *tree != eq) {
        return tree;
    } else if(tmpStr[0] == '~') {
        BTNode* tmpTree;
        tmpTree = getRightSon(*tree);
        tmpStr = getTreeValue(tmpTree);
        if(tmpStr[0] == ch && tmpTree != eq)
            return tree;
    } else if(tmpStr[0] == '^' && *tree != eq) {
        BTNode* tmpTree;
        tmpTree = getLeftSon(*tree);
        tmpStr = getTreeValue(tmpTree);
        if(tmpStr[0] == ch) {
            return tree;
        }
        if(tmpStr[0] == '~') {
            tmpTree = getRightSon(tmpTree);
            tmpStr = getTreeValue(tmpTree);
            if(tmpStr[0] == ch)
                return tree;
        }
    } else  {
        return NULL;
    }
    return NULL;
}

void reduceCh(BTNode** polynomial,char ch)
{
	puts("reduceCh");
    int min = 1;
    char* tmpStr;
    BTNode** ch1T = NULL;
    BTNode** ch2T = NULL;
    ch1T = findChPowInFactorsNE(polynomial, NULL, ch);
    if(ch1T != NULL) {
        ch2T = findChPowInFactorsNE(polynomial, *ch1T, ch);
    }
    while(ch2T) {
        tmpStr = getTreeValue(*ch1T);
        if(tmpStr[0] != '^') {

            BTNode* powTmp = createTree("^");
            BTNode* powNTmp = createTree("1");
            addRightTree(powTmp, powNTmp);
            addLeftTree(powTmp, *ch1T);
            *ch1T = powTmp;
        }
        tmpStr = getTreeValue(*ch2T);
        if(tmpStr[0] != '^'){

            BTNode* powTmp = createTree("^");
            BTNode* powNTmp = createTree("1");
            addRightTree(powTmp, powNTmp);
            addLeftTree(powTmp, *ch2T);
            *ch2T = powTmp;
        }

        tmpStr = getTreeValue(getLeftSon(*ch2T));
        if(tmpStr[0] == '~') {
            min *= -1;
        }

        int num1 = atoi(getTreeValue(getRightSon(*ch1T)));
        int num2 = atoi(getTreeValue(getRightSon(*ch2T)));

        char p[17];
        itoa(num1 + num2, p);
        (getRightSon(*ch1T))->data = (char*)realloc((getRightSon(*ch1T))->data, sizeof(char) * (strlen(p) + 1));
        strcpy(getTreeValue(getRightSon(*ch1T)), p);
        extractNode(polynomial, *ch2T);
        //ch2T = findChPowInFactorsNE(polynomial, *ch1T, ch);
        ch1T = findChPowInFactorsNE(polynomial, NULL, ch);
    	if(ch1T != NULL) {
        	ch2T = findChPowInFactorsNE(polynomial, *ch1T, ch);
    }
    puts("qqweq");
    }
    if(min == -1){
        tmpStr = getTreeValue(getRightSon(*ch2T));
        BTNode* tmp = getRightSon(*ch2T);
        if(tmpStr[0] == '~') {
            tmp = getRightSon(*ch2T);
            addRightTree(*ch2T, getRightSon(getRightSon(*ch2T)));
            addRightTree(tmp, NULL);
            treeDestroy(&tmp);
        } else {
            tmp = createTree("~");
            addRightTree(tmp, getRightSon(*ch2T));
            addLeftTree(*ch2T, tmp);
        }
    }
    puts("qqq");

}

BTNode** findNumInFactorsNE(BTNode** tree, BTNode* eq)
{
	puts("findNumInFactorsNE");
    char* tmpStr = getTreeValue(*tree);
    if(tmpStr[0] == '*') {
        BTNode** tmpTree;
        tmpTree = findNumInFactorsNE(&((*tree)->left), eq);
        if(tmpTree) {
            return tmpTree;
        }
        tmpTree =findNumInFactorsNE(&((*tree)->right), eq);
        if(tmpTree) {
            return tmpTree;
        }
    } else if(is_num(tmpStr[0]) && *tree != eq) {
        return tree;
    } else if(tmpStr[0] == '~') {
        BTNode* tmpTree;
        tmpTree = getRightSon(*tree);
        tmpStr = getTreeValue(tmpTree);
        
        puts("minus");
        
        if(is_num(tmpStr[0]) && *tree != eq) {
        	puts("minBazzz");
            return tree;
        } else if(is_num(tmpStr[0])) {
        	return NULL;
        }
        puts("minBack");
        BTNode** tmpTree2;
        tmpTree2 = findNumInFactorsNE(&((*tree)->right), eq);
        if(tmpTree2) {
            return tmpTree2;
        }
    } else {
    	puts("k");
        return NULL;
    }
    return NULL;

}

void reduceNum(BTNode** polynomial,int min)
{
	puts("reduceNum");
	puts("--------------------------------");
    	printTree(*polynomial, 0);
   		puts("--------------------------------");
	
    char* tmpStr;
    int num1 = 0;
    int num2 = 0;
    BTNode** num1T = NULL;
    BTNode** num2T = NULL;
    BTNode* num1add;
    BTNode* num2add;
    num1T = findNumInFactorsNE(polynomial, NULL);

    if(num1T != NULL) {
    	 
    	puts("--------------------------------");
    	printTree(*num1T, 0);
    	puts("--------------------------------");
        num2T = findNumInFactorsNE(polynomial, *num1T);
    }
    puts("dd");
    while(num2T) {
    	puts("zez");
        tmpStr = getTreeValue(*num1T);
        puts("zez");
        if(tmpStr[0] == '~') {
            min *= -1;
            num1add = getRightSon(*num1T);
            puts("--------------------------------");
    		printTree(*num1T, 0);
    		puts("--------------------------------");
        } else {
            num1add = *num1T;        
        }
        
        puts("------------------1111q-------------");
    		printTree(*num1T, 0);
    	puts("--------------------------------");
		puts("zez");
        tmpStr = getTreeValue(*num2T);
        if(tmpStr[0] == '~') {
            min *= -1;
            num2add = getRightSon(*num2T);
        } else {
            num2add = *num2T;
        }
        puts("---------------2222--------------");
    	printTree(*num2T, 0);
    	puts("--------------------------------");
		puts("zez");
        num1 = atoi(getTreeValue(num1add));
        num2 = atoi(getTreeValue(num2add));
        printf("%d %d\n", num1, num2);
        
        char p[17];
        itoa(num1*num2, p);
        treeDestroy(num1T);
        if(min == -1) {
        	*num1T = createTree("~");
        	addRightTree(*num1T, createTree(p));
        	
        } else {
        	*num1T = createTree(p);
        }
        
        //(*num1T)->data = (char*)realloc((*num1T)->data, sizeof(char) * (strlen(p) + 1));
        //strcpy(getTreeValue(*num1T), p);
        puts("--------------------------------");
    	printTree(*polynomial, 0);
    	puts("--------------------------------");
        extractNode(polynomial, *num2T);
        puts("--------------------------------");
    	printTree(*polynomial, 0);
    	puts("--------------------------------");

        num1T = findNumInFactorsNE(polynomial, NULL);
    	if(num1T != NULL) {
        	num2T = findNumInFactorsNE(polynomial, *num1T);
    	}
    	puts("--------------------------------");
    	printTree(*polynomial, 0);
   		puts("--------------------------------");
    	puts("kmk");
    	min = 1;
    }
    puts("sgag2");
}

void multiplyBranchToAddend(BTNode** polynomial, BTNode* addend)
{   
    puts("multiplyBranchToAddend");
    int min = 1;
    char* tmpStr;
    BTNode* tmpT;
    BTNode* out;
    Stack* pol1 = stack_create();
    Stack* pol2 = stack_create();
    puts("q");
    BTNode* pop1 = pop1addend(polynomial);
    puts("q");
    while(pop1) {
    	puts("kkkkkkk");
        puts("w");
        stack_push(pol1, pop1);
        pop1 = pop1addend(polynomial);
    }
    puts("q");
    puts("q");
    pop1 = stack_pop(pol1);
    puts("q");
    tmpStr = getTreeValue(pop1);
    if(tmpStr[0] == '~') {
        min *= -1;
        tmpT = getRightSon(pop1);
        addRightTree(pop1, NULL);
        treeDestroy(&pop1);
        pop1 = tmpT;
    }
    while(pop1) {
        puts("W");
        out = createTree("*");
        tmpStr = getTreeValue(addend);
        BTNode* numAd = NULL;
        if(tmpStr[0] == '~') {
            min *= -1;
            copyTree(&numAd, getRightSon(addend));
            puts("E");
        } else {
            copyTree(&numAd, addend);
        }
        puts("У");
        addRightTree(out, numAd);
        puts("У");
        addLeftTree(out, pop1);
        puts("У");
        pop1 = out;
        puts("shag1");
        reduceNum(&pop1, 1);
        puts("kj,");
        reduceCh(&pop1, 'x');
        puts("jsusssss");
        if(min == -1) {
            out = createTree("~");
            addRightTree(out, pop1);
            pop1 = out;
        }
        min = 1;
        puts("jsus");
        stack_push(pol2, pop1);
        pop1 = stack_pop(pol1);
        if(pop1) {
        	tmpStr = getTreeValue(pop1);
        }
        if(tmpStr[0] == '~' && pop1) {
        	puts("jrrr");
            min *= -1;
            puts("jsus");
            puts("--------------------------------");
    		printTree(pop1, 0);
    		puts("--------------------------------");
            tmpT = getRightSon(pop1);
            puts("jsus");
            addRightTree(pop1, NULL);
            treeDestroy(&pop1);
            puts("jsus");
            pop1 = tmpT;
        }
        puts("qwer");
    }
    puts("zzzzzzzzzzzzzzzz");
    *polynomial = stack_pop(pol2);
    out = stack_pop(pol2);
    while(out) {
    	puts("zqqfgfghcngcbgczzzzz");
        tmpStr = getTreeValue(out);
        if(tmpStr[0] == '~') {
            tmpT = createTree("-");
            addLeftTree(tmpT, *polynomial);
            addRightTree(tmpT, getRightSon(out));
            addRightTree(out, NULL);
            treeDestroy(&out);
        } else {
            tmpT = createTree("+");
            addLeftTree(tmpT, *polynomial);
            addRightTree(tmpT, out);
        }
        *polynomial = tmpT;
        out = stack_pop(pol2);
    }
    puts("zzzzzzqqqqqzzzzzzzzz");
    stack_delete (&pol1);
    stack_delete (&pol2);
}



BTNode* multiplyPolynomialToAddend(BTNode* polynomial, BTNode* addend)
{	
	puts("multiplyPolynomialToAddend");
    BTNode* out = NULL;
    copyTree(&out, polynomial);
    multiplyBranchToAddend(&out, addend);
    return out;
}

BTNode* multiplyPolynomials(BTNode* polynomial1, BTNode* polynomial2)
{
	puts("multiplyPolynomials");
    puts("A");
    BTNode* addendsTree = NULL;
    BTNode** tmpT =(BTNode**)malloc(sizeof(BTNode**));
    BTNode** out = (BTNode**)malloc(sizeof(BTNode**));
    copyTree(&addendsTree, polynomial2);
    BTNode* addend  = pop1addend(&addendsTree);
    puts("--------------------------------");
    printTree(addend, 0);
    puts("--------------------------------");
    *out = multiplyPolynomialToAddend(polynomial1, addend);
    puts("--------------out------------------");
    printTree(*out, 0);
    puts("--------------------------------");
    
    addend  = pop1addend(&addendsTree);
    puts("A");
    while(addend != NULL) {
        puts("B");
        *tmpT = multiplyPolynomialToAddend(polynomial1, addend);
        puts("----------------out----------------");
    	printTree(*out, 0);
    	puts("--------------------------------");
    	puts("----------------tmpT----------------");
    	printTree(*tmpT, 0);
    	puts("--------------------------------");
        *out =  addPolynomials(out, tmpT);
        puts("----------------out----------------");
    	printTree(*out, 0);
    	puts("--------------------------------");
        addend  = pop1addend(&addendsTree);
    }
    return *out;
}

BTNode* RPNtoTree(List* list)
{
    if (list != NULL) {
        Stack *stack = stack_create();
        BTNode* node;
        char* tmp;
        while(list_peak(list, 1) != NULL) {
            tmp = list_pop_back(list);
            if(is_op(tmp[0])) {
                node = createTree(tmp);
                addRightTree(node,stack_pop(stack));
                addLeftTree(node,stack_pop(stack));
                stack_push(stack, node);
            } else if(tmp[0] == '~') {
                if (list_peak(list, 1) != NULL) {
                    node = createTree(tmp);
                    addRightTree(node,createTree(list_pop_back(list)));
                    stack_push(stack, node);
                } else {
                    treeDestroy(&node);
                    while(!stack_is_empty(stack)){
                        node = stack_pop(stack);
                        treeDestroy(&node);
                    }
                    free(tmp);
                    stack_delete(&stack);
                    return NULL;
                }
            } else {
                stack_push(stack, createTree(tmp));
            }
            free(tmp);
        }
        node = stack_pop(stack);
        stack_delete(&stack);
        return node;
    } else {
        return NULL;
    }
}



int main (void)
{

    char* e1 = "x^2+4*x-18";
    char* e2 = "x^4-13*x^5+2*x+11";
    List* e1L = StrToRPN(e1);
    List* e2L = StrToRPN(e2);
    list_print(e1L);
    puts("--------------------------------");
    list_print(e2L);
    puts("--------------------------------");
    BTNode* e1T = RPNtoTree(e1L);
    BTNode* e2T = RPNtoTree(e2L);
    printTree(e1T, 0);
    puts("--------------------------------");
    printTree(e2T, 0);
    puts("--------------------------------");
    printTree(multiplyPolynomials(e1T, e2T), 0);
    puts("--------------------------------");
    list_destroy(&e1L);
    treeDestroy(&e1T);
    list_destroy(&e2L);
    treeDestroy(&e2T);
    return 0;
}
   