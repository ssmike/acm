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
#include <ctime>
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

#define TASKNAME "even"

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

#define MAXN 600

vector<int> G[MAXN];
bool vect[MAXN];
int color[MAXN];
bool vis[MAXN];
bool gen[MAXN];
int n, m;

int _cv = 0;

int cvss = 0;
pair<int, int> cvs[MAXN];

inline bool gen_cv(int v, int p, int col, int ev) {
    if (color[v] != 0) {
        return false;
    }
    //assert(_cv < n);
    //_cv++;
    color[v] = col;
    gen[v] = false;
    for (int i = 0; i < (int)G[v].size(); i++) {
        int ncol = col;
        if (G[v][i] == ev) ncol = 3 - col;
        if (G[v][i] != p && color[G[v][i]] != 0 && color[v] != color[G[v][i]])  gen[v] = !gen[v];
        else if (gen_cv(G[v][i], v, ncol, ev)) gen[v] = !gen[v];
    }
    return gen[v];
}

int _f =0;

inline bool gen_f(int v, int p) {
    if (vis[v]) return false;
    //assert(_f <= n);
    //_f++;
    vis[v] = true;
    gen[v] = false;
    for (int i = 0; i < (int)G[v].size(); i++) {
        if (G[v][i] != p && vis[G[v][i]])  gen[v] = !gen[v];
        else if (gen_f(G[v][i], v)) gen[v] = !gen[v];
    }
    return gen[v];
}

#define INTSZ 32
#define INTM(x) ((x)&((1 << 5) - 1))
#define INTLG(x) ((x) >> 5)

int vs[MAXN][MAXN * 3 / INTSZ];



inline bool get(int i, int j) {
    return (vs[i][INTLG(j)] & (1 << INTM(j))) != 0;
}

inline void set_true(int i, int j) {
    vs[i][INTLG(j)] |= 1 << INTM(j); 
}

inline void addto(int from, int to) {
    for (int i = 0; i <= INTLG(2 * n); i++) {
        vs[to][i] = vs[to][i] ^ vs[from][i];
    }
}

inline void c_swap(int a, int b) {
    for (int i = 0; i <= INTLG(2 * n); i++) {
        swap(vs[a][i], vs[b][i]);
    }
}

//int _c_m = 0;

inline void gen_c_m(int v, int c) {
    if (color[v] != 0) return;
    //assert(_c_m < n);
    //_c_m++;
    color[v] = c;
    for (int i = 0; i < (int)G[v].size(); i++) {
        if (get(n, n + G[v][i]))
            gen_c_m(G[v][i], 3 - c);
        else 
            gen_c_m(G[v][i], c);
    }
}

void solve(int test_number)
{
    //clock_t start = clock();
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a - 1].pb(b - 1);
        G[b - 1].pb(a - 1);
    }

    memset(vs, 0, sizeof vs);
    for (int i = 0; i < n; i++) {
        fill(color, color + n, false);
        fill(gen, gen + n, false);
        _cv = 0;
        for (int j = 0; j < n; j++) {
            gen_cv(j, -1, 1, i);
        }
        gen[i] = !gen[i];
        for (int j = 0; j < n; j++)
            if (gen[j])
                set_true(i, j);
        set_true(i, n + i);
    }
    //if (clock() - start > 0.8 * CLOCKS_PER_SEC) exit(2);
    fill(vis, vis + n, false);
    _f = 0;
    for (int i = 0; i < n; i++)
        gen_f(i, -1);
    for (int i = 0; i < n; i++) {
        gen[i] = !gen[i];
    }
    for (int i = 0; i < n; i++)  {
        if (gen[i])
            set_true(n, i);
            //vs[n][i] = gen[i];   
    }
    /*
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2 * n; j++)
            printf("%d", vs[i][j]);
        printf("\n");
    }
    printf("\n");*/
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (get(j, i)) {
                c_swap(j, i);
                break;
            }
        }
        for (int j = 0; j <= n; j++)
            if (i != j && get(j, i)) {
                addto(i, j);
            }
    }/*
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2 * n; j++)
            printf("%d", vs[i][j]);
        printf("\n");
    }
    printf("\n");*/
    for (int i = 0; i < n; i++) {
        if (get(n, i)) {
            printf("IMPOSSIBLE");
            return;
        }
    }
    fill(color, color + n, false);
    fill(vis, vis + n, false);
    //_c_m = 0;
    for (int i = 0; i < n; i++) {
        gen_c_m(i, 1);
    }
    //for (int i = 0; i < n; i++)
    //    gen_f(i);
    for (int i = 0; i < n; i++) {
        if (color[i] == 1) printf("A");
        else printf("B");
    }
}
