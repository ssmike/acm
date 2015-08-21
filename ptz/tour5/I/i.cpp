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

struct Point
{
    int x, y;
    Point(){}
    Point(Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
    i64 operator % (Point an)
    {
        return (i64)x * an.y - (i64)y * an.x;
    }
    i64 sqrDist(Point an)
    {
        return (i64)(x - an.x) * (x - an.x) + (i64)(y - an.y) * (y - an.y);
    }
};

const int maxn = 1e5 + 5;
typedef pair < double, double > mypair;

const double inf = 1e9;
const double eps = 1.0e-6;

int st[maxn];
int sz;
int bounds[maxn][2];
Point p[maxn];
int H;
vector <mypair> seg;

void conhull(int start, int finish, int delta, int number)
{
    for (int i = start; i != finish; i += delta)
    {
        while(sz > 1)
        {
            int prev = st[sz - 2];
            int top = st[sz - 1];
            Point v1(p[prev], p[top]);
            Point v2(p[top], p[i]);
            i64 tmp = v1 % v2;
            if ((tmp < 0) == number || (tmp == 0 && p[prev].sqrDist(p[top]) < p[prev].sqrDist(p[i])))
            {
                sz--;
            }
            else break; 
        }
        bounds[i][number] = st[sz - 1];
        st[sz] = i;
        sz++;
    }
}

bool mycmp(mypair seg1, mypair seg2)
{
    return seg1.se < seg2.se;
}

double intersect(Point p1, Point p2)
{
    double a = p2.y - p1.y;
    double b = p1.x - p2.x;
    double c = -a * p1.x - b * p1.y;
    return (-c - H * b) / a;
}

#define DEBUG false

int mark[maxn];

void solve(int test_number)
{
    int n;
    scanf("%d%d", &n, &H);
    forn(j, n)
        scanf("%d%d%d", &p[j].x, &p[j].y, &mark[j]);
    sz = 2;
    st[0] = 0;
    st[1] = 1;
    conhull(2, n, 1, 0);
    sz = 2;
    st[0] = n - 1;
    st[1] = n - 2;
    bounds[n - 1][1] = bounds[n - 2][1] = n - 1;
    conhull(n - 3, -1, -1, 1);
    if (DEBUG)
    {
        forn(i, n)
            printf("bounds[%d] = %d %d\n", i, bounds[i][0], bounds[i][1]);
    }
    forn(i, n) if (mark[i])
    {
        int L = bounds[i][0];
        mypair s;
        if (p[L].y <= p[i].y)
            s.fi = -inf;
        else s.fi = intersect(p[i], p[L]);
        int R = bounds[i][1];
        if (p[R].y <= p[i].y)
            s.se = inf;
        else s.se = intersect(p[i], p[R]);
        //printf("i = %d s = %.5lf %.5lf\n", i, s.fi, s.se);
        seg.pb(s);
    }
    sort(seg.begin(), seg.end(), mycmp);
    if (DEBUG)
    {
        forn(j, seg.size())
            printf("j = %d %.5lf %.5lf\n", j, seg[j].fi, seg[j].se);
    }
    double last = -inf - 1;
    int answer = 0;
    forn(i, seg.size())
    {
        if (DEBUG) printf("last = %.5lf seg[i].fi = %.5lf\n", last, seg[i].fi);
        if (seg[i].fi - last > eps)
        {
            answer++;
            last = seg[i].se;
            if (DEBUG) printf("take last = %.5lf\n", last);
        }
    }
    printf("%d\n", answer);
}
