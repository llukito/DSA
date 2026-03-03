#include <bits/stdc++.h>
using namespace std;

// I take a bit more than needed for safety
const int MAXN = 300005;

struct Meteor {
    int l, r;
    long long a;
};

int n, m, k;
vector<int> owner[MAXN];
long long req[MAXN];
Meteor meteors[MAXN];
int ans[MAXN];
long long bit[MAXN];

void update(int idx, long long val) {
    while (idx <= m){
        bit[idx] += val;
        idx += idx & -idx;
    }
}

long long query(int idx) {
    long long sum = 0;
    while (idx > 0){
        sum += bit[idx];
        idx -= idx & -idx;
    }
    return sum;
}

void range_update(int l, int r, long long val) {
    if (l <= r) {
        update(l, val);
        update(r + 1, -val);
    } else {
        update(l, val);
        update(m + 1, -val);
        update(1, val);
        update(r + 1, -val);
    }
}

void solve(int L, int R, vector<int>& participants) {
    if (participants.empty()) return;

    if (L == R) {
        for (int id : participants) {
            ans[id] = L;
        }
        return;
    }

    int mid = (L + R) / 2;

    for (int i = L; i <= mid; i++) {
        range_update(meteors[i].l, meteors[i].r, meteors[i].a);
    }

    vector<int> left_group, right_group;

    for (int id : participants) {
        long long collected = 0;
        for (int sector : owner[id]) {
            collected += query(sector);
            if (collected >= req[id]) break;
        }

        if (collected >= req[id]) {
            left_group.push_back(id);
        } else {
            req[id] -= collected;
            right_group.push_back(id);
        }
    }

    for (int i = L; i <= mid; i++) {
        range_update(meteors[i].l, meteors[i].r, -meteors[i].a);
    }

    solve(L, mid, left_group);
    solve(mid + 1, R, right_group);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int o;
        cin >> o;
        owner[o].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        cin >> req[i];
    }

    int k_events;
    cin >> k_events;

    for (int i = 1; i <= k_events; i++) {
        cin >> meteors[i].l >> meteors[i].r >> meteors[i].a;
    }

    vector<int> participants;
    for (int i = 1; i <= n; i++) {
        participants.push_back(i);
    }
   
    solve(1, k_events + 1, participants);

    for (int i = 1; i <= n; i++) {
        if (ans[i] <= k_events) {
            cout << ans[i] << endl;
        } else {
            cout << "NIE" << endl;
        }
    }

    return 0;
}