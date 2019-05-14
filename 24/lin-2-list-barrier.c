#include <stdio.h>
#include "lin-2-list-barrier.h"

List* list_create(void)
{
  List *lst;
  Node *nod;
  lst = (List*)malloc(sizeof(List));
  nod = (Node*)malloc(sizeof(Node));
  lst->size = 0;
  lst->barr = nod;
  nod->next = lst->barr;
  nod->prev = lst->barr;
  return(lst);
}

void list_push_front(List *lst, data_type value)
{
    Node *Next;
    Next = (Node*)malloc(sizeof(Node));
    Next->data = (char*)malloc(sizeof(char) * 
    Next->data = value;
    lst->size++;
    Next->prev = (lst->barr)->prev;
    (lst->barr)->prev = Next;
    Next->next = lst->barr;
    (Next->prev)->next = Next;
}

void list_push_back(List *lst, data_type value)
{
    Node *Next;
    Next = (Node*)malloc(sizeof(Node));
    Next->data = value;
    lst->size++;
    Next->next = (lst->barr)->next;
    (lst->barr)->next = Next;
    Next->prev = lst->barr;
    (Next->next)->prev = Next;
}

int list_insert(List *lst, int i, data_type value)
{
	if (i == 0 || abs(i) > lst->size + 1) {
		return 1;
	} else {
        lst->size++;
    }
	Node *Inter;
	Node *Tmp = lst->barr;
	Inter = (Node*)malloc(sizeof(Node));
	if (i > 0) {
        for (int k = 0; k < i; k++) {
		    Tmp = Tmp->next;
        }
	} else {
        for (int k = 0; k < -i; k++) {
		    Tmp = Tmp->prev;
	    }
        Tmp = Tmp->next;
    }
	Inter->data = value;
	Inter->next = Tmp;
	Inter->prev = Tmp->prev;
	(Tmp->prev)->next = Inter;
	Tmp->prev = Inter;
	return 0;
}

data_type list_pop_front(List *lst)
{
    if (lst->size == 0) {
        puts("Error: stack is empty");
        exit(100);
    }
    data_type tmp = list_peak(lst, -1);
    list_remove(lst, -1);
    return tmp;
}

data_type list_pop_back(List *lst)
{
    if (lst->size == 0) {
        puts("Error: stack is empty");
        exit(100);
    }
    data_type tmp = list_peak(lst, 1);
    list_remove(lst, 1);
    return tmp;
}

data_type list_get_out(List *lst, int i)
{
    if (lst->size == 0) {
        puts("Error: stack is empty");
        exit(100);
    }
    data_type tmp = list_peak(lst, i);
    list_remove(lst, i);
    return tmp;
}

int list_remove(List *lst, int i)
{
	if (i == 0 || abs(i) > lst->size) {
		return 1;
	} else {
        lst->size--;
    }
	Node *Tmp = lst->barr;
    if (i > 0) {
        for (int k = 0; k < i; k++) {
		    Tmp = Tmp->next;
        }
	} else {
        for (int k = 0; k < -i; k++) {
		    Tmp = Tmp->prev;
	    }
    }
	(Tmp->prev)->next = Tmp->next;
	(Tmp->next)->prev = Tmp->prev;
	free(Tmp);
	return 0;
}

int list_remove_k(List *lst, int i)
{
	if (i == 0 || abs(i) > lst->size) {
		return 1;
	}
    if (i > 0) {
        for (int k = i; k <= lst->size; k = k + i) {
            list_remove(lst, k);
            k -= 1;
        }
	} else {
        for (int k = -i; k <= lst->size; k = k - i) {
            list_remove(lst, -k);
            k -= 1;
        }
    }
    return 0;
}

data_type list_peak(List *lst, int i) 
{
    if (lst->size == 0) {
        puts("Error: stack is empty");
        exit(100);
    }
	Node *Tmp = lst->barr;
    if (i > 0) {
        for (int k = 0; k < i; k++) {
		    Tmp = Tmp->next;
        }
	} else {
        for (int k = 0; k < -i; k++) {
		    Tmp = Tmp->prev;
	    }
    }
	return Tmp->data;
}

void list_print(List *lst)
{
    Node *tmp = (lst->barr)->next;
    for (int i = 0; i < lst->size; i++) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    putchar('\n');
}


void list_destroy(List **lst) 
{
    Node *tmp = ((*lst)->barr)->next;
    Node *next = NULL;
    while (tmp != (*lst)->barr) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free((*lst)->barr);
    free(*lst);
    (*lst) = NULL;
}

int list_size(List *lst)
{
    return lst->size;
}
