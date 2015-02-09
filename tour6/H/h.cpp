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
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

const double EPS = 1e-6;

int n, m, k;
double x[110], y[110];
vector<int> g[10010];

inline pair<int, int> sym(int xx1, int yy1, int i) {
    int xx2, yy2;
    double xxc = x[i], yyc = y[i];
    xx1 *= 2, yy1 *= 2;
    int xc = (int)(floor(xxc) + EPS) * 2;
    if (fabs(floor(xxc) - xxc) > EPS)
        xc++;
    //cerr << xxc << ' ' << xc << endl;
    int yc = (int)(floor(yyc) + EPS) * 2;
    if (fabs(floor(yyc) - yyc) > EPS)
        yc++;
    if (xx1 < xc) {
        xx2 = xc + (xc - xx1) - 2;
    } else {
        xx2 = xc + (xc - xx1) - 2;
    }
    //cerr << xx1 << ' ' << xc << ' ' << xx2 << endl;
    if (yy1 < yc) {
        yy2 = yc + (yc - yy1) - 2;
    } else {
        yy2 = yc + (yc - yy1) - 2;
    }

    xx2 /= 2, yy2 /= 2;
    if (xx2 < 0 || xx2 >= n || yy2 < 0 || yy2 >= m)
        return mp(-1, -1);
    else
        return mp(xx2, yy2);
}

int used[1510];
int mt[1510];
vector<int> p1;
int color;
vector<int> p2;

inline bool dfs(int v) {
    if (used[v] == color)
        return false;
    used[v] = color;
    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i];
        if (mt[to] == -1 || dfs(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int res[1510][1510];
int used1[1510];
int color1;

void solve(int test_number)
{
    for (int i = 0; i < n * m; i++)
        g[i].clear();
    p1.clear();
    p2.clear();
    scanf("%d%d%d", &n, &m, &k);
    //printf("%d %d %d\n", n, m, k);
    for (int i = 0; i < k; i++) {
        scanf("%lf%lf", &x[i], &y[i]);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++) {
                pair<int, int> res = sym(i, j, l);
                //cerr << res.fi << ' ' << res.se << endl;
                if (res == mp(-1, -1))
                    continue;
                //cout << i << " " << j << " - " << res.fi << ' ' << res.se << endl;
                g[i * m + j].pb(res.fi * m + res.se);
                //g[res.fi * n + res.se].pb(i * n + j);
            }
            if ((i + j) % 2 == 0)
                p1.pb(i * m + j);
            else
                p2.pb(i * m + j);
        }
    //puts(""); 
    random_shuffle(p1.begin(), p1.end());
    for (int i = 0; i < n * m; i++)
        mt[i] = -1, used[i] = 0, used1[i] = 0;
    for (int i = 0; i < (int)p2.size(); i++) {
        int v = p2[i];
        for (int j = 0; j < (int)g[v].size(); j++) {
            int to = g[v][j];
            if (!used1[to]) {
                mt[v] = to;
                used1[to] = 1;
                break;
            }
        }
    }
    if (p1.size() != p2.size()) {
        puts("NO");
        return;
    }
    for (int i = 0; i < (int)p1.size(); i++) {
        int cur = p1[i];
        color++;
        if (used1[cur] != 0)
            continue;
        dfs(cur);
    }
    for (int i = 0; i < n * m; i++)
        used[i] = 0;
    for (int i = 0; i < (int)p2.size(); i++) {
        int v = p2[i];
        used[v] = 1;
        if (mt[v] == -1) {
            puts("NO");
            return;
        }
        used[mt[v]] = true;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!used[i * m + j]) {
                puts("NO");
                return;
            }
    puts("YES");
    for (int i = 0; i < (int)p2.size(); i++) {
        int v2 = p2[i];
        int v1 = mt[v2];
        int xx1 = v1 / m, yy1 = v1 % m;
        int xx2 = v2 / m, yy2 = v2 % m;
        for (int j = 0; j < k; j++)
            if (sym(xx1, yy1, j) == mp(xx2, yy2)) {
                res[xx1][yy1] = res[xx2][yy2] = j + 1;
                break;
            }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", res[i][j]);
        puts("");
    }
}
