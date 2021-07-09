#include<stdlib.h>
#ifndef LIST_H
#define LIST_H
typedef struct element{
    int x;
    char c;
    struct element * nxt;
}ele;
typedef struct Mylist{ 
    ele * Head;//as the head of elements
    int coe;
    int ha;
    struct Mylist * nxt;
}List,list;
void list_init(list **p){ 
    *p = (list *)malloc(sizeof (list));
    (*p) -> nxt = NULL;
    (*p) -> Head = NULL;
}
void clear_list(list *p){ 
    free(p);
    p = NULL;
}
void newele(ele ** p){
    *p = (ele *)malloc(sizeof (ele));
    (*p) -> nxt = NULL;
}
void newlist(List **p){ 
    *p = (List *)malloc(sizeof (List));
    (*p) -> nxt = NULL;
    (*p) -> Head = NULL;
}
int list_empty(list *p){ 
    return p == NULL || p -> nxt == NULL;
}
#endif
