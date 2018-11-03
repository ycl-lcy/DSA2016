#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
//#define H 13
//#define H 120000001
//#define H 80062687
//#define A 405321751
//#define H 2839503131
#define H 51537341
int hash_table[H] = {0}; 
int a[H] = {0};
int argc;
char **argv;

FILE* file;
FILE* ofile;
int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, file)) == buf) {
            hasEOF = 1;
            return EOF;  
        }
        p = buf;
    }
    return *p++;
}
void ReadInt(unsigned long long *x) {
    char c; //neg;
    *x = 0;
    while((c = readchar()) != '\n')
        *x = (*x << 3) + (*x << 1) + c-'0';
    //*x *= neg;
    return;
}

bool end_of_file = 0;
void ReadString(char *s){
    char c;
    int i = 0;
    //while((c = readchar()) >= '0' || c == EOF){
    while((c = readchar()) != 9){    
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

unsigned int setHash(char *s){
    unsigned int h = 0;
    h = s[0];
    for(int i = 1; i < strlen(s); i++){
        //cout << i << endl;
        h *= 519;
        h += s[i];
    }
    h = h%H;
    char *n = new char[20];
    sprintf(n, "%d", h);
    fputs(n, ofile);
    fputs(" ", ofile);
    //strcat(s, " ");
    //strcat(s, n);
    //strcat(s, "\n");
    //cout << s;
    delete(n);
    hash_table[h]++;
}

int main(int argc, char **argv){
    file = fopen("/tmp2/gm", "r");
    ofile = fopen(argv[1], "w");
    unsigned long long x;
    while(1){
        char *p = new char[1000];
        char *n = new char[30];
        ReadString(p);
        if(end_of_file)
            break;
        //add(p);
        //cout << p << endl;
        setHash(p);
        fputs(p, ofile);
        fputs("\t", ofile);
        ReadInt(&x);
        sprintf(n, "%llu", x);
        fputs(n, ofile);
        //cout << x << endl;
        fputs("\n", ofile);
        delete(p);
        delete(n);
    } 
    //for(int i = 0; i < H; i++){
        //a[hash_table[i]]++;
    //}
    //for(int i = 1; i < H; i++){
        //if(a[i] != 0){
            //cout << a[i] << " " << i << endl;
        //}
    //}
    return 0;
}
