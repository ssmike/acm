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

#define TASKNAME "banach"

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
    freopen(TASKNAME ".in", "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

struct point {
    li x, y;

    void read() {
        cin >> x >> y;
    }

    void write() {
        cout << x << ' ' << y << endl;
    }
};

const int MAXN = 510;

int n;
point b[MAXN];
point c[MAXN];
li a[MAXN][MAXN];

li u[MAXN], v[MAXN];
li mt[MAXN];
li mn[MAXN];
bool used[MAXN];
li link[MAXN];

void init() {
    for (int i = 0; i < n; i++) {
        u[i] = v[i] = 0;
        mt[i] = -1;
    }
}

int hungarian() {
    init();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            used[j] = false;
            mn[j] = INF;
            link[j] = -1;
        }

        int curi = i, curj = -1;
        int j;
        while (curi != -1) {
            j = -1;
            for (int j1 = 0; j1 < n; j1++) {
                if (!used[j1]) {
                    if (a[curi][j1] - u[curi] - v[j1] < mn[j1]) {
                        mn[j1] = a[curi][j1] - u[curi] - v[j1];
                        link[j1] = curj;
                    }
                    if (j == -1 || mn[j1] < mn[j])
                        j = j1;
                }
            }

            int delta = mn[j];
            for (int j1 = 0; j1 < n; j1++) {
                if (used[j1]) {
                    u[mt[j1]] += delta;
                    v[j1] -= delta;
                } else {
                    mn[j1] -= delta;
                }
            }
            u[i] += delta;
            
            used[j] = true;
            curj = j;
            curi = mt[curj];
        }

        for (; link[j] != -1; j = link[j]) {
            mt[j] = mt[link[j]];
        }
        mt[j] = i;
    }
    int res = 0;
    for (int i = 0; i < n; i++)
        res += a[mt[i]][i];
    return res;
}

int ans[MAXN];

li sqr(li a) {
    return a * a;
}

li dist(point a, point b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

bool check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            point q = b[i], w = b[j];
            q.x += c[ans[i] - 1].x, q.y += c[ans[i] - 1].y;
            w.x += c[ans[j] - 1].x, w.y += c[ans[j] - 1].y;
            if (dist(q, w) < dist(b[i], b[j])) {
                b[i].write();
                b[j].write();
                q.write();
                w.write();
                cout << i << ' ' << j << endl;
                return false;
            }
        }
    }
    return true;
}

void solve(int test_number)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        b[i].read();
    for (int i = 0; i < n; i++)
        c[i].read();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = -(b[i].x * c[j].x + b[i].y * c[j].y);
        }
    }
    hungarian();
    for (int i = 0; i < n; i++)
        ans[mt[i]] = i + 1;
    //for (int i = 0; i < n; i++)
        //cout << ans[i] << ' ';
    //cout << endl;
    if (check()) {
        cout << "Yes" << endl;
        for (int i = 0; i < n; i++)
            cout << ans[i] << ' ';
        cout << endl;
    } else {
        cout << "No" << endl;
    }
}

