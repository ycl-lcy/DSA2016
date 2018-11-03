#include<iostream>
#include<sstream>
#include<vector>
#include<set>
using namespace std;

class BID{
    public: 
        int bidID;
        int clientID;
        int action;
        int price;
        int shareCount;
        BID(){
            bidID = -1;
            clientID = -1;
            action = -1;
        price = -1;
        shareCount = -1;
        }
        void init(int n){
            if(bidID == -1)
                bidID = n;
            else {
                if(clientID == -1)
                    clientID = n;
                else {
                    if(action == -1)
                        action = n;
                    else {
                        if(price == -1)
                            price = n;
                        else {
                            if(shareCount == -1)
                                shareCount = n;
                        }
                    }
                }
            }    
        }
};

vector<BID> buyMax;
vector<BID> sellMin;
set<int> cancel;

void upHeap_Max(){
    int n = buyMax.size()-1;
    while(1){
        if(n == 1)
            return;
        if(buyMax[n/2].price < buyMax[n].price){
            swap(buyMax[n/2], buyMax[n]);
            n = n/2;
        }
        else {
            if(buyMax[n/2].price == buyMax[n].price){
                if(buyMax[n/2].bidID > buyMax[n].bidID){
                    swap(buyMax[n/2], buyMax[n]);
                    n = n/2;
                }
                else    
                    return;
            }
            else 
                return;
        }
    }
}

void upHeap_Min(){
    int n = sellMin.size()-1;
    while(1){
        if(n == 1)
            return;
        if(sellMin[n/2].price > sellMin[n].price){
            swap(sellMin[n/2], sellMin[n]);
            n = n/2;
        }
        else {
            if(sellMin[n/2].price == sellMin[n].price){
                if(sellMin[n/2].bidID > sellMin[n].bidID){
                    swap(sellMin[n/2], sellMin[n]);
                    n = n/2;
                }
                else    
                    return;
            }
            else 
                return;
        }
    }
}

void removeTop_buyMax(){
    int n = 1;
    swap(buyMax[1], buyMax[buyMax.size()-1]);
    buyMax.pop_back();
    while(1){
        if(2*n > buyMax.size()-1)
            return;
        else {
            if(2*n == buyMax.size()-1){
                if(buyMax[2*n].price > buyMax[n].price){
                    swap(buyMax[n], buyMax[2*n]);
                    n = 2*n;
                }
                else{
                    if(buyMax[2*n].price == buyMax[n].price){
                        if(buyMax[2*n].bidID < buyMax[n].bidID){
                            swap(buyMax[n], buyMax[2*n]);
                            n = 2*n;
                        }
                        else{
                            if(buyMax[2*n].bidID > buyMax[n].bidID)
                                return;
                        }
                    }
                    else 
                        return;
                }
            }
            else {
                int m;
                if(buyMax[2*n].price >= buyMax[n].price || buyMax[2*n+1].price >= buyMax[n].price){
                    if(buyMax[2*n].price > buyMax[2*n+1].price)
                        m = 2*n;
                    if(buyMax[2*n].price < buyMax[2*n+1].price)
                        m = 2*n+1;
                    if(buyMax[2*n].price == buyMax[2*n+1].price){
                        if(buyMax[2*n].bidID < buyMax[2*n+1].bidID)
                            m = 2*n;
                        if(buyMax[2*n].bidID > buyMax[2*n+1].bidID)
                            m = 2*n+1;
                    }
                    if(buyMax[m].price > buyMax[n].price){
                        swap(buyMax[n], buyMax[m]);
                        n = m;
                    }
                    else{
                        if(buyMax[m].price == buyMax[n].price){
                            if(buyMax[m].bidID < buyMax[n].bidID){
                                swap(buyMax[n], buyMax[m]);
                                n = m;
                            }
                            else{
                                if(buyMax[m].bidID > buyMax[n].bidID)
                                    return;
                            }
                        }
                    }
                }
                else
                    return;   
            }
        }
    }
}

