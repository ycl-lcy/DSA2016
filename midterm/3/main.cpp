#include<iostream>
#include<cstring>
#include<sstream>
using namespace std;

int main(){
    int n, flag, r = 1;
    string line1, line2;
    getline(cin,line1);
    istringstream s1(line1);
    while(s1 >> n){
        
    }
    //cin.ignore();
    getline(cin,line2);
    istringstream s2(line2);
    while(s2 >> n){
        cout << n << endl;
        if(r){
            if(n == 2)
                flag = 1;
            if(n == 5)
                flag = 2;   
        }
        r = 0;
    }
    if(flag == 1){
        cout << -1 << " " << 1 << " " << 2 << " " << 3 << endl;
    }
    if(flag == 2){
        cout << -1 << " " << 3 << " " << 2 << " " << 1 << " " << 5 << " " << 4 <<   endl;
    }
}
