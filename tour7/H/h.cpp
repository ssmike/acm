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

#define TASKNAME "work"

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
     //freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

inline double sqr(double x)
{
    return x * x;
}

const int maxn = 305;
const double eps = 1.0e-9;

vi ans[maxn];
char a[maxn][maxn];
int worker[maxn];
int cur[maxn];

void solve(int test_number)
{
    int n, m;
    scanf("%d%d\n", &n, &m);
    forn(i, n)
    {
        forn(j, m)
        {
            scanf("%c", &a[i][j]);       
        }
        scanf("\n");
    }
    //forn(i, n)
      //  printf("p[%d] = %d\n", i, p[i]);
    forn(j, m)
        worker[j] = -1;
    forn(i, n)
        cur[i] = 0;
    forn(j, m)
    {
        forn(i, n)
            if (a[i][j] == '1')
            {
                worker[j] = i;
                cur[i]++;
                break;
            }
    }
    //printf("mn = %.5lf\n", mn);
    //forn(i, n)
    //    printf("cur[%d] = %d\n", i, cur[i]);
    //printf("score = %.5lf\n", score);
    while(true)
    {
        bool optimized = false;
        forn(job, m)
        {
            forn(w, n)
            {
                if (a[w][job] == '1')
                {
                    //printf("job = %d w = %d cur[w] = %d cur[worker] = %d\n", job, w, cur[w], cur[worker[job]]);
                    //printf("score = %.5lf cur_score = %.5lf\n", score, cur_score);
                    if (cur[w] < cur[worker[job]] - 1)
                    {
                        cur[w]++;
                        cur[worker[job]]--;
                        optimized = true;
                        worker[job] = w;
    //                    printf("optimized\n");
                        //break;
                    }
                }
            }
        }
        if (!optimized)
            break;
    }
    //printf("score = %.5lf\n", score);
    forn(i, n)
        ans[i].clear();
    forn(job, m)
        if (worker[job] != -1)
            ans[worker[job]].pb(job);
    forn(i, n)
    {
        printf("%d ", (int)ans[i].size());
        forn(h, ans[i].size())
            printf("%d ", ans[i][h] + 1);
        printf("\n");
    }
}
