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
    int n = 1;
    forn(i, n)
        solve(i);
}

const int maxk = 105;
const int maxn = 20005;

pii tree[maxk][maxn * 4];
int dp[maxn][maxk];
int fr[maxn][maxk];
int a[maxn];

pii get(int number, int i, int tl, int tr, int L, int R)
{
    if (tl >= R || L >= tr)
        return mp(-1, -1);
    if (tl == L && tr == R)
        return tree[number][i];
    int m = (tl + tr) / 2;
    pii g1 = get(number, i * 2, tl, m, L, min(m, R));
    pii g2 = get(number, i * 2 + 1, m, tr, max(L, m), R);
    return max(g1, g2);
}

void upd(int number, int i, int tl, int tr, int pos, pii val)
{
    if (tl + 1 == tr)
    {
        tree[number][i] = max(tree[number][i], val);
        return;
    }
    int m = (tl + tr) / 2;
    if (pos < m)
        upd(number, i * 2, tl, m, pos, val);
    else upd(number, i * 2 + 1, m, tr, pos, val);
    tree[number][i] = max(tree[number][i * 2], tree[number][i * 2 + 1]);
}

int order[maxn];

void solve(int test_number)
{
    int n, k;
    scanf("%d%d", &n, &k);
    forn(j, n)
    {
        scanf("%d", &a[j]);
        order[j] = a[j];
    }
    if (k == 1) {
        printf("1");
        return;
    }
    sort(order, order + n);
    int sz = unique(order, order + n) - order;
    memset(tree, -1, sizeof tree);
    //sort(a, a + n);
    //memset(dp, -1, sizeof(dp));
    dp[0][1] = 1;
    upd(2, 1, 0, sz, upper_bound(order, order + sz, a[0]) - order - 1, mp(a[0], 0));
    fore(i, 1, n - 1)
    {
        for(int j = k; j >= 2; j--)
        {
            int pos2 = lower_bound(order, order + sz, a[i]) - order;
            pii bf = get(j, 1, 0, sz, 0, pos2);
            int g = bf.first;
            if (bf.first == -1)
                dp[i][j] = 0;
            else 
                dp[i][j] = a[i] - g;
            int pos = upper_bound(order, order + sz, dp[i][j] + a[i]) - order;
            //printf("dp[%d][%d] = %d; bf = (%d, %d)\n", i + 1, j, dp[i][j], bf.first, bf.second);
            fr[i][j] = bf.second;
            if (bf.first != -1)
                upd(j + 1, 1, 0, sz, pos - 1, mp(a[i], i));
        }
        dp[i][1] = 0;
        upd(2, 1, 0, sz, upper_bound(order, order + sz, a[i]) - order - 1, mp(a[i], i));
    }
    vi answer;
    forn(i, n)
        if (dp[i][k] != 0)
        {
            int cur = i;
            for (int iter = k; iter > 0; iter--)
            {
                int f = fr[cur][iter];
                answer.pb(cur + 1);
                cur = f;
            }
            for (int j = answer.size() - 1; j >= 0; j--)
                printf("%d ", answer[j]);
            exit(0);
        }
    printf("NO");

}
