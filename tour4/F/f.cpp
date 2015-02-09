#include <cstdio>
#include <deque>
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

#define TASKNAME "fulkerson"

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
    freopen(TASKNAME ".in", "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

#define MAXN 350010

vector<int> G[MAXN];
int deg[MAXN];
int used[MAXN];
int layer[MAXN];
int lcount[MAXN];
int dmin[MAXN];
int ans[MAXN];

int dans[MAXN];

void ssolve(int n) {
    //for ()
}

void solve(int test_number)
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
        deg[a - 1]++;
        deg[b - 1]++;
    }
    deque<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1)
            q.push_back(i);
    }
    int maxlayer = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        lcount[layer[v]]++;
        maxlayer = max(maxlayer, layer[v]);
        for (int i = 0; i < (int)G[v].size(); i++) {
            deg[G[v][i]]--;
            if (deg[G[v][i]] == 1 && !used[G[v][i]]) {
                used[G[v][i]] = true;
                q.push_back(G[v][i]);
                layer[G[v][i]] = layer[v] + 1;
            }
        }
    }
    dmin[0] = n;
    for (int k = 1; k < n; k++) {
        int i;
        int cans = 0;
        for (i = k; i <= maxlayer; i += 2 * k) {
            cans += lcount[i];
        }
        if (i - maxlayer <= k || maxlayer < k) {
            cans += 1;
        }
        dmin[k] = cans;
    }

    int cans = 0;
    for (int i = n; i >= 1; i--) {
         while (dmin[cans] > i) cans++;
         ans[i] = cans;
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}
