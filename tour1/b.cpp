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

using namespace std;


#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
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
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

int n, m;
vector<int> g[100];
vector<li> b[100][2][2];
vector<int> p1, p2;
bool used[100];

void dfs(int v, int color) {
    if (color == 0)
        p1.pb(v);
    else
        p2.pb(v);
    used[v] = true;

    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i];
        if (!used[to])
            dfs(to, 1 - color);
    }
}

li MOD = 1000000007;

void solve(int test_number)
{
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, b00, b01, b10, b11;
        cin >> u >> v >> b00 >> b01 >> b10 >> b11;
        u--, v--;
        g[u].pb(v);
        b[u][0][0].pb(b00), b[u][0][1].pb(b01), b[u][1][0].pb(b10), b[u][1][1].pb(b11);
        g[v].pb(u);
        b[v][0][0].pb(b00), b[v][0][1].pb(b10), b[v][1][0].pb(b01), b[v][1][1].pb(b11);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i, 0);
    if (p1.size() > p2.size())
        p1.swap(p2);
    map<int, int> q;
    for (int i = 0; i < (int)p1.size(); i++)
        q[p1[i]] = i;
    li res = 0;
    for (int msk = 0; msk < (1 << p1.size()); msk++) {
        li cur = 1;
        for (int i = 0; i < (int)p2.size(); i++) {
            li sum = 0;
            for (int col1 = 0; col1 <= 1; col1++) {
                li cur1 = 1;
                for (int j = 0; j < (int)g[p2[i]].size(); j++) {
                    int to = g[p2[i]][j];
                    int to_ind = q[to];
                    int col2;
                    if ((msk & (1 << to_ind)) == 0)
                        col2 = 0;
                    else
                        col2 = 1;
                    cur1 = (cur1 * b[p2[i]][col1][col2][j]) % MOD;
                }
                sum = (sum + cur1) % MOD;
            }
            cur = (cur * sum) % MOD;
        }
        res = (cur + res) % MOD;
    }
    cout << res << endl;
}
