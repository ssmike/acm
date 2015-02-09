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
    while (true)
        solve(1);
}

int n, m;
char c[2010][2010];
int r[2010][2010];
int d[2010][2010];
int jr[2010][2010];
int jd[2010][2010];
int pr_row[2010][2010];
int pr_col[2010][2010];
int ans[2010][2010];
int res;
int cc[2010][2010];

void solve() {
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++) {
            r[i][j] = d[i][j] = -1;
            jd[i][j] = jr[i][j] = -INF;
            pr_row[i][j] = 0;
            pr_col[i][j] = 0;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int add = (c[i][j] == '#' ? 1 : 0);
            pr_row[i][j] = pr_row[i][j - 1] + add;
            pr_col[i][j] = pr_col[i - 1][j] + add;
        }
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--) {
            r[i][j] = r[i][j + 1];
            d[i][j] = d[i + 1][j];
            if (r[i][j] == -1 && c[i][j] == '#')
                r[i][j] = j;
            if (d[i][j] == -1 && c[i][j] == '#')
                d[i][j] = i;
        }
    /*
    cout << "r" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cout << d[i][j] << ' ';
        cout << endl;
    }
    */
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--) {
            if (c[i][j] == '.')
                continue;
            // jr
            if (r[i][j] == j) {
                jr[i][j] = 0;
            } else {
                int cur = jd[i][r[i][j]];
                if (cur == 0) {
                    if (r[i][j] - j == 1 || 
                        pr_row[i + 1][r[i][j]] - pr_row[i + 1][j] == 0)
                        cur = 0;
                    else
                        cur = 1;
                } else {
                    cur++;
                }
                jr[i][j] = cur;
            }
            // jd
            if (d[i][j] == i) {
                jd[i][j] = 0;
            } else {
                int cur = jr[i][d[i][j]];
                if (cur == 0) {
                    if (d[i][j] - i == 1 || pr_col[d[i][j]][j] - pr_col[i][j] == 0)
                        cur = 0;
                    else
                        cur = 1;
                } else {
                    cur++;
                }
                jd[i][j] = cur;
            }
            ans[i][j] = max(jr[i][j], jd[i][j]);
            res = max(res, ans[i][j]);
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 1;j  <= m; j++) 
            cout << jr[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1;j  <= m; j++) 
            cout << jd[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void rotate() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cc[j][i] = c[i][j];
    swap(n, m);
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            c[i][j] = '.';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)    
            c[i][j] = cc[i][j];
}

void solve(int test_number)
{
    res = 0;
    cin >> n >> m;
    if (n * n + m * m == 0)
        exit(0);
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            c[i][j] = '.';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];
    solve();
    rotate();
    solve();
    cout << res << endl;;
}
