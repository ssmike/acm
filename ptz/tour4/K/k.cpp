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

#define TASKNAME "kolmogorov"

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
     freopen(TASKNAME ".in", "r", stdin);
     freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

#define ld long double

const int maxn = 1e5 + 5;

const ld eps = 1.0e-7;
const ld inf = 1e18;

typedef pair <ld, int> mypair;

vi edges[maxn];
set <mypair> order;
ld sum[maxn];
int cnt[maxn];
ld dp[maxn];
ld wait_time[maxn];
bool done[maxn];

void solve(int test_number)
{
    int n, m;
    scanf("%d%d", &n, &m);
    forn(j, m)
    {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        edges[t1].pb(t2);
        edges[t2].pb(t1);
    }
    fore(j, 1, m)
        wait_time[j] = (ld)m / j;
    fore(j, 1, n - 1)
        dp[j] = inf;
    dp[n] = 0;
    order.insert(mp(0, n));
    while(!order.empty())
    {
        mypair p = *order.begin();
        int v = p.se;
        order.erase(order.begin());

        if (abs(dp[v] - p.fi) > eps)
            continue;
        assert(!done[v]);
        done[v] = true;
        forn(j, edges[v].size())
        {
            int u = edges[v][j];
            sum[u] += dp[v];
            cnt[u]++;
            ld nnew = (sum[u] / cnt[u]) + wait_time[cnt[u]];
            //printf("u = %d cnt[u] = %d sum[u] = %.10Lf nnew = %.10Lf dp[u] = %.10Lf\n", u, cnt[u], sum[u], nnew, dp[u]);

            if (dp[u] > eps + nnew)
            {
                dp[u] = nnew;
                order.insert(mp(dp[u], u));
                assert(!done[u]);
            }
        }
    }
    fore(j, 1, n)
        assert(done[j]);
    printf("%.10lf\n", (double)dp[1]);
}
