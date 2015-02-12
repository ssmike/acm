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

#define TASKNAME "adsadasd"

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);
#ifdef LOCAL
    assert(freopen("inp", "r", stdin));
    //freopen("outp", "w", stdout);
#else
#endif
    
    solve();
}

const int maxn = 52;
const int maxk = 22;
const int alpha = 26;
const int MOD = 1e9 + 7;

char s[maxn][maxk];
lint dp[maxn][maxn][maxk][alpha + 1];
int n, maxlen;
bool bad[maxn][maxn][maxk][alpha + 1];

inline lint get(int i, int j, int k, int lower)
{
    if (i > j)
        return 1;
    if (k == maxlen)
        return (i == j ? 1 : 0);
    if (lower > alpha)
        return 0;
    if (dp[i][j][k][lower] != -1)
        return dp[i][j][k][lower];
    i64 ret = get(i, j, k, lower + 1);
    fore(h, i, j)
    {
        if (!bad[i][h][k][lower])
        {
            lint part1 = get(i, h, k + 1, 0);
            lint part2 = get(h + 1, j, k, lower + 1);                             
            ret = (part1 * part2 + ret) % MOD;
        }
        else break;
    }
    return dp[i][j][k][lower] = ret;
}

void precalc()
{
    forn(start, n)
        fore(finish, start, n - 1)
            forn(pos, maxlen)
            {
                fore(number, start, finish)
                {
                     if (s[number][pos] != '\0')
                     {
                         bad[start][finish][pos][0] = true;
                     }
                }
                fore(symbol, 1, alpha)
                    fore(number, start, finish)
                            if (s[number][pos] != '?' && (s[number][pos] != symbol + 'a' - 1))
                            {
                               bad[start][finish][pos][symbol] = true; 
                            }
            }
}

void solve()
{
    memset(s, 0, sizeof s);
    scanf("%d\n", &n);
    maxlen = 0;
    forn(i, n)
    {
        gets(s[i]);
        maxlen = max(maxlen, (int)strlen(s[i]));
    }
    precalc();
    memset(dp, -1, sizeof dp);
    lint answer = get(0, n - 1, 0, 0);
    cout << answer << endl;
}
