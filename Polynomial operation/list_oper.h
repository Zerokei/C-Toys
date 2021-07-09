#include "list.h"
#include "list_io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
List * copy_list_to_new_node(List *B){ 
    List *A;
    newlist(&A);
    A -> ha = B -> ha;
    A -> coe = B -> coe;
    A -> Head = B -> Head;
    return A;
}
ele * copy_ele_to_new_node(ele *B){ 
    ele *A;
    newele(&A);
    A -> c = B -> c;
    A -> x = B -> x;
    return A;
}
void delete_repeated_node_ele(ele *head){ 
    static ele * Sum[256];
    memset(Sum,0,sizeof Sum);
    ele *p = head;
    for(;p -> nxt != NULL;){ 
        ele *q = p -> nxt;
        if (Sum[(int)(q -> c)]){ 
            p -> nxt = q -> nxt;
            Sum[(int)(q -> c)] -> x += q -> x;
        }
        else { 
            Sum[(int)(q -> c)] = q;
            p = q;
        }
    }
    /*
    ele *tail = p;
    p = head;
    int add_f = 0;
    for(;p -> nxt != NULL;){ 
        ele *q = p -> nxt;
        if(q -> c != '#' && q -> x == 0){ 
            if (!Sum['#']){ 
                newele(&Sum['#']);
                Sum['#'] -> c = '#';
                Sum['#'] -> x = 0;
                add_f = 1;
            }
            Sum['#'] -> x += q -> x;
            p -> nxt = q -> nxt;
        }
        else p = q;
    }
    if(add_f == 0){ 
        tail -> nxt = Sum['#'];    
    }*/
}
void calc_ha_of_elements(List *A){ 
    ele *p = A -> Head;
    int ha = 0;
    for(p = p -> nxt; p != NULL; p = p -> nxt){ 
        if (p -> c == '#') continue; // don't calc the special number
        ha = (ha + Pow(p -> c, p -> x))%P;
        //printf("%c %d ",p -> c, p -> x);
    }
    //printf("%d\n",ha);
    A -> ha = ha;
}
void joint_the_list(List *P, ele **Tail){ 
    ele *q, *tail = *Tail;
    for(q = (P -> Head) -> nxt; q != NULL; q = q -> nxt){ 
        if (q -> c == '#') continue;
        ele *p = copy_ele_to_new_node(q);
        tail -> nxt = p;
        tail = p;
    }
    *Tail = tail;
}
List * mul_node(List *A, List *B){ 
    List *Node;
    newlist(&Node);
    Node -> coe = A -> coe * B -> coe;
    
    ele *head;
    newele(&head);
    ele *tail = head;

    joint_the_list(A, &tail);
    joint_the_list(B, &tail);
    
    if (tail == head){//both the A and B are numbers 
        ele *p;
        newele(&p);
        p -> c = '#';
        tail -> nxt = p;
        //puts("666");
    }
    
    delete_repeated_node_ele(head);
    Node -> Head = head;
    calc_ha_of_elements(Node);
    return Node;
}
void delete_repeated_node_list(List *head){ 
    static List * Sum[100005];
    memset(Sum,0,sizeof Sum);
    List *p = head;
    for(;p -> nxt != NULL;){ 
        List *q = p -> nxt;
        //printf("%d\n",q -> ha);
        if(Sum[q -> ha]){
            p -> nxt = q -> nxt;
            Sum[q -> ha] -> coe += q -> coe;
            free(q);
        }
        else { 
            Sum[q -> ha] = q;
            p = q;
        }
    }
}

List * list_add(List *A, List *B, int op){
    List *p1 = A -> nxt, *p2 = B -> nxt;
    List *head;
    newlist(&head);
    List *tail = head;
    for (; p1 != NULL; p1 = p1 -> nxt){ 
        List *q = copy_list_to_new_node(p1);
        tail -> nxt = q;
        tail = q;
    }
    for (; p2 != NULL; p2 = p2 -> nxt){ 
        List *q = copy_list_to_new_node(p2);
        q -> coe *= op;
        tail -> nxt = q;
        tail = q;
    }
    delete_repeated_node_list(head);
    return head;
}
List * list_mul(List *A, List *B){ 
    List *head;
    newlist(&head);
    List *tail = head;
    List *p1, *p2;
    for (p1 = A -> nxt; p1 != NULL; p1 = p1 -> nxt)
    { 
        for(p2 = B -> nxt; p2 != NULL; p2 = p2 -> nxt)
        {
            List *q = mul_node(p1, p2);
            tail -> nxt = q;
            tail = q;
        } 
    }
    delete_repeated_node_list(head);
    return head;
}
