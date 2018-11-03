#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstring>
#include<unordered_map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
#define H 51537341
//#define H 9433186 
//#define H 80062687
//#define H 5000
#define C 10

int argc;
char **argv;

FILE *file;
bool input = 0;
string *hash_table;

unordered_map <string, long long int> freq;



//bool(*fn_pt)(string,string) = comp;

vector<string> edit_tmp;
vector<string> edit_set;

bool comp(string a, string b){
    if(freq[a] == freq[b]){
        return a < b;
    }
    else{
        return freq[a] > freq[b];
    }
}

//set<string,bool(*)(string, string)> edit_set_sort(fn_pt);

string prepo[] = {"of", "to", "in", "for", "with", "on", "at", "by", "from", "up", "about", "than", "after", "before", "down", "between", "under", "since", "without", "near"};

string prepo_space[] = {" of ", " to ", " in ", " for ", " with ", " on ", " at ", " by ", " from ", " up ", " about ", " than ", " after ", " before ", " down ", " between ", " under ", " since ", " without ", " near "};

string prepo_suffix_space[] = {"of ", "to ", "in ", "for ", "with ", "on ", "at ", "by ", "from ", "up ", "about ", "than ", "after ", "before ", "down ", "between ", "under ", "since ", "without ", "near "};



int readchar(){
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        end = buf + fread(buf, 1, N, file);
        if(end == buf) {
            return EOF;  
        }
        p = buf;
    }
    return *p++;
}

int readchar2(){
    static int N2 = 1<<20;
    static char buf2[1<<20];
    static char *p2 = buf2, *end2 = buf2;
    if(p2 == end2) {
        end2 = buf2 + fread(buf2, 1, N2, stdin);
        if(end2 == buf2) {
            return EOF;  
        }
        p2 = buf2;
    }
    return *p2++;
}

bool end_of_file = 0;

void ReadInt(unsigned long long *x) {
    char c; //neg;
    *x = 0;
    while(((c = readchar()) != ' ') && (c != '\n')){
        if(c == EOF){
            end_of_file = 1;
            return;
        }
        *x = (*x << 3) + (*x << 1) + c-'0';
    }
    //*x *= neg;
    return;
}

void ReadString(char *s){
    char c;
    int i = 0;
    //while((c = readchar()) >= '0' || c == EOF){
    while((c = input ? readchar2() : readchar()) != '\n' && c != 9){    
        if(c == EOF){
            //s[i] = c;
            //return 0;
            end_of_file = 1;
            return;
        }
        *s++ = c;
    }
    *s = '\0';
    return;
}

void search(string s){
    unsigned int h = 0;
    h = s[0];
    for(int i = 1; i < s.length(); i++){
        h *= 519;
        h += s[i];
    }
    h = h%H;
    int flag = 0;
    for(int i = 0; i < C; i++){
        if(hash_table[h*C + i] == ""){
            break;
        }
        else{
            if(hash_table[h*C + i] == s){
                edit_set.push_back(s);    
            }
        }
    }
}

void edit_a(string s){
    s.insert(0, 1, ' ');
    s.insert(s.length(), 1, ' ');
    for(int i = 0; i < s.length(); i++){
        if(s[i] == ' '){
            for(int j = 0; j < 20; j++){
                string v = s;
                v.insert(i+1, prepo_suffix_space[j]);
                v.erase(v.begin());
                v.erase(v.end()-1);
                edit_tmp.push_back(v);
            }   
        }
    }
}

vector<string> edit_product[1000];

int a = 0;
void dfs(int n, string s, int bound){
    if(n == bound){
        //cout << s << endl;
        s.erase(s.begin());
        s.erase(s.end()-1);
        search(s);
        return;
    }
    for(int i = 0; i < edit_product[n].size(); i++){
        string v = s;
        s.replace(s.find('#'), 1, edit_product[n][i]);
        dfs(n+1, s, bound);
        s = v;
    }
    return;
}

