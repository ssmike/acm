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

typedef pair<int, bool> mypair;

const int maxn = 5005;

int n;
mypair prec[(1 << 10)][(1 << 10)];
vi S[maxn];
int prof[maxn][5];

void precalc()
{
    forn(holes, (1 << 10))
        forn(balls, (1 << 10))
        {
            prec[holes][balls].fi = 0;
            forn(i, 10) if ((1 << i) & holes)
                {
                    bool flag = false;
                    fore(j, i, 9)
                    {
                        if ((j != i) && ((1 << j) & holes))
                            break;
                        if ((1 << j) & balls)
                        {
                            flag = true;
                            break;
                        }
                    }
                    if (flag)
                        prec[holes][balls].fi++;
                }
            int left_hole = -1;
            int left_ball = -1;
            forn(i, 10)
                if ((1 << i) & holes)
                {
                    left_hole = i;
                    break;
                }
            forn(j, 10)
                if ((1 << j) & balls)
                {
                    left_ball = j;
                    break;
                }
            prec[holes][balls].se = (left_ball != -1 && (left_hole == -1 || left_hole > left_ball));               
        }
}

void solve(int test_number)
{
    precalc();
    scanf("%d", &n);
    forn(i, n)
    {
        int k;
        scanf("%d", &k);
        forn(j, k)
        {
            int x;
            scanf("%d", &x);
            x--;
            S[i].pb(x);
        }
    }
    forn(i, n)
    {
        forn(j, 5)
            prof[i][j] = 0;
        forn(k, S[i].size())
        {
            prof[i][S[i][k] / 10] += (1 << (S[i][k] % 10));   
        }
        //forn(j, 5)
         //   printf("prof[%d][%d] = %d\n", i, j, prof[i][j]);
    }
    int answer = 0;
    forn(i, n)
        {
            fore(j, i + 1, n - 1)
            {
               // printf("i = %d j = %d\n", i, j);
                int sum = 0;
                bool flag = false;
                for (int step = 4; step >= 0; step--)
                {
                    int balls_prof = prof[j][step];
                    if (flag)
                        balls_prof |= (1 << 9);
                    mypair p = prec[prof[i][step]][balls_prof];
                    sum += p.first;
                    flag = p.second;
                    //printf("step = %d sum = %d flag = %d\n", step, sum, flag);
                }
                if (sum % 2 == 1)
                    answer++;
            }
        }
    printf("%d", answer);
}
