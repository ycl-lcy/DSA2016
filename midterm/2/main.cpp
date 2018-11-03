#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

vector<int> tree;
void preorder(int n){
    if(n > tree.size()-1 || tree[n] == -1)
        return;
    cout << tree[n] << " ";
    preorder(2*n);
    preorder(2*n+1);
}

void inorder(int n){
    if(n > tree.size()-1 || tree[n] == -1)
        return;
    inorder(2*n);
    cout << tree[n] << " ";
    inorder(2*n+1);
}

void postorder(int n){
    if(n > tree.size()-1 || tree[n] == -1)
        return;
    postorder(2*n);
    postorder(2*n+1);
    cout << tree[n] << " ";
}
int main(){
    string line;
    int n;
    getline(cin,line);
    istringstream ss(line);
    while(ss >> n){
        tree.push_back(n);
    }
    preorder(1);
    cout << endl;
    inorder(1);
    cout << endl;
    postorder(1);
    cout << endl;
    /*for(int i = 0; i < tree.size(); i++){
        cout << tree[i] << endl;
    }*/
    return 0;
}
