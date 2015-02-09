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
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

const int maxn = 1e5 + 5;

int d[maxn];

void solve(int test_number)
{
    int n, k, x, y;
    scanf("%d%d%d%d", &n, &k, &x, &y);
    forn(j, n)
        scanf("%d", &d[j]);
    sort(d, d + n);
    int p1 = lower_bound(d, d + n, x) - d;
    int C = n - p1;
    if (C < 2)
    {
        printf("NO\n");
        return;
    }
    int p2 = lower_bound(d, d + n, y) - d;
    int D = n - p2;
    if (x <= y)
    {
        D = min(D, C - 2);          
    }
    else D -= 2;
    if (D >= k)
    {
        printf("YES\n");
    }
    else printf("NO\n");
}
