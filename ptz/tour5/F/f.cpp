#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>
#include <queue>

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

#define TASKNAME "adsadasd"

void solve(int test_number);

int main() {
    ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

#define MAXN 500100

int p[MAXN];
vector<int> G[MAXN];
int sz[MAXN];
bool vis[MAXN];
bool active[MAXN];
int deg[MAXN];
int leafqueue[MAXN];
int qf, ql;

int getParent(int v) {
    return G[v][0];
}

vector<vector<int>> slices;

void disable(int v) {
    for (int i = 0; i < G[v].size(); i++) {
        deg[G[v][i]]--;
        if (active[G[v][i]] && deg[G[v][i]] == 1) {
            leafqueue[ql++] = G[v][i];
        }
    }
    active[v] = false;
}


vector<int> findLeaves(int v) {
    vector<int> ans;
    for (int i = 0; i < G[v].size(); i++) {
        if (active[G[v][i]] && deg[G[v][i]] == 1)
            ans.push_back(G[v][i]);
    }
    return ans;       
}

int color[MAXN];

bool check(int v, int col) {
    for (int i = 0; i < G[v].size(); i++) {
        if (color[G[v][i]] == col) return false;
    }
    return true;
}

void solve(int test_number)
{
    qf = ql = 0;
    int n; scanf("%d", &n);   
    for (int i = 1; i < n; i++) {
        scanf("%d", p + i);
        p[i]--;
        G[p[i]].push_back(i);
        G[i].push_back(p[i]);
        deg[i]++;
        deg[p[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1)
            leafqueue[ql++] = i;          
    }
    fill(active, active + n, true);
    for (int i = 0; i < n - 3; i += 3) {
        while (qf < ql && !active[leafqueue[qf]]) qf++;
        int u = leafqueue[qf];
        int v = getParent(u);
        slices.push_back(vector<int>());
        slices.back().push_back(u);
        if (deg[v] == 2) {
            slices.back().push_back(v);
        } else {
            vector<int> ll = findLeaves(v);
            while (ll.back() == u) ll.pop_back();
            slices.back().push_back(ll.back());
        }
        for (int i = qf; i < ql && slices.back().size() < 3; i++) {
           if (active[leafqueue[i]] && getParent(leafqueue[i]) != v) {
               slices.back().push_back(leafqueue[i]);
           }
        }
        for (int i = 0; i < slices.back().size(); i++) {
            disable(slices.back()[i]);
        }
    }
    slices.push_back(vector<int>());
    for (int i = 0; i < n; i++) {
        if (active[i])
            slices.back().push_back(i);
    }
    memset(color, -1, sizeof color);
    for (int i = ((int)slices.size()) - 1; i >= 0; i--) {
        assert(slices[i].size() == 3);
        for (int m = 0; m < 6; m++) {
            int fs = m / 3;
            int sc = (fs + 1 + m % 2) % 3;
            int thd = 3 - fs - sc;
            if (check(slices[i][0], fs) &&
                    check(slices[i][1], sc) && 
                    check(slices[i][2], thd)) {
                color[slices[i][0]] = fs;
                color[slices[i][1]] = sc;
                color[slices[i][2]] = thd;
                break;
            }
        }
    }
    char C[3] = {'N', 'K', 'P'};
    for (int i = 0; i < n; i++) {
       // assert(color[i] != -1);
       if (color[i] != -1)
        printf("%c", C[color[i]]);
    }
}
