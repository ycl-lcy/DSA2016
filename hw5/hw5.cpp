#include<iostream>
#include<sstream>
#include<fstream>
#include<cstring>
#include<unordered_set>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

unordered_set<string> dic;
set<string> words_unic;
vector<string> words;
char alpha[] = "abcdefghijklmnopqrstuvwxyz";
int words_count;

void gen_words(string& init_s, bool n){
    string s;
    for(int i = 0; i <= init_s.length(); i++){
        for(int j = 0; j < 26; j++){
            s = init_s;
            s.insert(i, 1, alpha[j]); 
            if(n){
                words.push_back(s);
                words_count++;
            }
            if(dic.find(s) != dic.end()){
                words_unic.insert(s);
            }
        }          
    }
    for(int i = 0; i < init_s.length(); i++){
        s = init_s;
        s.erase(s.begin()+i);
        if(n){
            words.push_back(s);
            words_count++;
        }
        if(dic.find(s) != dic.end()){
            words_unic.insert(s);
        }
    }
    for(int i = 0; i < init_s.length(); i++){
        for(int j = 0; j < 26; j++){
            s = init_s;
            s[i] = alpha[j];
            if(n){
                words.push_back(s);
                words_count++;
            }
            if(dic.find(s) != dic.end()){
                words_unic.insert(s);
            }
        }
    }
    if(init_s.length() > 0){
        for(int i = 0; i < init_s.length()-1; i++){
            s = init_s;
            swap(s[i], s[i+1]);
            if(n){
                words.push_back(s);
                words_count++;
            }
            if(dic.find(s) != dic.end()){
                words_unic.insert(s);
            }
        }
    }     
}

int main(){
    ifstream fin("/tmp2/dsa2016_hw5/cmudict-0.7b");
    string line, s;
    dic.reserve(350000);
    while(getline(fin, line)){
        istringstream in(line);
        in >> s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        dic.insert(s);
    }
    while(getline(cin, line)){
        words_count = 0;
        istringstream in(line);
        in >> s;
        cout << s << " ==>";
        if(dic.find(s) != dic.end()){
            cout << " OK" << endl;
        }
        else{
            gen_words(s,1);
            for(int i = 0; i < words_count; i++){
                gen_words(words[i],0);
            }
            if(words_unic.size() != 0){
                words.assign(words_unic.begin(), words_unic.end());                
                for(int i = 0; i < words.size(); i++){
                    cout << " " << words[i];
                }
                cout << endl;
            }
            else{
                cout << " NONE" << endl;
            }
            words.clear();
            words_unic.clear();
        }
    }   
    return 0;
}
