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

#define TASKNAME "greater"

void solve(int test_number);

int main() {
    ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("precalc.txt", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
   // scanf("%d", &n);
    forn(i, n)
        solve(i);
}

const int maxn = 22;
const int max_pr = 3005;


//int mypow[maxn][maxn];

int p[maxn];

double coeff;

int d, b, max_prof;

vi edges[max_pr];


void precalc()
{
    /*forn(i, b + 1)
    {
        mypow[i][0] = 1;
        fore(j, 1, d)
        {
            mypow[i][j] = mypow[i][j - 1] * i;
            printf("mypow[%d][%d] = %d\n", i, j, mypow[i][j]);
        }
    }*/
    p[0] = 1;
    fore(j, 1, d)
        p[j] = p[j - 1] * (b + 1);
}


double dp[maxn][max_pr][max_pr];
vi list[maxn];

void solve(bool flag)
{
    forn(move, 2 * d)
        fore(prof1, 0, max_prof)
            fore(prof2, 0, max_prof)
                dp[move][prof1][prof2] = 0;
    fore(prof1, 0, max_prof)
        fore(prof2, 0, max_prof)
        {
            dp[2 * d][prof1][prof2] = (prof1 > prof2 ? 1.0 : 0.0);
        }
    for (int move = 2 * d - 1; move >= 0; move--)
    {
        bool first_player;
        if (flag)
            first_player = (move % 2 == 0);
        else first_player = (move < d);
        //printf("move = %d first_player = %d\n", move, first_player);
        int sz1, sz2;
        if (flag)
        {
            if (first_player)
                sz1 = sz2 = move / 2;
            else
            {
                sz1 = move / 2 + 1;
                sz2 = move / 2;
            }
        }
        else
        {
            if (move < d)
            {
                sz1 = move;
                sz2 = 0;
            }
            else
            {
                sz1 = d;
                sz2 = move - d;
            }
        }
        forn(p1, list[sz1].size())
        {
            int prof1 = list[sz1][p1];
            forn(p2, list[sz2].size())
            {
                int prof2 = list[sz2][p2];
                fore(r, 1, b)
                {
                    double chosen = (first_player ? 0.0 : 1.0);
                    if (first_player)
                    { 
                        forn(tmp, d - sz1)
                        {
                            int pos = edges[prof1][tmp];
                            chosen = max(chosen, dp[move + 1][prof1 + p[pos] * r][prof2]);
                        }
                    }
                    else
                    {
                        forn(tmp, d - sz2)
                        {
                            int pos = edges[prof2][tmp];
                            chosen = min(chosen, dp[move + 1][prof1][prof2 + p[pos] * r]);
                        }
                    }
                    //printf("prof1 = %d prof2 = %d r = %d chosen = %.5lf\n", prof1, prof2, r, chosen);
                    dp[move][prof1][prof2] += coeff * chosen;
                }
            }
        }
    }
    printf("%.10lf, ", dp[0][0][0]);
}

void solve(int test_number)
{
/*    for (d = 1; d <= 10; d++)
    {
        for (b = 2; b <= 10; b++)
        {*/
            scanf("%d%d", &d, &b); 
            coeff = 1.0 / b;
            precalc();
            max_prof = 0;
            forn(j, d)
                max_prof += b * p[j];
            if (max_prof > 3000)
            {
                printf("-1.0, -1.0, ");
        //        continue;
            }
            /*int tmp = 1;
            forn(j, d)
                tmp = (tmp * (b + 1));
            printf("tmp = %d\n", tmp);*/
            forn(j, 2 * d)
                list[j].clear();
            fore(prof, 0, max_prof)
            {
                int cnt = 0;
                int cur = prof;
                edges[prof].clear();
                forn(h, d)
                {
                    if (cur % (b + 1) != 0)
                    {
                        cnt++;
                    }
                    else edges[prof].pb(h);
                    cur /= (b + 1);
                }
                list[cnt].pb(prof);
            }
            //assert(max_prof < max_pr);
            //printf("max_prof = %d\n", max_prof);
            solve(true); 
            solve(false);
     //   }
    //}
}