void edit_b(string s){
    string w;
    s.insert(0, 1, ' ');
    s.insert(s.length(), 1, ' ');
    //char *s = new char[200];
    for(int i = 0; i < s.length(); i++){
        if(s[i] == ' '){
            for(int j = 0; j < 20; j++){
                if(w == prepo[j]){
                    s[i] = '0'; 
                    if(s[i-w.length()-1] == '0'){
                        s[i-w.length()-1] = '1';
                    }
                    else{
                        s[i-w.length()-1] = '0';
                    }  
                    break;
                }
            }
            w.clear();
        }
        else{
            w += s[i];   
            //cout << w << endl;
        }  
    }
    //s.erase(s.end()-1);
    //cout << s << endl;
    int flag = 0;
    int ps_num = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '0'){
            if(!flag){
                flag = 1;
            }
            else{
                w += " ";
                //cout << i-w.length()+1 << " " << i << endl;
                for(int j = 0; j < w.length(); j++){
                    if(w[j] == ' '){
                        for(int k = 0; k < 20; k++){
                            string v = w;
                            v.insert(j+1, prepo_suffix_space[k]);
                            edit_product[ps_num].push_back(v);
                        }   
                    }
                }
                int l = 0;
                for(int j = 0; j < w.length(); j++){
                    if(w[j] != ' '){
                        l++;
                    }
                    else{
                        if(l != 0){
                            string v = w;
                            v.replace(j-l-1, l+1, "");
                            edit_product[ps_num].push_back(v);
                            l = 0;
                        }
                    }
                }
                l = 0;
                for(int j = 0; j < w.length(); j++){
                    if(w[j] != ' '){
                        l++;
                    }
                    else{
                        if(l != 0){
                            for(int k = 0; k < 20; k++){
                                string v = w;
                                v.replace(j-l, l, prepo[k]);
                                edit_product[ps_num].push_back(v);
                            }
                            l = 0;
                        }
                    }
                }
                ps_num++;
                s.replace(i-w.length()+1, w.length(), "#");
                i = i-w.length()+1;
                w.clear();
                flag = 0;
            }
        }
        if(flag){
            if(s[i] == '0' || s[i] == '1'){
                w += ' ';
            }
            else{
                w += s[i];
            }
            //cout << w << endl;
        }
    }
    //cout << ps_num << endl;
    dfs(0, s, ps_num);
    for(int i = 0; i < ps_num; i++){
        edit_product[i].clear();
    }
    //blablablalbla
}

//int main(){
int main(int argc, char **argv){
    hash_table = new string[H * C];
   /* for(int i = 0; i < H; i++){*/
        //hash_table[i] = new string[C];
    /*}*/
    file = fopen(argv[1], "r");
    while(1){
        unsigned long long x;
        char *c = new char[300];
        ReadInt(&x);
        if(end_of_file)
            break;
        ReadString(c);
        for(int i = 0; i < C; i++){
            if(hash_table[x*C + i] == ""){
                hash_table[x*C + i] = c;
                break;
            }
        }
        ReadInt(&x);
        string s(c); //??
        freq[s] = x;
        delete(c);
    }
    /*unsigned long long x;*/
    //ReadInt(&x);
    /*cout << x << endl;*/
    //cout << "gg" << endl;
    end_of_file = 0;
    input = 1;
    fclose(file);
    while(1){
        char *c = new char[100];
        ReadString(c);
        if(end_of_file)
            break;
        string s(c);
        string ss = s;
        search(s);
        cout << "query: " << s << endl;
        ss.insert(ss.begin(), 1, ' ');
        ss.insert(ss.end(), 1, ' ');
        int flag = 0;
        for(int i = 0; i < 20; i++){
            if(ss.find(prepo_space[i]) != ss.npos){
                //cout << prepo_space[i] << endl;
                flag = 1;
                break;
            }
        }
        if(flag){
            edit_b(s);
        }
        else{
            edit_tmp.push_back(s);
            edit_a(s);
            a = edit_tmp.size();
            for(int i = 1; i < a; i++){
                edit_a(edit_tmp[i]);
            }
            for(int i = 0; i < edit_tmp.size(); i++){
                search(edit_tmp[i]);
            }
            //cout << edit_tmp.size() << endl;
            edit_tmp.clear();

        }
        sort(edit_set.begin(), edit_set.end(), comp);
        int ii = 0;
        //edit_set_sort = edit_set;
        int up = 10;
        string tmp = "";
        string ans_s[10];
        long long int ans_n[10];
        for(vector<string>::iterator it = edit_set.begin(); it != edit_set.end(); it++){
            if(*it == tmp){
                continue;
            }
            else{
                ans_s[ii] = *it;
                ans_n[ii] = freq[*it];
                ii++;
                tmp = *it;
            }
            if(ii == up){
                break;
            }
        }
        cout << "output: " << ii << endl;
        for(int i = 0; i < ii; i++){
            cout << ans_s[i] << "\t" << ans_n[i] << endl; 
        }
        edit_set.clear();
        delete(c);
        //cout << s << endl;
    } 
    /*for(int i = 0; i < H; i++){*/
        //for(int j = 0; j < C; j++){
            //if(hash_table[i*C + j] == ""){
                //break;
            //}
            //else{
                ////cout << i << " " << hash_table[i*C + j] << " " << freq[hash_table[i*C + j]] << endl;
            //}
        //}
    /*}*/
}
