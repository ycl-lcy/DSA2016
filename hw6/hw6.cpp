#include<iostream>
#include<vector>
#include<cmath>
#include<cfloat>
using namespace std;

int main(){
    int n, m, x, y;
    double min_dis = DBL_MAX;
    double **dp;
    vector<int> ans;
    cin >> n;
    dp = new double*[n];
    double *p = new double[n];
    for(int i = 0; i < n; i++){
        cin >> p[i];
    }
    cin >> m;
    double *q = new double[m];
    for(int i = 0; i < m; i++){
        cin >> q[i];
    }
    for(int i = 0; i < n; i++){
        dp[i] = new double[m];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i < j){
                continue;
            }
            else if(i == 0){
                dp[i][j] = abs(p[i] - q[j]);
            }
            else if(j == 0){
                dp[i][j] = abs(p[i] - q[j]) + dp[i-1][j];

            }
            else if(i == j){
                dp[i][j] = abs(p[i] - q[j]) + dp[i-1][j-1];
            }
            else{
                dp[i][j] = abs(p[i] - q[j]) + min(dp[i-1][j], dp[i-1][j-1]);
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(dp[n-1][i] < min_dis){
            min_dis = dp[n-1][i];
            y = i;
        }
    }
    x = n-1;
    ans.push_back(x);
    while(x >= 0){
        if(x == y){
            ans.push_back(x);
            x--;
            y--;
        }
        else if(y == 0){
            x--;
        }
        else{
            if(dp[x-1][y] >= dp[x-1][y-1]){
                ans.push_back(x);
                x--;
                y--;
            }
            else{
                x--;
            }
        }
    }
    cout << min_dis << endl;
    for(vector<int>::iterator it = ans.end()-1; it != ans.begin(); it--){
        cout << *it;
        if(it-1 != ans.begin()){
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
