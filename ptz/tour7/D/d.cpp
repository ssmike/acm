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

#define TASKNAME "lines"

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
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

struct Line
{
    int a, b, c;
};

const int maxn = 6005;

Line lines[maxn];
pii mt[maxn];
pii intersect[maxn];
pii v[maxn];
bool was[maxn];
vector <pii> edges[maxn];

bool dfs(int v)
{
    if (was[v])
        return false;
    was[v] = true;
    forn(j, edges[v].size())
    {
        int u = edges[v][j].fi;
        if (mt[u].fi == -1 || dfs(mt[u].fi))
        {
            mt[u] = mp(v, edges[v][j].se);
            return true;
        }
    }
    return false;
}

void solve(int test_number)
{
    int n;
    scanf("%d", &n);
    forn(j, n)
        scanf("%d%d%d", &lines[j].a, &lines[j].b, &lines[j].c);
    vector <pii> points;
    vector <pii> vectors;
    int spec_number = -1;
    forn(i, n) if (lines[i].b != 0)
    {
        int g = __gcd(abs(lines[i].c), abs(lines[i].b));
        int b1 = lines[i].b / g;
        int c1 = lines[i].c / g;
        if (c1 < 0 || (c1 == 0 && b1 < 0))
        {
            b1 *= -1;
            c1 *= -1;
        }
        intersect[i] = mp(c1, b1);
        points.pb(intersect[i]);
    }
    else if (lines[i].c != 0)
        spec_number = i;
    sort(points.begin(), points.end());
    points.resize(unique(points.begin(), points.end()) - points.begin());
    forn(i, n)
    {
        int g = __gcd(abs(lines[i].a), abs(lines[i].b));
        int a1 = lines[i].a / g;
        int b1 = lines[i].b / g;
        if (a1 < 0 || (a1 == 0 && b1 < 0))
        {
            a1 *= -1;
            b1 *= -1;
        }
        v[i] = mp(a1, b1);
        vectors.pb(v[i]);
    }
    sort(vectors.begin(), vectors.end());
    vectors.resize(unique(vectors.begin(), vectors.end()) - vectors.begin());
    forn(i, points.size())
        edges[i].clear();
    forn(i, n) if (lines[i].b != 0)
    {
        int t1 = lower_bound(points.begin(), points.end(), intersect[i]) - points.begin();
        int t2 = lower_bound(vectors.begin(), vectors.end(), v[i]) - vectors.begin();
        edges[t1].pb(mp(t2, i));
    }
    forn(j, vectors.size())
        mt[j] = mp(-1, -1);
    forn(i, points.size())
    {
        forn(j, points.size())
            was[j] = false;
        dfs(i);
    }
    vi ans;
    forn(j, vectors.size())
        if (mt[j].fi != -1)
            ans.pb(mt[j].se);
    //printf("size = %d\n", ans.size());
    if (spec_number != -1)
        ans.pb(spec_number);
    if (ans.empty())
        ans.pb(0);
    printf("%d\n", (int)ans.size());
    forn(j, ans.size())
        printf("%d ", ans[j] + 1);
    printf("\n");
}
