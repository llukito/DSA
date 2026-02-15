#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;      
    int priority;
    int size;
    Node *left, *right;

    Node(int k) : key(k), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

int getSize(Node* t) {
    return t ? t->size : 0;
}

void updateSize(Node* t) {
    if (t) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
    }
}

void split_by_size(Node* t, int k, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    int leftSize = getSize(t->left);

    if (leftSize < k) {
        split_by_size(t->right, k - leftSize - 1, t->right, r);
        l = t;
    } else {
        split_by_size(t->left, k, l, t->left);
        r = t;
    }
    updateSize(t);
}

void split_by_key(Node* t, int split_key, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }

    if (t->key < split_key) {
        split_by_key(t->right, split_key, t->right, r);
        l = t;
    } else {
        split_by_key(t->left, split_key, l, t->left);
        r = t;
    }
    updateSize(t);
}

Node* unite(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;

    if (l->priority > r->priority) {
        Node *r_left, *r_right;
        split_by_key(r, l->key, r_left, r_right);
        l->left = unite(l->left, r_left);
        l->right = unite(l->right, r_right);
        updateSize(l);
        return l;
    } else {
        Node *l_left, *l_right;
        split_by_key(l, r->key, l_left, l_right);
        r->left = unite(l_left, r->left);
        r->right = unite(l_right, r->right);
        updateSize(r);
        return r;
    }
}

void inorder_traversal(Node* t, char c, string& s) {
    if (!t) {
        return;
    }
    inorder_traversal(t->left, c, s);
    s[t->key] = c; 
    inorder_traversal(t->right, c, s);
}

int n, m;
string s;
char x, y;
int p;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr)); // make random output unique ones

    cin >> n >> m;
    cin >> s;

    vector<Node*> treaps(5, nullptr); // 5 treaps for each colour

    for (int i = 0; i < n; i++) {
        int color_idx = s[i] - 'a';
        treaps[color_idx] = unite(treaps[color_idx], new Node(i));
    }

    for (int i = 0; i < m; i++) {
        cin >> p;
        cin >> x >> y;
        if (x == y) continue;

        int x_idx = x - 'a';
        int y_idx = y - 'a';

        Node *to_move = nullptr;
        Node *remaining_a = nullptr;

        int x_size = getSize(treaps[x_idx]);
        split_by_size(treaps[x_idx], min(p, x_size), to_move, remaining_a);

        treaps[x_idx] = remaining_a;

        treaps[y_idx] = unite(to_move, treaps[y_idx]);
    }

    for (int i = 0; i < 5; i++) {
        if (treaps[i]) {
            inorder_traversal(treaps[i], 'a' + i, s);
        }
    }

    cout << s << endl;
    return 0;
}
