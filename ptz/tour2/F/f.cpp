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

struct Vector
{
    int x, y;
    i64 price;
    Vector(){}
    Vector(int _x, int _y, i64 _price) : x(_x), y(_y), price(_price) {}
};

const i64 inf = 1e17;

i64 operator % (Vector first, Vector second)
{
    return (i64)first.x * second.y - (i64)first.y * second.x;
}

typedef map <pii, pair <Vector, Vector > > map_type;

map_type mymap;

bool mycmp(Vector v1, Vector v2)
{
    return v1 % v2 < 0;
}

bool check_norm(int x, int y)
{
    if (x < 0)
        return false;
    if (x > 0)
        return true;
    return y >= 0;
}

int gcd(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    if (x > y)
        return gcd(x % y, y);
    return gcd(x, y % x);
}

pii norm(int x, int y)
{
    i64 g = gcd(abs(x), abs(y));
    if (g == 0)
        return mp(0, 0);
    if (check_norm(x, y))
        return mp(x / g, y / g);
    return mp((-x) / g, (-y) / g);
}

i64 answer;
int n;

const int maxn = 2e5 + 5;

Vector p[maxn];
vector <Vector> list[2];

void get(Vector base)
{
 //   printf("get %d %d\n", base.x, base.y);
    list[0].clear();
    list[1].clear();
    forn(i, n)
    {
        if (base % p[i] < 0)
            list[0].pb(p[i]);
        else if (base % p[i] > 0)
            list[1].pb(p[i]);
    }
    forn(j, 2)
        sort(list[j].begin(), list[j].end(), mycmp);
    /*printf("list[0]:\n");
    forn(j, list[0].size())
        printf("list[0][%d] = (%d %d)\n", j, list[0][j].x, list[0][j].y);
    printf("list[1]:\n");
    forn(j, list[1].size())
        printf("list[1][%d] = (%d %d)\n", j, list[1][j].x, list[1][j].y);*/
    i64 minn = inf;
    int cur = 0;
    forn(j, list[0].size())
    {
        while(cur < (int)list[1].size())
        {
            if (list[0][j] % list[1][cur] < 0)
            {
                minn = min(minn, list[1][cur].price);
                cur++;
            }
            else break;
        }
        i64 tmp = base.price + list[0][j].price + minn;
        //printf("tmp = %lld\n", tmp);
        answer = min(answer, tmp);
    }
}

void solve(int test_number)
{
    cin >> n;
    Vector bad = Vector(0, 0, inf);
    i64 minprice = inf;
    pii minv;
    forn(i, n)
    {
        cin >> p[i].x >> p[i].y >> p[i].price;
        if (p[i].x == 0 && p[i].y == 0)
            continue;
        pii v = norm(p[i].x, p[i].y);
 //       printf("(%d %d) (%d %d)\n", p[i].x, p[i].y, v.fi, v.se);
        if (p[i].price < minprice)
            {
                minprice = p[i].price;
                minv = v;
            }
        if (mymap.find(v) == mymap.end())
            mymap[v] = mp(bad, bad);
        if (check_norm(p[i].x, p[i].y))
        {
            if (mymap[v].fi.price > p[i].price)
                mymap[v].fi = p[i];
        }
        else
        {
            if (mymap[v].se.price > p[i].price)
                mymap[v].se = p[i];
        }
    }
   // printf("minprice = %lld minv = %d %d\n", minprice, minv.fi, minv.se);
    answer = inf;
    if (mymap[minv].fi.price != inf)
       get(mymap[minv].fi);
    if (mymap[minv].se.price != inf)
       get(mymap[minv].se);
    i64 min1 = inf;
    i64 min2 = inf;
    for (map_type :: iterator iter = mymap.begin(); iter != mymap.end(); iter++)
        {
            //pii p = iter->fi;
            pair <Vector, Vector> p = iter->se;
            if (p.fi.price == inf || p.se.price == inf)
                continue;
            i64 nnew = p.fi.price + p.se.price;
            if (nnew < min1)
            {
                min2 = min1;
                min1 = nnew;
            }
            else if (nnew < min2)
                min2 = nnew;
        }
    //printf("min1 = %lld min2 = %lld\n", min1, min2);
    answer = min(answer, min1 + min2);
    if (answer == inf)
        cout << -1;
    else cout << answer;
}
