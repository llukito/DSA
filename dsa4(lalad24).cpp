#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    int n;
    vector<int> parent;
    vector<int> rankv;
    vector<char> covered;

    DisjointSet(int size = 0) { init(size); }

    void init(int size) {
        n = size;
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rankv.assign(n, 0);
        covered.assign(n, 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rankv[a] < rankv[b]) swap(a,b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        covered[a] = covered[a] | covered[b];
    }

    void markCovered(int x) {
        covered[find(x)] = 1;
    }

    bool isCovered(int x) {
        return covered[find(x)] != 0;
    }
};

struct Cell {
    int height;
    bool isCity;
    int idx;
    int r, c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    cin >> rows >> cols;

    vector<int> raw(rows * cols);
    for (int i = 0; i < rows * cols; i++) cin >> raw[i];

    vector<Cell> cells;
    cells.reserve(rows * cols);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int x = raw[r * cols + c];
            cells.push_back({ abs(x), x > 0, r * cols + c, r, c });
        }
    }

    sort(cells.begin(), cells.end(),
         [](const Cell &a, const Cell &b){ return a.height < b.height; });

    DisjointSet dsu(rows * cols);
    vector<char> active(rows * cols, 0);
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    long long pumps = 0;

    for (int i = 0; i < cells.size(); ) {
        int curH = cells[i].height;
        int j = i;
        while (j < cells.size() && cells[j].height == curH) j++;

        for (int k = i; k < j; k++) {
            int r = cells[k].r;
            int c = cells[k].c;
            int id = cells[k].idx;
            active[id] = 1;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                int nid = nr * cols + nc;
                if (active[nid]) dsu.unite(id, nid);
            }
        }

        for (int k = i; k < j; k++) {
            if (!cells[k].isCity) continue;
            int id = cells[k].idx;
            int root = dsu.find(id);
            if (!dsu.covered[root]) {
                pumps++;
                dsu.covered[root] = 1;
            }
        }

        i = j;
    }

    cout << pumps << endl;
    return 0;
}