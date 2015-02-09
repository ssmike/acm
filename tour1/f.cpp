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
#define lint unsigned long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

#define TASKNAME "adsadasd"

void solve(int test_number);

#define MAXN ((int)5e6+5)
#define MAXM 11
#define MOD ((lint)(1e9 + 7))

lint CNK[MAXM][MAXM];

int main() {
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("inp", "r", stdin);
 //   freopen("outp", "w", stdout);
#else
#endif
    forn(i, 11)
        fore (j, 0, i) {
            if (j == 0) CNK[i][j] = 1;
            else if (i == j) CNK[i][j] = 1;
            else {
                CNK[i][j] = CNK[i - 1][j - 1] + CNK[i - 1][j];
            }
        }
    int n = 1;
    forn(i, n)
        solve(i);
}

char a[MAXN];
int lim[MAXN * 2];
int d[2][MAXN][MAXM];
int n;


inline lint md(lint x) {
    return (x >= MOD) ? (x - MOD) : x;
}

inline lint get(int t, int x, int k) {
    if (x > n) return k == 0;
    else return d[t][x][k];
}

inline lint get(int x, int k) {
    if (x > n) return k == 0;
    else return md(d[0][x][k] + d[1][x][k]);
}

inline lint cnk(int n, int k) {
    return CNK[n][k] % MOD;
}


void solve(int test_number) {
    int m; scanf("%d%d\n", &n, &m);
    gets(a);
    d[0][n + 1][0] = 1;
    fill(lim, lim + MAXN, 1);
    for (int i = n; i >= 1; i--) {
        //lim[i] = m;
        //if (2 * i <= n && a[i - 1] == '0')
        lim[i] = min(lim[2 * i] + lim[2 * i + 1] + 1, m);
        for (int k = 1; k <= lim[i]; k++) {
            if (a[i - 1] == '0') {
                lint tmp = 0;
                for (int j = 0; j <= k - 1; j++) {
                    tmp = (tmp + get(0, 2 * i, j) * get(0, 2 * i + 1, k - 1 - j));
                }
                d[1][i][k] = tmp % MOD;
            }
            lint tmp = 0;
            for (int j = 0; j <= k; j++) {
                tmp = (tmp + get(2 * i, j) * get(2 * i + 1, k - j));
            }
            d[0][i][k] = tmp % MOD;
        }
        d[0][i][0] = 1;
    }
    lint ans = 0;
    for (int i = 1; i <= m; i++) {
        ans = (ans + cnk((m - i) + (i - 1), i - 1) * get(1, i)) % MOD;
    }
    cout << ans;
}
