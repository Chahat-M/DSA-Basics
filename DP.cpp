// DP - Modifiying overlapping recursive solution 
//      so that value of once calculated recursive part remains stored and can be directly used
// 2ways - memoization (Top Down)
//       - tablulation (Bottom Up)
#include <iostream>
#include <string.h>
using namespace std;

// Memoization
int memo[10000];

int fibM(int n){
    if(memo[n] == -1){
        int res;
        if(n == 0 || n == 1)
            return n;
        else
            res = fib(n-1) + fib(n-2);
        memo[n] = res;
    }
    return memo[n];
}

// Tabulation
int fibT(int n){
    int f[n+1];
    f[0] = 0;
    f[1] = 1;
    for(int i = 2; i <= n; i++){
        f[i] = f[i-1] + f[i-2];
    }
    return f[n];
}

int main(){
    int n = 7;
    memset(memo, -1, sizeof(memo));
    cout << fib(3);
    return 0;
}

