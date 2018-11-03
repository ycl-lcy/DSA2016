#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<utility>
#include<set>
#include<map>
#include<vector>
using namespace std;

#define DATA 73209277
#define ITEM 4710

clock_t start, finish;

struct Item{
    Item(){
        userCount = 0;
    }
    int itemID;
    int userCount;
    struct User* user;
};

struct User{
    User(){
        timeCount = 0;
    }
    int userID;
    int timeCount;
    struct Time* time;
};

struct Time{
    int timeStamp;
    int accept;
};

struct Data{
    Data(){
        itemID = 0;
        userID = 0;
        timeStamp = 0;
        accept = 0;
    }   
    int itemID;
    int userID;
    int timeStamp;
    int accept;
    void add(int a){
        if (userID == 0) userID = a;
        else if(itemID == 0) itemID = a;
        else if(accept == 0) accept = a;
        else if(timeStamp == 0) timeStamp = a;
    }
    void print(){
        cout << userID << " " << itemID << " " << accept << " " << timeStamp << endl;
    }
};

struct Recommend{
    int userID;
    int times;
};

Data* data;
Item* item;
int* rec;
set<int> timeCollect;
set<int>::iterator timeIt;
map<int,int> userRec;
vector<int> v;
vector<int>::iterator vit;

bool cmp(const Data x, const Data y){
    if(x.itemID == y.itemID){
        if(x.userID == y.userID){
                return x.timeStamp < y.timeStamp;
        }
        return x.userID < y.userID;
    }
    else return x.itemID < y.itemID;
}

bool cmp_rev(const Data x, const Data y){
    return x.userID < y.userID;
}

void readFile(FILE* file){
    int x = 0, i = 0, k = 0, c = 0, neg = 0;
    while(1){
        c = fgetc(file);
        if(c == '\n'){ 
            data[i].add(x);
            x = 0;
            i++;
            continue;
        }
        if(c == '\t' || c == ' '){
            data[i].add(x);
            x = 0;
            neg = 0;
            continue;
        }
        if(c == '-'){
            neg = 1;
            continue;
        }
        if(c == EOF) break;
        x = (x<<1) + (x<<3) + c - 48;
        if(neg) x *= -1;
    }
}

int item_cmp(const void* a, const void* b){
    return ((*(Item*)a).itemID - (*(Item*)b).itemID);
}

int user_cmp(const void* a, const void* b){
    return ((*(User*)a).userID - (*(User*)b).userID);
}

int time_cmp(const void* a, const void* b){
    return ((*(Time*)a).timeStamp - (*(Time*)b).timeStamp);
}
void accept(int u, int i0, int t){
    Item* a;
    User* b;
    Time* c;
    a = (Item*)bsearch(&i0, item, ITEM, sizeof(Item), item_cmp);
    if(a == NULL){
        cout << 0 << endl;
        return;
    }
    b = (User*)bsearch(&u, a->user, a->userCount, sizeof(User), user_cmp);
    if(b == NULL){
        cout << 0 << endl;
        return;
    }
    c = (Time*)bsearch(&t, b->time, b->timeCount, sizeof(Time), time_cmp);
    if(c == NULL){
        cout << 0 << endl;
        return;
    }
    cout << c->accept << endl;
}

