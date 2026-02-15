#include <bits/stdc++.h>
using namespace std;
// This code is almost the same we just avoid recursion
// in order to avoid possible stack overflow

struct NodeInfo {
    int maxG[3];
    int minG[3];
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin>>s;

    vector<NodeInfo> st;
    st.reserve(s.size());

    for (int pos = (int)s.size() - 1; pos >= 0; pos--) {
        char c = s[pos];
        if (c == '0') {
            NodeInfo leaf;
            leaf.maxG[0] = 0; leaf.maxG[1] = 1; leaf.maxG[2] = 0;
            leaf.minG[0] = 0; leaf.minG[1] = 1; leaf.minG[2] = 0;
            st.push_back(leaf);
        } else if (c == '1') {
            NodeInfo child = st.back();
            st.pop_back();
            NodeInfo cur;
            for (int i = 0; i < 3; ++i) {
                int mx = INT_MIN;
                int mn = INT_MAX;
                for (int j = 0; j < 3; ++j) {
                    if (j == i) continue;
                    mx = max(mx, (i == 1) + child.maxG[j]);
                    mn = min(mn, (i == 1) + child.minG[j]);
                }
                cur.maxG[i] = mx;
                cur.minG[i] = mn;
            }
            st.push_back(cur);
        } else { 
            NodeInfo left = st.back(); st.pop_back();
            NodeInfo right = st.back(); st.pop_back();
            NodeInfo cur;
            for (int i = 0; i < 3; ++i) {
                int mx = INT_MIN;
                int mn = INT_MAX;
                for (int j = 0; j < 3; ++j) {
                    if (j == i) continue;
                    for (int k = 0; k < 3; ++k) {
                        if (k == i) continue;
                        if (k == j) continue;
                        mx = max(mx, (i == 1) + left.maxG[j] + right.maxG[k]);
                        mn = min(mn, (i == 1) + left.minG[j] + right.minG[k]);
                    }
                }
                cur.maxG[i] = mx;
                cur.minG[i] = mn;
            }
            st.push_back(cur);
        }
    }

    NodeInfo resultInfo = st.back();
    int max_ = max(max(resultInfo.maxG[0], resultInfo.maxG[1]), resultInfo.maxG[2]);
    int min_ = min(min(resultInfo.minG[0], resultInfo.minG[1]), resultInfo.minG[2]);
    
    string res = to_string(max_) + " " + to_string(min_);
    cout<<res<<endl;
    return 0;
}

