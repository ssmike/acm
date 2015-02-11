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
    //srand(time(0));
    int n = 1;
    forn(i, n)
        solve(i);
}

#define MAXN 3000

vector<int> G[MAXN];
int n, r;
bool special[MAXN];
bool mark[MAXN];

lint ans[MAXN][2 * MAXN];
lint anssum[MAXN][2 * MAXN];

#define MOD 1000000007

lint getsum(int v, int l, int r) {
    //if (l > r) return 0;
    return (anssum[v][r+MAXN] - anssum[v][l+MAXN-1] + MOD) % MOD;
}

void calc_sum(int v) {
    anssum[v][0] = 0;
    for (int i = 1; i < 2 * MAXN; i++)
        anssum[v][i] = (anssum[v][i - 1] + ans[v][i]) % MOD;
}

void add(int v, int d, lint val) {
    ans[v][MAXN + d] = (ans[v][MAXN + d] + val) % MOD;
}

void calc(int v) {
    if (mark[v]) return;
    mark[v] = true;
    vi nh;
    for (int i = 0; i < (int)G[v].size(); i++) {
        if (!mark[G[v][i]]) nh.pb(G[v][i]);
        calc(G[v][i]);
    }
    //leaf
    if (nh.empty()) {
        if (special[v]) {
            add(v, -1, 1);
        } else {
            add(v, 0, 1);
        }
        add(v, r, 1);
        calc_sum(v);
        return;
    }
    //v is not covered | out = 0
    if (!special[v]) {
        lint cur = 1;
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], 0, 0)) % MOD;
        }
        add(v, 0, cur);
    }
    // x == 0 | v is covered
    {
        lint cur = 1;
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], 0, 1));
        }
        add(v, 0, cur);
        cur = 1;
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], 0, 0)) % MOD;
        }
        add(v, 0, MOD - cur);
    }
    //out | v is covered
    for (int x = 1; x < r; x++) {
        lint cur = 1;
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], -x, x)) % MOD;
        }
        add(v, x, MOD - cur);
        cur = 1;
        for (int i = (int)nh.size() - 1; i >= 0; i--) {
            cur = (cur * getsum(nh[i], -x, x + 1)) % MOD;
        }
        add(v, x, cur);
    }
    //in
    for (int x = -r; x < -1; x++) {
        lint cur = 1;
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], x + 2, - x - 1)) % MOD;
        }
        add(v, x, MOD - cur);
        cur = 1;
        for (int i = (int)nh.size() - 1; i >= 0; i--) {
            cur = (cur * getsum(nh[i], x + 1, - x - 1)) % MOD;
        }
        add(v, x, cur);
    }
    // -1
    if (special[v]) {
        lint cur = 1;
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], 0, 0)) % MOD;
        }
        add(v, -1, cur);
    }
    {
        lint cur = 1; 
        for (int i = 0; i < (int)nh.size(); i++) {
            cur = (cur * getsum(nh[i], -r, r)) % MOD;
        }
        add(v, r, cur);
    }
    calc_sum(v);
}

bool chosen[MAXN];

int mindist(int v) {
    if (chosen[v]) return 0;
    if (mark[v]) return 1e9;
    mark[v] = true;
    int ans = 1e9;
    for (int i = 0; i < (int)G[v].size(); i++) {
        ans = min(ans, 1 + mindist(G[v][i]));
    }
    return ans;
}

int count(int n) {
    int ans = 0;
    for (int d = 0; d < (1 << n); d++) {
        bool flag = true;
        fill(chosen, chosen + n, false);
        for (int i = 0; i < n; i++)
            if ((1 << i) & d)
                chosen[i] = true;
        for (int i = 0; i < n; i++) {
            fill(mark, mark + n, false);
            if (special[i] && mindist(i) > r)
                flag = false;
        }
        ans += flag;
    }
    return ans;
}

void solve(int test_number)
{
    int str = -1;
    memset(special, 0, sizeof special);
    memset(mark, 0, sizeof mark);
    memset(ans, 0, sizeof ans);
    for (int i = 0; i < MAXN; i++)
        G[i].clear();
    int m;
    //n = 4; m = rand()%3; r = rand()%3;
    cin >> n >> m >> r;
    for (int i = 0; i < m; i++) {
        int t; cin >> t;
        //int t = rand() % n + 1;
        special[t - 1] = true;
        str = t - 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        //int a, b; a = rand() % (i + 1) + 1; b = i + 2;
        G[a - 1].pb(b - 1);
        G[b - 1].pb(a - 1);
    }
    calc(max(str, 0));
    cout << getsum(max(str, 0), 0, r);
    /*if (getsum(max(str, 0), 0, r) != count(n)) {
        cout << "--" << endl << getsum(max(str, 0), 0, r) << "!=" << count(n) << endl
            << n << " " << m << " " << r << endl;
        for (int i = 0; i < n; i++)
            if (special[i]) cout << i + 1 << " ";
        cout << "\nedges "<< endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)G[i].size(); j++)
                cout << G[i][j] + 1 << " ";
            cout << endl;
        }
        exit(1);
    }*/
    //assert(getsum(max(str, 0), 0, r) == count(n));
}
