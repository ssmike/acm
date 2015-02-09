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

bool check_more_eq(int pos, int X)
{
    if (exact[pos])
    {
        return pref[pos] >= X;
    }
    bool f = check_more_eq(p[pos], X - 1);
    if (f)
    {
        
    }
}

void solve(int test_number)
{
    scanf("%d%d", &n, &m);
    forn(p, n)
        order.push(p);
    forn(iter, n - 1)
    {
        order.push(iter + n + 1);
        op_cnt = 5;
        calc();
        printf("$ 0\n");
        fflush(stdout);
    }
    int cur = 0;
    fore(iter, n, m - 1)
    {
        //order.push(iter + n + 1);
        op_cnt = 5;
        if (!check_more_eq(n + iter, n - 1))
        {
            printf("$ %d\n", cur);
        }
        else
        {
            if (check_more_eq(n + iter + 1, n))
                
        }
    }


}
