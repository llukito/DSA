#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
int n;
long long mod;
vector<int> primeDivisors(MAX+1, 0);
vector<int> freqOfDivisors(MAX+1, 0);

void erastos(){
    for(int i=2; i<=MAX; i++){
        if(primeDivisors[i]!=0) continue;
        for(long long j=1ll * i * i; j<=MAX; j+=i){
            if(primeDivisors[j]==0){
                primeDivisors[j] = i;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    erastos();
    cin >> n >> mod;
    for(int i=0; i<n; i++){
        int temp = 0; cin >> temp;
        if(temp == 1) continue;
        while(temp > 1){
            int p = (primeDivisors[temp] == 0) ? temp : primeDivisors[temp];
            int curr = 0;
            while(temp % p == 0){
                temp /= p;
                curr++;
            }
            if(freqOfDivisors[p] < curr) freqOfDivisors[p] = curr;
        }
    }

    long long allDivisors = 1;
    for(int p = 2; p <= MAX; p++){
        if(freqOfDivisors[p] > 0){
            allDivisors = (allDivisors * ((freqOfDivisors[p] + 1) % mod)) % mod;
        }
    }

    long long res = (allDivisors - (n % mod) + mod) % mod;
    cout << res << endl;
    return 0;
}
