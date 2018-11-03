#include<iostream>
#include<stdio.h>
using namespace std;

void dfs(int a[], int i, int n){
   int j;
   if (i == n){
        for(int k = 0; k <= n; k++){
            cout << a[k] << " ";
        }
        cout << endl;
   }
   else{
       for (j = i; j <= n; j++){
          swap(a[i], a[j]);          
          dfs(a, i+1, n);
          swap(a[i], a[j]);
       }
   }
} 

int main()
{
    int n;
    cin >> n;
    int a[100];
    for(int i = 0; i < n; i++){
        a[i] = i+1;
    }
    dfs(a, 0, n-1);
    return 0;
}
