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
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

struct point {
    li x, y;

    point() {
        x = y = 0;
    }

    point(li _x, li _y) {
        x = _x, y = _y;
    }

    void read() {
        cin >> x >> y;
    }

    void write() {
        cout << x << ' ' << y;
    }
};

inline li area(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

inline li area(point a, point b, point c) {
    return area(a, b) + area(b, c) + area(c, a);
}

inline bool counter_clockwise(point a, point b) {
    point o;
    li s = area(o, a, b);
    return s >= 0;
}

const int MAXN = 1010;

int n;
point a[MAXN];
pair<point, int> b[MAXN * 5];
int nb;

void fail() {
    cout << "Impossible" << endl;
    exit(0);
}

bool between(point a, point b, point c) {
    return counter_clockwise(a, c) && counter_clockwise(c, b);
}

pair<point, point> solve(vector<point> a) {
    if (a.size() == 0)
        return mp(point(), point());
    point from = a[0], to = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        //from.write(); 
        //cout << " - " ;
        //to.write();
        //cout << endl;
        point b = a[i - 1], c = a[i];
        if (!counter_clockwise(b, c))
            swap(b, c);
        if (between(from, to, b) && between(from, to, c))
            continue;
        else if (between(from, to, b))
            to = c;
        else
            from = b;
        //from.write(); 
        //cout << " - " ;
        //to.write();
        //cout << endl;
        if (!counter_clockwise(from, to)) { 
            fail();
        }
    }

    return mp(from, to);
}

bool check(int pos) {
    //cout << pos << endl;
    vector<point> after;
    vector<point> before;
    for (int i = pos + 1; i < n; i++)
        after.push_back(a[i]);
    for (int i = pos - 1; i >= 0; i--)
        before.push_back(a[i]);
    for (int i = 0; i < (int)before.size(); i++) {
        before[i].x -= a[pos].x;
        before[i].y -= a[pos].y;
    }
    for (int i = 0; i < (int)after.size(); i++) {
        after[i].x -= a[pos].x;
        after[i].y -= a[pos].y;
    }
    pair<point, point> before_res = solve(before);
    pair<point, point> after_res = solve(after);
    if (pos == 0 || pos == n - 1)
        return true;
    if (between(before_res.first, before_res.second, after_res.first) ||
            between(before_res.first, before_res.second, after_res.second))
        return false;
    return true;
}

void solve(int test_number)
{    
    cin >> n;
    for (int i = 0; i < n; i++)
        a[i].read();
    for (int i = 0; i < n; i++) {
        if (!check(i)) {
            cout << "Impossible" << endl;
            exit(0);
        }
    }
    cout << "Possible" << endl;
}
