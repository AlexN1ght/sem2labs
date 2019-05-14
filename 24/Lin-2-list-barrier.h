#ifndef _LIN_2_LIST_BARRIER_H_
#define _LIN_2_LIST_BARRIER_H_

#include <stdlib.h>

typedef char* data_type;

typedef struct Node{
    data_type data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    int size;
    Node *barr;
} List;

List* list_create(void);
void list_destroy(List **lst);
int list_remove(List *lst, int i);
int list_remove_k(List *lst, int i);
int list_insert(List *lst, int i, data_type value);
void list_push_front(List *lst, data_type value);
void list_push_back(List *lst, data_type value);
data_type list_get_out(List *lst, int i);
data_type list_pop_front(List *lst);
data_type list_pop_back(List *lst);
data_type list_peak(List *lst, int i);
void list_print(List *lst);
int list_size(List *lst);

#endif
