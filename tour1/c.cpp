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
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
    freopen(TASKNAME ".in", "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

int get_typ(Point p1, Point p2)
{
    if (p1.y < p2.y)
        return 1;
    if (p1.y == p2.y)
    {
        if (p1.x == p2.x)
            return -1;
        if (p1.x > p2.x)
            return 1;
        return 0;
    }
    return 0;
}

void solve(int test_number)
{
    scanf("%d", &n);
    forn(i, n)
        scanf("%d%d", &p[i].x, &p[i].y);
    forn(i, n)
    {
        list[0].clear();
        list[1].clear();
        forn(j, n)
        {
            bool typ = get_typ(p[i], p[j]);
            if (typ != -1)
                list[typ].pb(j);
        }

    }
}
