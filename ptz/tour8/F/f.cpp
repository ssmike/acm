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
vi c_bounds[maxn];
int n, cnt;

void dfs(int number, int v, int anc, int cur_d)
{
    d[number][v] = cur_d;
    forn(j, edges[v].size())
    {
        int u = edges[v][j];
        if (u != anc)
            dfs(number, u, v, cur_d + 1);
    }
}

void paint(int v, int anc)
{
    color[v] = cnt;
    forn(j, edges[v].size())
    {
        int u = edges[v][j];
        if (u != anc && bound[u] == 0 && color[u] == 0)
        {
            paint(u, v);
        }
        else if (bound[u] != 0)
        {
            bool was = false;
            forn(prev, c_bounds[cnt].size())
                if (c_bounds[cnt][prev] == u)
                {
                    was = true;
                    break;
                }
            if (!was)
                c_bounds[cnt].pb(u);
        }
    }
}

inline bool on_path(int number1, int number2, int v, int full)
{
    return d[number1][v] + d[number2][v] == full;
}

inline void print_move(int v, int c)
{
    printf("%d %d\n", v, c);
    fflush(stdout);
    bound[v] = c;
}


void find_list()
{
    //printf("find_list\n");
    //fore(j, 1, n)
      //  printf("bound[%d] = %d\n", j, bound[j]);
    bool done = false;
    fore(v, 1, n) if (bound[v] == 0)
    {
        int e_cnt = 0;
        forn(h, edges[v].size())
        {
            int u = edges[v][h];
            if (color[u] == color[v])
                e_cnt++;
        }
        if (e_cnt <= 1)
        {
            fore(chosen, 1, 4)
            {
                bool fail = false;
                forn(j, edges[v].size())
                {
                    if (bound[edges[v][j]] == chosen) 
                    {
                        fail = true;
                        break;
                    }
                }
                if (!fail)
                {
                    done = true;
                    print_move(v, chosen);
                    break;
                }
            }
            if (done)
                break;
        }
    }
    assert(done);
}


void solve(int test_number)
{
   scanf("%d", &n);
   forn(j, n - 1)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[u].pb(v);
        edges[v].pb(u);
    }
    print_move(1, 1);
     while(true)
    {
        int opp_move, opp_color;
        scanf("%d%d", &opp_move, &opp_color);
        if (opp_move == -1)
        {
            exit(0);
        }
        bound[opp_move] = opp_color;
        memset(color, 0, sizeof(color));
        int p = 0;
        cnt = 0;
        fore(j, 1, n)
            if (color[j] == 0 && bound[j] == 0)
            {
                cnt++;
                c_bounds[cnt].clear();
                paint(j, -1);
                assert(c_bounds[cnt].size() <= 3);
                if (c_bounds[cnt].size() > c_bounds[p].size())
                    p = cnt;        
            }
        if (c_bounds[p].size() <= 1)
        {
            find_list();
            continue;
        } 
        forn(j, c_bounds[p].size())
        {
            dfs(j, c_bounds[p][j], -1, 0);
            //fore(h, 1, n)
              //  printf("d[%d][%d] = %d\n", j, h, d[j][h]);
        }
        int center = -1;
        fore(j, 1, n) if (color[j] == p)
        {
            bool fail = false;
            forn(first, c_bounds[p].size())
                fore(second, first + 1, c_bounds[p].size() - 1)
                    if (!on_path(first, second, j, d[first][c_bounds[p][second]]))
                    {
                        fail = true;
                        break;
                    }
            if (!fail)
            {
                center = j;
                break;
            }
        }
        assert(center != -1);
        int chosen = 1;
        while(true)
        {
            bool fail = false;
            forn(j, c_bounds[p].size())
                if (bound[c_bounds[p][j]] == chosen)
                {
                    fail = true;
                    break;
                }
            if (!fail)
                break;
            chosen++;
        }
        print_move(center, chosen);
                            
    }
}
