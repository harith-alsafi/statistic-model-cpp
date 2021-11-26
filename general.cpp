#include <bits/stdc++.h>
using namespace std;

int factorial(int n){
    int fa = n;
    for(int i = n-1; i >= 1; i--){
        fa *= i;
    }
    return fa;
}

int combination(int n, int k){
    return factorial(n)/(factorial(k)*factorial(n-k));
}

string get_pascal(int n){
    string str;
    int coef = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0 || j == i || i == 0){
                coef = 1;
            }
            else{
                coef = combination(i, j);
            }
            str = str + to_string(coef) + " ";
        }
    }
    return str;
}

int main(int argc, char const *argv[])
{
    cout << get_pascal(6);
    // cout << fact(3);
    return 0;
}
