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
    //freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

const int maxn = 1005;

vi edges[maxn];
int d[3][maxn];
int color[maxn];
int bound[maxn];

void dfs(int number, int v, int anc, int cur_d)
{
    d[number][v] = cur_d;
    forn(j, edges[v].size())
    {
        int u = edges[v][j];
        if (u != anc && color[u] == c)
            dfs(number, u, v, cur_d + 1);
    }
}

inline bool on_path(int number1, int number2, int v, int full)
{
    return d[number1][v] + d[number2][v] == full;
}

void split(int v, int anc)
{
   color[v] = cnt;
   forn(j, edges[v].size())
   {
        int u = edges[v][j];
        if (u == anc)
            continue;
       if (color[u] == c)
            split(u, v);
   }
}

void solve(int test_number)
{
    int n;
   scanf("%d", &n);
   forn(j, n - 1)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].pb(v);
        edges[v].pb(u);
    }
    /*int first_v = -1;
    fore(j, 1, n)
        if (edges[j].size() <= 1)
        {
            first_v = j;
            break;
        }
    printf("%d 1\n", first_v);
    bound[first_v] = 1;
    fore(j, 1, n)
        color[j] = 1;
    cnt = 1;*/
    bound[1] = 1;
    printf("1 1\n");
    fflush(stdout);
    while(true)
    {
        int opp_move, opp_color;
        scanf("%d%d", &opp_move, &opp_color);
        if (opp_move == -1)
        {
            exit(0);
        }
        c = color[opp_move];
        int first_bound = -1;
        int second_bound = -1;
        fore(j, 1, n)
            if (color[j] == c && bound[j] != 0)
            {
                if (first_bound == -1)
                    first_bound = j;
                else if (second_bound == -1)
                    second_bound = j;
                else assert(false);
            }
        assert(first_bound != -1);
        if (second_bound == -1)
        {
            fore(j, 1, n) if (color[j] == c && j != first_bound)
            {
                int e_cnt = 0;
                forn(h, edges[j].size())
                {
                    int u = edges[j][h];
                    if (color[u] == c)
                        e_cnt++;
                }
                if (e_cnt == 1)
                {
                    second_bound = j;
                    bound[second_bound] = 1;
                    break;
                }
            }
            assert(second_bound != -1);
        }
        dfs(0, opp_move, -1, 0);
        dfs(1, first_bound, -1, 0);
        dfs(2, second_bound, -1, 0);
        int center = -1;
        fore(j, 1, n) if (color[j] == c)
            if (on_path(0 ,1, j, d[0][first_bound]) && on_path(0, 2, j, d[0][second_bound]) && on_path(1, 2, j, d[1][second_bound]))
            {
                center = j;
                break;
            }
        assert(center != -1);
        int chosen = 1;
        while(opp_color == chosen || chosen == bound[first_bound] || chosen == bound[second_bound])
        {
            chosen++;
        }
        printf("%d %d\n", center, chosen);
        fflush(stdout);
        bound[center] = chosen;
        forn(j, edges[center].size())
        {
            int u = edges[center][j];
            if (color[u] == c)
            {
                cnt++;
                split(u, center);
            }
        }
                    
    }
}
