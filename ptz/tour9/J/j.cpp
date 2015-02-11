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

#define TASKNAME "jitterbug"

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
     freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

const int maxn = 205;
const double eps = 1.0e-6;

int n;
double a[maxn][maxn];
double E[maxn];

void print()
{
    forn(i, n)
    {
        printf("i = %d: ", i);
        forn(j, n + 1)
        {
            if (a[i][j] > -eps)
                printf("+");
            printf("%.2lf ", a[i][j]);
        }
        printf("\n");
    }
   
}

double gauss()
{
 //   print();
    forn(step, n)
    {
        int chosen = -1;
        fore(i, step, n - 1) if (abs(a[i][step]) > eps) 
        {
            chosen = i;
            break;
        }
        if (chosen == -1)
            return -1;
        //assert(chosen != -1);
        //printf("step = %d chosen = %d\n", step, chosen);
        double coeff = 1.0 / a[chosen][step];
        forn(h, n + 1)
        {
            swap(a[step][h], a[chosen][h]);
            a[step][h] *= coeff;
        }
        fore(j, step + 1, n - 1) if (abs(a[j][step]) > eps)
        {
            double coeff = a[j][step];
            fore(h, step, n + 1)
                a[j][h] -= coeff * a[step][h];
        }
    //    printf("\n\n===============================\n\nafter step = %d\n", step);
      //  print();
    }
    //print();
    //E[n - 1] = 0.0;
    memset(E, 0, sizeof(E));
    for (int step = n - 1; step >= 0; step--)
    {
        E[step] = -a[step][n];
        for (int j = step + 1; j <= n - 1; j++)
            E[step] -= E[j] * a[step][j];
    }
    return E[0];
    //printf("E[0] = %.5lf\n", E[0]);
   // forn(j, n)
       // printf("E[%d] = %.5lf\n", j, E[j]);
}

const int L = 1;
//vi edges[maxn];
int base[maxn];
int e[maxn][maxn];

/*void build_graph()
{
    assert(n % L == 0);
    int sz = n / L;
    fore(j, 0, L)
        base[j] = j * sz;
    forn(key, L)
    {
        int start = base[key];
        int finish = base[key + 1] - 1;
        fore(i, start, finish - 1)
        {
            edges[i].pb(i + 1);
            edges[i + 1].pb(i);
        }
    }
    int b = base[1] - 1;
    fore(key, 1, L - 1)
        {
            edges[b].pb(base[key]);
           edges[base[key]].pb(b);
        }
}*/

double get()
{
    memset(a, 0, sizeof(a));
    forn(i, n)
    {
        a[i][i] = 1.0;
                    if (i != n - 1)
                    {
                        int esz = 0;
                        forn(j, n)
                            if (e[i][j] == 1)
                                esz++;
                        double coeff = 1.0 / esz;
                        forn(tj, n) if (e[i][tj] == 1)
                            a[i][tj] = -coeff;
                        a[i][n] = -1.0;
                    }
    }
    a[n - 1][n - 1] = 1.0;
    return gauss();

}

bool mark[maxn];

void dfs(int v)
{
    mark[v] = true;
    forn(j, n)
        if (e[v][j] && !mark[j])
            dfs(j);

}

inline bool check()
{
    memset(mark, false, sizeof(mark));
    //forn(i, n)
      //  if (!mark[i])
        //    dfs(i);
    dfs(0);
    forn(i, n)
        if (!mark[i])
            return false;
    return  true;
}

void solve(int test_number)
{
    int b;
    scanf("%d%d", &n, &b);
    n = 5;
    //printf("%d %d\n", n, b);
    /*n = 3;
    b = 4;
    edges[0].pb(1);
    edges[1].pb(0);
    edges[1].pb(2);
    edges[2].pb(1);*/
    //build_graph();
   /* n = 200;
    forn(j, n)
    {
        edges[j].pb(j + 1);
        if (j + 1 < n)
            edges[j + 1].pb(j);
    }*/
    //printf("n = %d\n", n);
    /*forn(i, n)
    {
        forn(j, n) if (i != j)
        {
            edges[i].pb(j);
            edges[j].pb(i);
        }
    }*/
    forn(i, n)
        forn(j, n)
            if (i != j)
                //e[i][j] = 1;
                e[i][j] = (rand() % 10 != 0);
    /*forn(i, n)
    {
        forn(j, n)
            printf("%d ", e[i][j]);
        printf("\n");
    }*/
    assert(check());
    double cur = get();
    printf("n = %d b = %d\n", n, b);
    while(cur < b)
    {
        bool optimized = false;
        forn(ti, n)
            fore(tj, ti + 1, n - 1) if (e[ti][tj] == 1)
            {
                e[ti][tj] = e[tj][ti] = 0;
                if (!check())
                {
                    e[ti][tj] = e[tj][ti]  = 1;
                    continue;
                }
                double nnew = get();
                if (nnew - cur > eps)
                {
                    cur = nnew;
                    //printf("nnew = %.5lf\n", nnew);
                    optimized = true;
                    //e[ti][tj] = 0;
                }
                else  e[ti][tj] = e[tj][ti] = 1;
                //printf("edges[%d] = %d\n", i, (int)
            }
                //printf("before gauss\n");
        //gauss();
        if (!optimized)
            break;
    }
    vector <pii> ans;
    forn(i, n)
    {
        fore(j, i + 1,  n)
            if (e[i][j])
                ans.pb(mp(i, j));
           // printf("%d ", e[i][j]);
        //printf("\n");
    }
    printf("%d\n", ans.size());
    forn(j, ans.size())
        printf("%d %d\n", ans[j].fi, ans[j].se);
    printf("%.10lf\n", cur);
}
