#include<stdio.h>
#include"list.h"
#ifndef _LIST_IO_H_
#define _LIST_IO_H_
const int P = 99991;
int Pow(int x,int n){// calc x^n 
    int S = 0, a = x;
    while(n){ 
        a = (1ll * a * a) % P;
        if(n & 1) S = (S + a) % P;
        n >>= 1;
    }
    return S;
}
List* push(char C[],int top,List *p,int op){ 
    // example 2*a^2*b^2
    List *pnd;
    newlist(&pnd);
    int i;
    int coe = 0, ha = 0;
    for(i = 0; i < top; ++i){ 
        if(C[i] == '*')
            break;
        coe = coe * 10 + C[i] - '0';
    }

    coe *= op;    
    pnd -> coe = coe;
    // make all the element be a list, and add to the "List p";
    ele *pnod;
    newele(&pnod);
    ele *head = pnod, *tail = pnod;
    pnd -> Head = head;
    
    if (i == top){ // only have number
        newele(&pnod);
        pnod -> c = '#'; // # represent the number
        tail -> nxt = pnod;
        pnd -> ha = 0; // special value : zero, only to represent number
        p -> nxt = pnd;
        return pnd;
    }

    ++i;//ignore the *
    while(i < top)
    { 
        newele(&pnod);
        pnod -> c = C[i]; 
        
        i += 2;//ignore the char and ^
        
        int num = 0;
        for(; i < top; ++i)
        {
            if(C[i] == '*')
                break;
            num = num * 10 + C[i] - '0';
        }
        pnod -> x = num;
        tail -> nxt = pnod;
        tail = pnod;
        ha = (ha + Pow(pnod -> c, num))%P;
        ++i;//ignore the *
    }
    pnd -> ha = ha;
    p -> nxt = pnd;
    return pnd;
}
List* list_input(){ 
    // 2*a^2*b^2
    char Sk[100];
    int top = 0, op = 1;

    List *pL;
    newlist(&pL);
    List *head = pL, *tail = pL;
    list_init(&pL);

    char c;
    while(c = getchar()){ 
        if (c == '\n')
        { 
            tail = push(Sk,top,tail,op);
            top = 0;
            break;
        }
        else if (c == '+')
        { 
            tail = push(Sk,top,tail,op);
            top = 0;
            op = 1;
        }
        else if (c == '-')
        {
            if (top)
                tail = push(Sk,top,tail,op);
            top = 0;
            op = -1;   
        }
        else 
            Sk[top++] = c;
    }
    return head;
}
void list_print(List *head){
    if(head == NULL || head -> nxt == NULL)
        return;
    List *p = head;
    int fi = 0;
    for(p = p -> nxt; p != NULL; p = p -> nxt)
    { 
        if (p -> coe == 0)
            continue;
        if (fi == 0)
            fi = 1;
        else if(p -> coe >= 0)
            printf("+");
        printf("%d",p -> coe);
        
        ele *ep = p -> Head;
        if( ep == NULL ||              // empty
            ep -> nxt == NULL ||       // empty
            (ep -> nxt) -> c == '#' // the number
          ) continue;
        
        putchar ('*');

        int fi1 = 0;
        for(ep = ep -> nxt; ep != NULL; ep = ep -> nxt){
            if(fi1 == 0)
                fi1 = 1;
            else 
                printf("*");
            printf("%c^%d",ep -> c,ep -> x);
        }  
    }
    if(fi == 0){//have not printed anything yet 
        printf("0");
    }
    puts("");
}
#endif
