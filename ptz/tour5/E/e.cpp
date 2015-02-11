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

inline double sqr(double x)
{
    return x * x;
}

struct Point
{
    double x, y, z;
    Point(){}
    Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    Point(Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}
    double distTo(Point an)
    {
        return sqrt(sqr(x - an.x) + sqr(y - an.y) + sqr(z - an.z));
    }
    void read()
    {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
    void print()
    {
        printf("%.5lf %.5lf %.5lf\n", x, y, z);
    }
};

Point P1, P2, P3, V1, V2;

double f(double t, double u)
{
    Point P(V1.x * t + V2.x * u + P1.x, V1.y * t + V2.y * u + P1.y, V1.z * t + V2.z * u + P1.z);
    return P.distTo(P1) + P.distTo(P2) + P.distTo(P3);
}

const int it_count = 1000;

double get(double t)
{
    double startu = 0;
    double finishu = 1;
    forn(iter_inner, it_count)
    {
        double m1u = startu + (finishu - startu) / 3.0;
        double m2u = finishu - (finishu - startu) / 3.0;
        double f1 = f(t, m1u);
        double f2 = f(t, m2u);
        if (f1 < f2)
            finishu = m2u;
        else startu = m1u;
    }
    return f(t, startu);
}

void solve(int test_number)
{
    P1.read();
    P2.read();
    P3.read();
    V1 = Point(P1, P2);
    V2 = Point(P1, P3);
    //V1.print();
    //V2.print();
    double startt = 0;
    double finisht = 1;
    forn(iter_outer, it_count)
    {
        double m1t = startt + (finisht - startt) / 3.0;
        double m2t = finisht - (finisht - startt) / 3.0;
        //printf("startt = %.5lf finisht = %.5lf m1t = %.5lf m2t = %.5lf\n", startt, finisht, m1t, m2t);
        double g1 = get(m1t);
        double g2 = get(m2t);
        if (g1 < g2)
        {
            finisht = m2t;
        }
        else startt = m1t;
    }
    //printf("startt = %.5lf\n", startt);
    double answer = get(startt);
    printf("%.10lf\n", answer);
}
