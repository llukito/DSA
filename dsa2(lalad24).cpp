#include <bits/stdc++.h>
using namespace std;

struct nodeInfo{
    int next;
    int maxG[3];
    int minG[3];
};

nodeInfo compute(string& str, int idx){
    char type = str[idx];
    nodeInfo res;

    if(type == '0'){
        res.next = idx + 1;
        res.maxG[0] = 0; res.maxG[1] = 1; res.maxG[2] = 0;
        res.minG[0] = 0; res.minG[1] = 1; res.minG[2] = 0;
    } else if(type == '1'){
        nodeInfo node1 = compute(str, idx+1);
        res.next = node1.next;
        
        for(int i=0; i < 3; i++){
            res.maxG[i] = INT_MIN;
            res.minG[i] = INT_MAX;
            for(int j=0; j<3; j++){
                if(j==i)continue;
                res.maxG[i] = max(res.maxG[i], (i==1) + node1.maxG[j]);
                res.minG[i] = min(res.minG[i], (i==1) + node1.minG[j]);
            }
        }
    } else { // type is '2'
        nodeInfo node1 = compute(str, idx+1);
        nodeInfo node2 = compute(str, node1.next);
        res.next = node2.next;
        
        for(int i=0; i < 3; i++){
            res.maxG[i] = INT_MIN;
            res.minG[i] = INT_MAX;
            for(int j=0; j<3; j++){
                if(j==i)continue;
                for(int k=0; k<3; k++){
                    if(k == j || k == i)continue;
                    res.maxG[i] = max(res.maxG[i], (i==1) + node1.maxG[j] + node2.maxG[k]);
                    res.minG[i] = min(res.minG[i], (i==1) + node1.minG[j] + node2.minG[k]);
                }
            }
        }
    }
    return res;
}

int main(){
    //to make it faster
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin>>str;
    nodeInfo resultInfo = compute(str, 0);
    int max_ = max(max(resultInfo.maxG[0], resultInfo.maxG[1]), resultInfo.maxG[2]);
    int min_ = min(min(resultInfo.minG[0], resultInfo.minG[1]), resultInfo.minG[2]);
    
    string res = to_string(max_) + " " + to_string(min_);
    cout<<res<<endl;
    return 0;
}
