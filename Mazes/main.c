#include "IO.h"
#include "solve.h"
#include "type.h"
int main(){
    input();
    struct answer Ans;
    Ans = solve();
    output(&Ans);
    return 0;
}
