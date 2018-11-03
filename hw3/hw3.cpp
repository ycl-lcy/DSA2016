#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

int **nono;
int **preNono;
int **preNono_row;
int **preNono_column;
int **ans;
int rowNumber, columnNumber;
vector<int> *rowRule;
vector<int> *columnRule;
int line[30] = {0};
int nonoLine[50] = {0};
int ans_found = 0;

void dfs_solve(int, int);
void print_nono();
void print_preNono();
int check_complete(int, int);
void preTreat();
void preTreat_dfs(int, int, int);
void print_line();
void print_nonoLine();
int black_check_row(int, int);
int black_check_column(int, int);
int white_check_row(int, int);
int white_check_column(int, int);

void dfs_solve(int m, int n){
    if(ans_found) 
        return;
    if(n == columnNumber){
        m += 1;
        n = 0;
    }       
    if(m == rowNumber){
        for(int i = 0; i < rowNumber; i++){
            if(!check_complete(1,i)) return;
        }
        for(int i = 0; i < columnNumber; i++){
            if(!check_complete(0,i)) return;
        }
        print_nono();
        ans_found++;
        return;
    }
    if(preNono[m][n] == 1){
        if(black_check_row(m, n) && black_check_column(m, n)){           
            nono[m][n] = 1;
            dfs_solve(m, n+1);
            nono[m][n] = 0;
        }
        else
            return;
    }
    if(preNono[m][n] == -1){
        if(white_check_row(m, n) && white_check_column(m, n)){
            nono[m][n] = -1;
            dfs_solve(m, n+1);
            nono[m][n] = 0;
        }
        else
            return;
    }
    if(preNono[m][n] == 0){
        if(black_check_row(m, n) && black_check_column(m, n)){           
            nono[m][n] = 1;
            dfs_solve(m, n+1);
            nono[m][n] = 0;       
        }
        if(white_check_row(m, n) && white_check_column(m, n)){
            nono[m][n] = -1;
            dfs_solve(m, n+1);
            nono[m][n] = 0;           
        }
    }
}

int black_check_row(int m, int n){
    int length = 0, block = 0;
    for(int i = 0; i < n; i++){
        if(nono[m][i] == 1)
            length++;
        else{
            if(nono[m][i] == -1 && length != 0){
                length = 0;
                block++;
            }
        }
    } 
    if(block == rowRule[m].size())
        return 0;
    if(length < rowRule[m][block])
        return 1;
    else
        return 0;
}

int black_check_column(int m, int n){
    int length = 0, block = 0;
    for(int i = 0; i < m; i++){
        if(nono[i][n] == 1)
            length++;
        else{
            if(nono[i][n] == -1 && length != 0){
                length = 0;
                block++;
            }
        }
    } 
    if(block == columnRule[n].size())
        return 0;
    if(length < columnRule[n][block])
        return 1;
    else
        return 0;
}

int white_check_row(int m, int n){
    int length = 0, block = 0, backCell = 0;
    for(int i = 0; i < n; i++){
        if(nono[m][i] == 1)
            length++;
        else{
            if(nono[m][i] == -1 && length != 0){
                length = 0;
                block++;
            }
        }
    }
    if(block == rowRule[m].size())
        return 1;
    if(length != 0){
        if(length < rowRule[m][block])
            return 0;
        else 
            return 1;
    }
    for(int i = block; i < rowRule[m].size(); i++){
        backCell += rowRule[m][i];
        backCell++;
    }
    if(columnNumber-n < backCell)
        return 0;
    else
        return 1; 
}

int white_check_column(int m, int n){
    int length = 0, block = 0, backCell = 0;
    for(int i = 0; i < m; i++){
        if(nono[i][n] == 1)
            length++;
        else{
            if(nono[i][n] == -1 && length != 0){
                length = 0;
                block++;
            }
        }
    }
    if(block == columnRule[n].size())
        return 1;
    if(length != 0){
        if(length < columnRule[n][block])
            return 0;
        else 
            return 1;
    }
    for(int i = block; i < columnRule[n].size(); i++){
        backCell += columnRule[n][i];
        backCell++;
    }
    if(rowNumber-m < backCell)
        return 0;
    else
        return 1; 
}

void print_nono(){
    for(int i = 0; i < rowNumber; i++){
        for(int j = 0; j < columnNumber; j++){
            if(nono[i][j] == 1) cout << '#';
            else if(nono[i][j] == -1) cout << '.';
            else cout << 'j';
        }
        cout << endl;
    }    
}

void print_preNono(){
    for(int i = 0; i < rowNumber; i++){
        for(int j = 0; j < columnNumber; j++){
            if(preNono[i][j] == 1) cout << '#';
            else if(preNono[i][j] == -1) cout << '.';
            else cout << 'j';
        }
        cout << endl;
    }    
    cout << endl;
}