void items(int u1, int u2){
    User *a, *b;
    bool j = 1;
    for(int i = 0; i < ITEM; i++){
        a = (User*)bsearch(&u1, item[i].user, item[i].userCount, sizeof(User), user_cmp);
        if(a == NULL) continue;
        b = (User*)bsearch(&u2, item[i].user, item[i].userCount, sizeof(User), user_cmp);
        if(b == NULL) continue;
        cout << item[i].itemID << endl;
        j = 0;
    }
    if(j) cout << "EMPTY" << endl;
};
void users(int i1, int i2, int t1, int t2){
    Item* pi1 = (Item*)bsearch(&i1, item, ITEM, sizeof(Item), item_cmp);
    Item* pi2 = (Item*)bsearch(&i2, item, ITEM, sizeof(Item), item_cmp);
    vector<int> v1;
    vector<int> v2;
    int tmpCount, j = 0;
    if(pi1->userCount > pi2->userCount)
        tmpCount = pi2->userCount;
    else tmpCount = pi1->userCount;
    for(int j = 0; j < pi1->userCount; j++){
        for(int k = 0; k < pi1->user[j].timeCount; k++){
            if(pi1->user[j].time[k].timeStamp >= t1 && pi1->user[j].time[k].timeStamp <= t2){
                v1.push_back(pi1->user[j].userID);
                k = pi1->user[j].timeCount;
            }
        }
    }
    for(int j = 0; j < pi2->userCount; j++){
        for(int k = 0; k < pi2->user[j].timeCount; k++){
            if(pi2->user[j].time[k].timeStamp >= t1 && pi2->user[j].time[k].timeStamp <= t2){
                v2.push_back(pi2->user[j].userID);
                k = pi2->user[j].timeCount;
            }
        }
    }
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));
    for(vit = v.begin(); vit != v.end(); vit++) cout << *vit << endl;
    if(v.empty()) cout << "EMPTY" << endl;
    v.clear();
};
void ratio(int i0, int threshold){
    int total = rec[threshold];
    int accept = 0;
    Item* itp= (Item*)bsearch(&i0, item, ITEM, sizeof(Item), item_cmp);
    for(int i = 0; i < itp->userCount; i++){
        if(userRec[itp->user[i].userID] > threshold){
             for(int j = 0; j < itp->user[i].timeCount; j++){
                if((*itp).user[i].time[j].accept == 1){
                    accept++;
                    j = itp->user[i].timeCount;
                }
            }
        }
    }
    cout << accept << "/" << total << endl;
};
void findtime_item(int i0, int* us, int x){
    Item* it = (Item*)bsearch(&i0, item, ITEM, sizeof(Item), item_cmp);
    for(int i = 0; i < x; i++){
        User* usp = (User*)bsearch(&us[i], it->user, it->userCount, sizeof(User), user_cmp);
        if(usp != NULL){ 
            for(int j = 0; j < usp->timeCount; j++){
                timeCollect.insert(usp->time[j].timeStamp);
            }
        }
    }
    if(timeCollect.empty()) cout << "EMPTY" << endl;
    for(timeIt = timeCollect.begin(); timeIt != timeCollect.end(); timeIt++){
        cout << *timeIt << endl;   
    }
    timeCollect.clear();
};
int main(){
    data = new Data[DATA];
    item = new Item[ITEM];
    rec = new int[100000]();
    FILE* file;
    file = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","r");
    readFile(file);   
    int i, j, k, l, tmp_item, tmp_user, y = 0, x = 0, count = 0, n, u, i0, t, u1, u2, i1, i2, t1, t2, threshold;
    string action;  
    int us[100000];
    Data tmpdata;
    sort(data,data+DATA,cmp);
    tmp_user = 0;
    for(i = 0; i < ITEM; i++){
        item[i].itemID = data[y].itemID;
        tmp_item = data[y].itemID;
        for(;y < DATA; y++){
            if(data[y].itemID != tmp_item){
                tmp_user = 0;
                break;
            }
            if(data[y].userID == tmp_user) {
                if(data[y].itemID != tmp_item){
                    tmp_user = 0;
                    break;    
                }
                else continue;
            }
            else{
                item[i].userCount++;
                tmp_user = data[y].userID;
            }
        }
        item[i].user = new User[item[i].userCount];
    }
    tmp_item = data[0].itemID;
    tmp_user = data[0].userID;
    y = 0;
    for(i = 0; i < ITEM; i++){
        for(j = 0; j < item[i].userCount; j++){
            for(;y < DATA; y++){
                if(data[y].userID != tmp_user || (data[y].userID == tmp_user && data[y].itemID != tmp_item)){
                    tmp_item = data[y].itemID;
                    tmp_user = data[y].userID;    
                    break;
                }
                item[i].user[j].userID = data[y].userID;
                item[i].user[j].timeCount++;
                tmp_item = data[y].itemID;
                tmp_user = data[y].userID;               
            }
            item[i].user[j].time = new Time[item[i].user[j].timeCount];       
        }
    }
    y = 0;
    for(i = 0; i < ITEM && y < DATA; i++){
        for(j = 0; j < item[i].userCount && y < DATA; j++){
            if(userRec.find(item[i].user[j].userID) == userRec.end())
                userRec[item[i].user[j].userID] = 0;
            for(k = 0; k < item[i].user[j].timeCount && y < DATA; k++){
                    if(tmpdata.itemID == data[y].itemID && tmpdata.userID == data[y].userID && tmpdata.timeStamp == data[y].timeStamp){
                        item[i].user[j].timeCount--;
                        data[y].userID = 0;
                        y++;
                        k--;
                        continue;
                    }
                    userRec[item[i].user[j].userID]++;
                    tmpdata.itemID = data[y].itemID;
                    tmpdata.userID = data[y].userID;
                    tmpdata.timeStamp = data[y].timeStamp;
                    item[i].user[j].time[k].accept = data[y].accept;
                    item[i].user[j].time[k].timeStamp = data[y].timeStamp;
                    y++;
              
            }
        }
    }

    sort(data, data+DATA, cmp_rev);
    for(i = 0; i < DATA; i++){
        if(data[i].userID == 0) continue;
            count++;
        if(data[i+1].userID != data[i].userID || i == DATA-1){
            for(j = 0; j < count; j++) rec[j]++;    
            count = 0;           
        }
    }
    cin >> n;
    while(n--){
        cin >> action;
        if(action == "accept"){
            cin >> u >> i0 >> t;
            accept(u, i0, t);
        }
        if(action == "items"){
            cin >> u1 >> u2;
            items(u1, u2);
        }
        if(action == "users"){
            cin >> i1 >> i2 >> t1 >> t2;
            users(i1, i2, t1, t2);
        }
        if(action == "ratio"){
            cin >> i0 >> threshold;
            ratio(i0, threshold);
        }
        if(action == "findtime_item"){
            cin >> i0;
            string line;
            getline(cin, line);
            istringstream in(line);
            while(in >> us[x]) x++;
            findtime_item(i0, us, x);
            x = 0;
        }   
    }
    delete(rec);
    delete(item);
    delete(data);
    return 0;
}
