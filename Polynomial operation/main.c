#include <stdio.h>
#include <stdlib.h>
#include "list_io.h"
#include "list.h"
#include "list_oper.h"
void menu();

int main(){     
    list *A, *B, *C;
    list_init(&A);
    list_init(&B);
    list_init(&C);
    while(1)
    { 
        menu();
        int op;
        scanf("%d",&op);
        getchar();
        //printf("%x %x %x %x\n",A,B,A->nxt,B->nxt);
        if(op == 1){
            puts("standard: 1*a^1+2*b^10+3*a^1*b^1");
            if(list_empty(A))
                A = list_input();
            else if(list_empty(B))
                B = list_input();
        }
        else if(op == 2 || op == 3 || op == 4)
        {
            if(list_empty(A)||list_empty(B))
            { 
                puts("Please input two polynomial!"); 
                continue;
            }
            
            if (op ==2)
                C = list_add(A,B,1);
            else if(op ==3)
                C = list_add(A,B,-1);
            else 
                C = list_mul(A,B);
        }
        else if(op == 5)
        { 
            printf("the first polynomial is: ");
            list_print(A);
            list_init(&A);
            printf("the second polynomial is: ");
            list_print(B);
            list_init(&B);
            printf("the result of the operation is: ");
            list_print(C);
            list_init(&C);
        }
        else if(op == 0) 
            exit(0);
        else 
            puts("input invaild!");
    }

    return 0;
}
void menu(){ 
    puts("1:input the polynomial");
    puts("2:add operation");
    puts("3:sub operation");
    puts("4:mul operation");
    puts("5:print the result");
    puts("0:exit");
    puts("-----------");
}
