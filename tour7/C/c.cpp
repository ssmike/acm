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
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

#define TASKNAME "heap"

void solve(int test_number);

const li MOD = 1000000007;

li c[3010][3010];

void init() {
    for (int i = 0; i <= 3000; i++)
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) 
                c[i][j] = 1;
            else
                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
}

li a[3010];
li n, d;

bool heap() {
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < d; j++) {
            int to = (i - 1) * d + j + 2;
            if (to > n)
                continue;
            if (a[to] < a[i])
                flag = false;
        }
    }
    return flag;
}

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
#endif
    /*int nn = 120;
    cin >> nn;
    init();
    forn(i, nn)
        solve(i);*/
    int nn = 1200;
    init();
    n = 30, d = 6;
    for (int i = 1; i <= n; i++)
        a[i] = i;
    forn(i, nn) {
        solve(i);
        do {
            if (!next_permutation(a + 1, a + n + 1))
                break;
        } while (!heap());
    }
}

li cnt[100100];
li sz[100100];
li p[10010];

void dfs(int v, int n) {
    if (v > n) {
        return;
    }
    sz[v] = 1;
    for (int i = 0; i < d; i++) {
        int to = (v - 1) * d + i + 2;
        dfs(to, n);
        if (to > n)
            continue;
        sz[v] += sz[to];
    }
}

int get_pred(int v) {
    if (v == 1)
        return 0;
    else
        return (v - 2) / d + 1;
}

lint modpow(lint x, int p) {
    lint r = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            x = (x * x) % MOD;
            p /= 2;
        } else {
            r = (r * x) % MOD;
            p--;
        }
    }
    return r;
}

lint inv(lint x) {
    return modpow(x, MOD - 2);
}

li g[3010];
li q[3010];
pii tmp[3010];
bool used[3010];
int hcnt[3010];
int usum[3010];

int cnk(int n, int k) {
    if (k > n || n < 0) return 0;
    else return c[n][k];
}

li x[3010];

int naive() {
    for (int i = 1; i <= n; i++)
        x[i] = i;
    int res = 0;
    while (true) {
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < d; j++) {
                int to = (i - 1) * d + j + 2;
                if (to > n)
                    continue;
                if (x[to] < x[i])
                    flag = false;
            }
        }
        if (flag)
            res++;
        flag = true;
        for (int i = 1; i <= n; i++)
            if (a[i] != x[i]) {
                flag = false;
            }
        if (flag)
            return res;
        next_permutation(x + 1, x + n + 1);
    }
}

void solve(int test_number)
{
    
    /*cin >> n >> d;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    */
    cnt[0] = 1;
    cnt[1] = 1;
    for (li i = 2; i <= n; i++) {
        dfs(1, i);
        cnt[i] = 1;
        int rem = i - 1;
        for (int j = 2; j <= min(d + 1, i); j++) {
            cnt[i] = (cnt[i] * (c[rem][sz[j]] * cnt[sz[j]]) % MOD) % MOD;
            rem -= sz[j];
        }
    }
    dfs(1, n);
    li l = 0, r = 1;
    q[0] = 1;
    fill(used, used + n + 1, false);
    lint ans = 0;
    for (int i = 1; i <= n; i++) {
        fill(hcnt, hcnt + n + 1, 0);
        int cur = q[l];
        li to_mult = 1;
        fore(j, l, r - 1) {
            to_mult = (to_mult * cnt[sz[q[j]]]) % MOD;
            if (j != l)
                tmp[j - l] = mp(a[get_pred(q[j])], q[j]);
        }
        sort(tmp + 1, tmp + r - l);
        int first = 1;
        int delta = 0;
        lint cpr = 1;
        usum[0] = 0;
        fore(i, 1, n) {
            usum[i] = usum[i - 1] + (!used[i]); 
        }
        for (int j = r - 1 - l; j > 0; j--) {
            int v = tmp[j].second;
            int w = tmp[j].first;
            cpr = (cpr * cnk(n - (i - 1) - usum[w] - delta, sz[v])) % MOD;
            delta += sz[v];
        }
        for(int j = 1; j <= n; j++) { 
            if (!used[j] && (cur == 1 || j > a[get_pred(cur)])) {
                while (first < r - l && tmp[first].first <= j) {
                    int v = tmp[first].second;
                    int w = tmp[first].first;
                    delta -= sz[v];
                    cpr = ((inv(cnk(n - (i - 1) - usum[w] - delta, sz[v])) *
                             cnk(n - (i - 1) - usum[w] - delta - sz[cur], sz[v]))%MOD * cpr) % MOD;
                    first++;
                }
                hcnt[j] = ((to_mult * cpr)%MOD * cnk(n - usum[j] + 1 - i - delta, sz[cur] - 1))%MOD;
            }
        }
        forn(j, a[i]) {
            ans = (ans + hcnt[j]) % MOD;
        }
        l++;
        used[a[cur]] = true;
        forn(j, d) {
            int v = (cur - 1) * d + j + 2;
            if (v > n)
                break;
            q[r++] = (cur - 1) * d + j + 2;
        }
    }
    int naive_res = naive();
    cout << endl;
    cout << n << ' ' << d << endl;
    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << endl;
    cout << (ans + 1) % MOD << '\n';
    cout << naive_res << endl;
    assert(naive_res == ans + 1);
}
