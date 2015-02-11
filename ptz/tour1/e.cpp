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
    //freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    //freopen(TASKNAME ".in", "r", stdin);
    //freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

double sqr(double x)
{
    return x * x;
}

void solve(int test_number)
{
    double x0, y0, x1, y1, x2, y2;
    scanf("%lf%lf", &x0, &y0);
    scanf("%lf%lf", &x1, &y1);
    scanf("%lf%lf", &x2, &y2);
    printf("%.10lf\n", sqrt(sqr(x0 - x2) + sqr(y0 - y2)) + 2 * sqrt(sqr(x1 - x2) + sqr(y1 - y2)));
}
