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

const int maxn = 2005;

int a[maxn];
int dp[maxn][maxn];

void solve(int test_number)
{
    int n;
    scanf("%d", &n);
    forn(j, n)
        scanf("%d", &a[j]);
    sort(a, a + n);
    for (int first = n - 1; first >= 0; first--)
        for (int second = first + 1; second <= n - 1; second++)
        {
            int next = 2 * a[second] - a[first];
            int tmp = lower_bound(a, a + n, next) - a;
            if (tmp == n || a[tmp] != next)
                dp[first][second] = 2;
            else dp[first][second] = dp[second][tmp] + 1;
        }
    int answer = 1;
    forn(first, n)
        fore(second, first + 1, n - 1)
            answer = max(answer, dp[first][second]);
    printf("%d\n", answer);
}
