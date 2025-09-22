#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
int n;
long long mod;
vector<int> primeDivisors(MAX+1, 0);
unordered_map<int,int> freqOfDivisors;

void erastos(){
    for(int i=2; i<=MAX; i++){
        if(primeDivisors[i]!=0)continue;
        for(long long j=1ll* i*i; j<=MAX; j+=i){
            if(primeDivisors[j]==0){
                primeDivisors[j] = i;
            }
        }
    }
}

int main(){
    erastos();
    cin>>n>>mod;
    for(int i=0; i<n; i++){
        int temp = 0; cin>>temp;
        if(temp == 1)continue;
        unordered_map<int,int> currFreqOfDivisors;
        while(primeDivisors[temp]!=0){
            currFreqOfDivisors[primeDivisors[temp]]++;
            temp /= primeDivisors[temp];
        }
        currFreqOfDivisors[temp]++;
        for(auto& entry : currFreqOfDivisors){
            if(freqOfDivisors[entry.first] < entry.second){
                freqOfDivisors[entry.first] = entry.second; 
            }
        }
    }
    long long allDivisors = 1;
    for(auto& entry : freqOfDivisors){
        allDivisors = (allDivisors*((entry.second+1)%mod))%mod;;
    }
    long long missingDivisors = allDivisors - (n%mod) + mod;
    long long res = missingDivisors%mod;
    cout<<res<<endl;
    return 0;
}