void removeTop_sellMin(){
    int n = 1;
    swap(sellMin[1], sellMin[sellMin.size()-1]);
    sellMin.pop_back();
    while(1){
        if(2*n > sellMin.size()-1)
            return;
        else {
            if(2*n == sellMin.size()-1){
                if(sellMin[2*n].price < sellMin[n].price){
                    swap(sellMin[n], sellMin[2*n]);
                    n = 2*n;
                }
                else{
                    if(sellMin[2*n].price == sellMin[n].price){
                        if(sellMin[2*n].bidID < sellMin[n].bidID){
                            swap(sellMin[n], sellMin[2*n]);
                            n = 2*n;
                        }
                        else{
                            if(sellMin[2*n].bidID > sellMin[n].bidID)
                                return;
                        }
                    }
                    else 
                        return;
                }
            }
            else {
                int m;
                if(sellMin[2*n].price <= sellMin[n].price || sellMin[2*n+1].price <= sellMin[n].price){
                    if(sellMin[2*n].price < sellMin[2*n+1].price)
                        m = 2*n;
                    if(sellMin[2*n].price > sellMin[2*n+1].price)
                        m = 2*n+1;
                    if(sellMin[2*n].price == sellMin[2*n+1].price){
                        if(sellMin[2*n].bidID < sellMin[2*n+1].bidID)
                            m = 2*n;
                        if(sellMin[2*n].bidID > sellMin[2*n+1].bidID)
                            m = 2*n+1;
                    }
                    if(sellMin[m].price < sellMin[n].price){
                        swap(sellMin[n], sellMin[m]);
                        n = m;
                    }
                    else{
                        if(sellMin[m].price == sellMin[n].price){
                            if(sellMin[m].bidID < sellMin[n].bidID){
                                swap(sellMin[n], sellMin[m]);
                                n = m;
                            }
                            else{
                                if(sellMin[m].bidID > sellMin[n].bidID)
                                    return;
                            }
                        }
                    }
                }
                else
                    return;   
            }
        }
    }
}

int main(){
    string line;
    int s, transID = 0;
    BID empty;
    buyMax.push_back(empty);
    sellMin.push_back(empty);
    while(getline(cin,line)){
        istringstream ss(line);
        BID bid;
        while(ss >> s)
            bid.init(s);   
        if(bid.action == 0){
            buyMax.push_back(bid);
            upHeap_Max();
        }
        if(bid.action == 1){
            sellMin.push_back(bid);   
            upHeap_Min();
        }
        if(bid.action == 2){
            cancel.insert(bid.price);           
        }
        while(1){
            if(buyMax[1].price >= sellMin[1].price && buyMax.size() > 1 && sellMin.size() > 1){
                if(cancel.find(buyMax[1].bidID) != cancel.end()){
                    removeTop_buyMax();
                    continue;
                }
                if(cancel.find(sellMin[1].bidID) != cancel.end()){
                    removeTop_sellMin();
                    continue;
                }
                if(buyMax[1].shareCount < sellMin[1].shareCount){
                    cout << transID << '\t' << buyMax[1].clientID << '\t' << sellMin[1].clientID << '\t' << sellMin[1].price << '\t' << buyMax[1].shareCount << endl;
                    sellMin[1].shareCount -= buyMax[1].shareCount; 
                    removeTop_buyMax();
                    transID++;
                }
                else {
                    if(buyMax[1].shareCount > sellMin[1].shareCount){
                        cout << transID << '\t' << buyMax[1].clientID << '\t' << sellMin[1].clientID << '\t' << sellMin[1].price << '\t' << sellMin[1].shareCount << endl;
                        buyMax[1].shareCount -= sellMin[1].shareCount;
                        removeTop_sellMin();
                        transID++;
                    }
                    else {
                        cout << transID << '\t' << buyMax[1].clientID << '\t' << sellMin[1].clientID << '\t' << sellMin[1].price << '\t' << buyMax[1].shareCount << endl;
                        removeTop_buyMax();
                        removeTop_sellMin();
                        transID++;
                    }
                }
            }
            else 
                break;
        }
    }
    return 0;
}
