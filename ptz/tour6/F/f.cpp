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

#define TASKNAME "adsadasd"

void solve(int test_number);

int mind[100000];
int T = 1;
int ts[100000];
int rem[100000];

int getrem(int x) {
    if (ts[x] == T) return rem[x];
    else return -1;
}

void setrem(int x, int r) {
    ts[x] = T;
    rem[x] = r;
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
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    memset(ts, 0, sizeof ts);
    memset(mind, -1, sizeof mind);
    for (int i = 2; i < 100000; i++) {
        if (mind[i] == -1) {
            for (int j = i; j < 100000; j += i) {
                if (mind[j] == -1)
                    mind[j] = i;
            }
        }
    }
    int n;
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

#define MAXN 110
#define MAXM 10100

int n, m;
int perm[MAXN][MAXM];
bool mark[MAXM];

inline bool checkk(int v, int w, int * p, int * q) {
    int cnt = 0, c = v;
    while (v != c || cnt == 0) {
        if (w != q[c])
            return false;
        cnt++;
        c = p[c];
        w = p[w];
    }
    return true;
}

inline bool factor(int x, int k) {
    while (x > 1) {
        int m = mind[x];
        while (x % m == 0) {
            if (getrem(m) != -1 && getrem(m) != k%m)
                return false;
            setrem(m, k % m);
            m = m * mind[x];
        }
        x /= m / mind[x];
    }
    return true;
}


pii K[MAXN][MAXM];
bool first[MAXN];
int csize[MAXN];
int shift[MAXM];

inline int md(int x, int m) {
    if (x > m) return m;
    else return x;
}

inline bool check(int i, int j) {
    T++;
    for (int k = 0; k < m; k++) {
        if (K[i][k].first != K[j][k].first)
            return false;
    }
    for (int k = 0; k < m; k++) {
        if (first[k]) {
            shift[k] = K[i][perm[j][k]].second;
            if (!factor(csize[k], shift[k])) return false;
        }
        if (K[i][perm[j][k]].second != md(K[i][k].second + shift[K[i][k].first], csize[K[i][k].first]))
            return false;
    }
    return true;
}

void solve(int test_number) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &perm[i][j]);
            perm[i][j]--;
        }
    }
    for (int i = 0; i < n; i++) {
        fill(mark, mark + m, false);
        fill(first, first + m, false);
        for (int j = 0; j < m; j++) {
            if (!mark[j]) {
                first[j] = true;
                int cnt = 0;
                for (int k = j; (k != j || cnt == 0); cnt++, k = perm[i][k]) {
                    K[i][k] = mp(j, cnt);
                    mark[k] = true;
                }
                csize[j] = cnt;
            }
        }
        int ans = 0;
        for (int j = 0; j < i; j++) {
            ans += check(i, j);// && check(j, i);
        }
        printf("%d\n", ans);
    }
}