int check_complete(int Row_or_Column, int num){
    if(Row_or_Column){
        int x = 0,check[30] = {0};    
        for(int i = 0; i < columnNumber; i++){
            if(nono[num][i] == 1){
                check[x]++;
            }        
            if((nono[num][i] == 1 && i == columnNumber-1) || (nono[num][i] == 1 && nono[num][i+1] == -1 && i != columnNumber-1)) x++;
        }
        for(int i = 0; i < rowRule[num].size(); i++){
            if(rowRule[num][i] != check[i]) return 0;
        } 
        if(check[rowRule[num].size()] == 0) return 1;
        else return 0;
    }
    else{
        int x = 0,check[30] = {0};    
        for(int i = 0; i < rowNumber; i++){
            if(nono[i][num] == 1){
                check[x]++;
            }        
            if((nono[i][num] == 1 && i == rowNumber-1) || (nono[i][num] == 1 && nono[i+1][num] == -1 && i != rowNumber-1)) x++;
        }
        for(int i = 0; i < columnRule[num].size(); i++){
            if(columnRule[num][i] != check[i]) return 0;
        } 
        if(check[columnRule[num].size()] == 0) return 1;
        else return 0;
    }       
}

void preTreat(){
    for(int i = 0; i < rowNumber; i++){
        int restCell = columnNumber;
        for(int j = 0; j < rowRule[i].size(); j++){
            line[2*j+1] = rowRule[i][j];    
            restCell -= rowRule[i][j];        
        }
        line[2*rowRule[i].size()+1] = -1;
        preTreat_dfs(0,rowRule[i].size(),restCell);
        for(int j = 0; j < columnNumber; j++){
            preNono_row[i][j] = nonoLine[j];
            nonoLine[j] = 0;
        }
        for(int j = 0; j < 2*(rowRule[i].size()+1); j++){
            line[j] = 0;
        }
    } 
    for(int i = 0; i < columnNumber; i++){
        int restCell = rowNumber;
        for(int j = 0; j < columnRule[i].size(); j++){
            line[2*j+1] = columnRule[i][j];    
            restCell -= columnRule[i][j];        
        }
        line[2*columnRule[i].size()+1] = -1;
        preTreat_dfs(0,columnRule[i].size(),restCell); 
        for(int j = 0; j < rowNumber; j++){
            preNono_column[j][i] = nonoLine[j];
            nonoLine[j] = 0;
        }
        for(int j = 0; j < 2*(columnRule[i].size()+1); j++){
            line[j] = 0;
        }
    }
    for(int i = 0; i < rowNumber; i++){
        for(int j = 0; j < columnNumber; j++){
            if(preNono_row[i][j] != 2)
                preNono[i][j] = preNono_row[i][j];
            if(preNono_column[i][j] != 2){
                if(preNono[i][j] != 0 && preNono[i][j] != preNono_column[i][j])
                preNono[i][j] = preNono_column[i][j];
            }           
        }
    }    
}

void preTreat_dfs(int spaceCount, int spaceNum, int restCell){
    if(spaceCount == spaceNum){
        line[2*spaceCount] = restCell;
        int k = 0;
        for(int i = 0; i < 2*spaceNum+1; i++){
            for(int j = 0; j < line[i]; j++){
                if(i%2){
                    if(nonoLine[k] == 0 || nonoLine[k] == 1)
                        nonoLine[k] = 1;
                    else
                        nonoLine[k] = 2;
                }
                else{
                    if(nonoLine[k] == 0 || nonoLine[k] == -1){
                        nonoLine[k] = -1;
                    }
                    else
                        nonoLine[k] = 2;
                }
                k++;
            }                    
        }
        line[2*spaceCount] = 0;
        return;
    }
    int upperLimit = restCell - spaceNum + spaceCount + 1;
    for(int i = 0; i <= upperLimit ;i++){
        if(spaceCount != 0 && i == 0) continue;
        line[2*spaceCount] = i;
        preTreat_dfs(spaceCount+1, spaceNum, restCell-i);
        line[2*spaceCount] = 0;    
    }
}

void print_line(){
    for(int i = 0; line[i] != -1; i++){
        cout << line[i] << " ";
    }
    cout << endl;
}

void print_nonoLine(){
    for(int i = 0; i < 30; i++){
        cout << nonoLine[i] << " ";
    }
    cout << endl;
}

int main(){
    int m = 0, n = 0;
    string gline;
    cin >> rowNumber >> columnNumber;
    cin.ignore(100,'\n');
    nono = new int*[rowNumber];
    for(int i = 0; i < rowNumber; i++){
        nono[i] = new int[columnNumber]();
    }
    preNono = new int*[rowNumber];
    for(int i = 0; i < rowNumber; i++){
        preNono[i] = new int[columnNumber]();
    }
    preNono_row = new int*[rowNumber];
    for(int i = 0; i < rowNumber; i++){
        preNono_row[i] = new int[columnNumber]();
    }
    preNono_column = new int*[rowNumber];
    for(int i = 0; i < rowNumber; i++){
        preNono_column[i] = new int[columnNumber]();
    }
    rowRule = new vector<int>[rowNumber];
    columnRule = new vector<int>[columnNumber];
    while(m < rowNumber){
        int num;
        getline(cin,gline);
        istringstream ss(gline);
        while(ss >> num){
            rowRule[m].push_back(num);
        } 
        m++;
    }
    while(n < columnNumber){
        int num;
        getline(cin,gline);
        istringstream ss(gline);
        while(ss >> num){
            columnRule[n].push_back(num);
        } 
        n++;
    }    
    preTreat();   
    dfs_solve(0,0);
    return 0;
}
