#include <cstdio>
#include <cstring>
#include <ctime>
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

#define STRESS true

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
    srand(time(0));
    int n = STRESS ? 100000 : 1;
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
int priority[MAXN];
int leaves[MAXN];
int parent[MAXN];

inline vector<int> findLeaves(int v) {
    vector<int> ans;
    for (int i = 0; i < G[v].size(); i++) {
        if (active[G[v][i]] && deg[G[v][i]] == 1)
            ans.push_back(G[v][i]);
    }
    return ans;       
}

inline int getParent(int v) {
    if (parent[v] == -1 || !active[parent[v]]) {
        for (int i = 0; i < G[v].size(); i++)
            if (active[G[v][i]])
                return G[v][i];
        assert(false);  
    }
    return parent[v];
}

inline int getpriority(int v) {
    return priority[v];
}


set<pair<int, int> > qq;

inline void recalcpriority(int v) {
    if (deg[v] != 1) return;
    if (priority[v] != deg[getParent(v)] - leaves[getParent(v)]) {
        qq.erase(mp(priority[v], v));
        qq.insert(mp(priority[v] = deg[getParent(v)] - leaves[getParent(v)], v));
    }
}

vector<vector<int>> slices;
int isolated[MAXN];
int isf, isl;

int op[MAXN];

inline void update(int v) {
    if (!active[v]) return;
    if (deg[v] == 1)
        recalcpriority(v);
    vector<int> ls = findLeaves(v);
    for (int i = 0; i < (int)ls.size(); i++)
        recalcpriority(G[v][i]);
}

inline void disable(int v) {
    if (deg[v] == 1)
        leaves[getParent(v)]--;
    active[v] = false;
    for (int i = 0; i < G[v].size(); i++) {
        deg[G[v][i]]--;
        if (active[G[v][i]] && deg[G[v][i]] == 1) {
            leaves[getParent(G[v][i])]++;
            leafqueue[ql++] = G[v][i];
        }
        if (active[G[v][i]] && deg[G[v][i]] == 0) {
            isolated[isl++] = G[v][i];
        }
    }
    for (int i = 0; i < G[v].size(); i++) {
        if (active[G[v][i]])
            update(G[v][i]);
        if (active[G[v][i]] && deg[G[v][i]] == 1) {
            update(getParent(G[v][i]));
        }
    }
}

int color[MAXN];

inline bool check(int v, int col) {
    for (int i = 0; i < G[v].size(); i++) {
        if (color[G[v][i]] == col) return false;
    }
    return true;
}

void solve(int test_number)
{
    memset(op, -1, sizeof op);
    memset(parent, -1, sizeof parent);
    memset(priority, -1, sizeof priority);
    memset(leaves, 0, sizeof leaves);
    qf = ql = 0;
    isf = isl = 0;
    int n; 
    if (STRESS) n = 42;
    else scanf("%d", &n);   
    slices.clear();
    memset(deg, 0, sizeof deg);
    for (int i = 0; i < n; i++)
        G[i].clear();
    for (int i = 1; i < n; i++) {
        if (!STRESS) {
            scanf("%d", p + i);
            p[i]--;
        } else {
            int c = 0;
            for (int j = max(0, i - 20); j < i; j++) {
                if (deg[j] < 4) c++;
            }
            c = rand()%c + 1;
            for (int j = max(0, i - 20); j < i; j++) {
                if (deg[j] < 4) c--;
                if (c == 0) {
                    p[i] = j;
                    break;
                }
            }
        }
        G[p[i]].push_back(i);
        G[i].push_back(p[i]);
        deg[i]++;
        deg[p[i]]++;
    }
    qq.clear();
    clock_t tstart = clock();
    if (STRESS) {
        for (int i = 1; i < n; i++)
            fprintf(stderr, "%2d ", p[i] + 1);
        for (int i = 0; i < n; i++)
            assert(deg[i] <= 4);
    }
    fill(active, active + n, true);
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) {
            leaves[getParent(i)]++;
            leafqueue[ql++] = i;
            //int v = getParent(i);
            recalcpriority(i);
        }
    }
    for (int i = 0; i < n - 3; i += 3) {
        while (qf < ql && (!active[leafqueue[qf]] || deg[leafqueue[qf]] != 1)) qf++;
        slices.push_back(vector<int>());
        while (isf < isl && slices.back().size() < 3) {
            while (isf < isl && !active[isolated[isf]]) isf++;
            if (isf < isl) slices.back().push_back(isolated[isf++]);
        }
        int u = -1, v = -1;
        if (slices.back().size() == 0) {
            do {
                assert(!qq.empty());
                int c = qq.begin()->first;
                int vv = qq.begin()->second;
                if (active[vv] && deg[vv] == 1 &&
                        getpriority(vv) == c)
                    u = vv;
                if (u == -1) qq.erase(qq.begin());
            } while (u == -1);
            v = getParent(u);
            slices.back().push_back(v);
            vector<int> ll = findLeaves(v);
            for (int i = 0; i < ll.size() && slices.back().size() < 3; i++)
                slices.back().push_back(ll[i]);
        }
        for (int i = qf; i < ql && slices.back().size() < 3; i++)
           if (active[leafqueue[i]] && deg[leafqueue[i]] == 1 && getParent(leafqueue[i]) != v && 
                   find(slices.back().begin(), slices.back().end(), leafqueue[i]) == slices.back().end())
               slices.back().push_back(leafqueue[i]);
        for (int i = 0; i < slices.back().size(); i++) {
            disable(slices.back()[i]);
        }
    }
    slices.push_back(vector<int>());
    for (int i = 0; i < n; i++)
        if (active[i])
            slices.back().push_back(i);
    memset(color, -1, sizeof color);
    for (int i = ((int)slices.size()) - 1; i >= 0; i--) {
        assert(slices[i].size() == 3);
        for (int m = 0; m < 6; m++) {
            int fs = m / 2;
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
    for (int i = 0; i < n; i++)
        assert(color[i] != -1);
    char C[3] = {'N', 'K', 'P'};
    for (int i = 0; i < n; i++) {
        printf("%c", C[color[i]]);
    }
    if (STRESS) {
        fprintf(stderr, "OK - %ld\n", (clock() - tstart) / CLOCKS_PER_SEC);
    }
}
