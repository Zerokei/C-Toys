#include<stdio.h>
#include"type.h"
extern int map[12][12];
void input(){
    freopen("input.txt","r",stdin);
    int i, j;
    /*
     * mp[i][j]=1 obstacles
     * mp[i][j]=0 clearing
     */
    printf("Please input the map (10 * 10)\n");
    printf("the 1 is obstacle and the 0 is area\n");
    printf("And the piece will start at (1,1)\n");
    printf(">>>>>input area>>>>\n");
    for(i = 0; i < 10; i++){ 
        for(j = 0; j < 10; j++){ 
            scanf("%d", &map[i][j]);
        }
    }
    return;
}
void output(struct answer *Ans){
    int i;
    puts("the answer is >>>>>>>");
    printf("the number of step is %d\n", Ans -> n);
    for(i = 0; i < Ans -> n; i++){ 
        printf("(%d,%d)", Ans->X[i], Ans->Y[i]);
        if(i != Ans -> n -1){
            printf("->");
        }
        puts("");
    }
    puts(">>>>>>>>>>>>>>>>>>>>>");
}
