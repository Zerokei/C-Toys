#include"type.h"
#include<stdio.h>
extern int map[12][12];
int mark[12][12];
void Add(struct pro *cur, int *index, struct pro *Stack){
    mark[cur -> x][cur -> y] = 1;
    (*index)++;
    Stack[*index]= *cur;
} 
void Delete(struct pro *cur, int *index){
    (*index)--;
    mark[cur -> x][cur -> y] = 0;
}
struct pro new_pos(struct pro *cur){ 
    int nx[] = {0, 1, 0, -1};
    int ny[] = {1, 0, -1, 0};
    static int x;
    x = (cur -> x) + nx[cur -> dir];
    static int y;
    y = (cur -> y) + ny[cur -> dir];
    struct pro nxt;
    nxt.x = x;
    nxt.y = y;
    nxt.dir = 0;
    return nxt;
}

int judge(struct pro *cur){ 
    struct pro nxt = new_pos(cur);
    static int x;
    x = nxt.x;
    static int y;
    y = nxt.y;
    if(x < 0 || x > 9 || y < 0 || y > 9)
        return 0;
    if(map[x][y] == 0 && mark[x][y] == 0)
        return 1;
    else 
        return 0;
}

int judge_end(struct pro *cur){ 
    if (cur -> x == 8 && cur -> y == 8)
        return 1;
    else 
        return 0;
}

struct pro next_pos(struct pro *cur){
    struct pro nxt = *cur; 
    nxt.dir = cur -> dir + 1;
    if(judge(&nxt) == 0 || nxt.dir > 3)
        nxt.dir = -1;
    return nxt;
    // if nxt.dir == -1 where is no way to go
}

struct answer solve(){
    struct pro cur = (struct pro){1, 1, 0};
    int index = -1;
    struct pro Stack[105];
    Add(&cur, &index, Stack);

    do{ 
        cur = Stack[index];

        //printf("%d %d %d\n",cur.x, cur.y, cur.dir);

        if (judge(&cur)){// true: able to go 
            struct pro nxt = new_pos(&cur);
            Add(&nxt, &index, Stack);

            if (judge_end(&nxt))
                break;
        }
        else { 
            struct pro nxt1 = next_pos(&cur);
            if (nxt1.dir == -1){ 
                //have tried all the directions and there is no way to go
                do{
                    Delete(&cur, &index);
                    cur = Stack[index];
                    cur.dir++;
                }while(cur.dir == 4);
                Stack[index] = cur;
            }
            else { 
                Delete(&cur, &index);
                Add(&nxt1, &index, Stack);
            }
        }
    }while(index != -1);
    
    // put Stack into answers
    int i;
    struct answer route;
    for(i = 0; i <= index; i++){ 
        route.X[i] = Stack[i].x;
        route.Y[i] = Stack[i].y;
    }
    route.n = index + 1;
    printf("route.n = %d\n", route.n);
    return route;
}
