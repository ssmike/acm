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
#define pii pair<i64, i64>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

#define TASKNAME "jordan"

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

const int maxn = 10000;
const i64 inf = 1e18;

vi list;
pii dp[maxn];
i64 L[maxn];
i64 R[maxn];
i64 sum[maxn];

void solve(int test_number)
{
    int n;
    scanf("%d", &n);
    forn(i, n)
    {
        scanf("%lld%lld%lld", &L[i], &R[i], &sum[i]);
        list.pb(L[i]);
        list.pb(R[i]);
        list.pb(L[i] - 1);
    }
    sort(list.begin(), list.end());
    list.resize(unique(list.begin(), list.end()) - list.begin());
    /*forn(i, list.size())
        printf("%d ", list[i]);
    printf("\n");*/
    forn(j, list.size())
        dp[j].se = inf;
    forn(i, n)
    {
        forn(j, list.size())
            if (list[j] >= L[i] && list[j] <= R[i])
                dp[j].se = min(dp[j].se, sum[i]);
    }
    dp[0] = mp(0, 0);
    fore(i, 1, list.size() - 1)
    {
        int cur = list[i];
        dp[i].fi = dp[i - 1].fi;
        //dp[i].se = inf;
        forn(j, n)
        {
            if (R[j] == cur)
            {
                int l = L[j] - 1;
                int pos = lower_bound(list.begin(), list.end(), l) - list.begin();
                i64 new_lower = dp[pos].fi + sum[j];
                i64 new_upper = dp[pos].se + sum[j];
                //if (pos != i - 1)
                //    new_upper = min(new_upper, dp[pos + 1].se + sum[j]);
                dp[i].fi = max(dp[i].fi, new_lower);
                dp[i].se = min(dp[i].se, new_upper);
            }
        }
        //printf("dp %d = %lld %lld\n", i, dp[i].fi, dp[i].se);
    }
    pii ans = dp[list.size() - 1];
    if (ans.fi > ans.se)
        printf("-1 -1\n");
    else printf("%lld %lld\n", ans.fi, ans.se);
}
