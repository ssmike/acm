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
#include <unordered_map>

using namespace std;


#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

#define TASKNAME "adsadasd"

typedef pair<i64, i64> mypair;


typedef map <i64, vector <pii> > map_type;

map_type mymap[1005];

void solve(int test_number);

int main() {
    //ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

const int maxn = 1005;
const i64 PRIME1 = 1e9 + 7;
const i64 PRIME2 = 1e6 + 7;
const i64 MOD = 1e9 + 9;

int ones[maxn];
i64 h[maxn];
int delta[maxn];

inline i64 get(int p)
{
    if (p == 0)
        return 1;
    i64 y = get(p / 2);
    y = y * y;   
    if (p & 1)
    {
        y = y * PRIME1;  
    }
    return y;
}


void solve(int test_number)
{
    //printf("!!!!\n");
    //fflush(stdout);
   int n, m;
   scanf("%d%d", &n, &m);
   
   forn(j, m)
   {
        scanf("%d", &ones[j]);
        if (j != 0)
            delta[j - 1] = ones[j] - ones[j - 1] - 1;
   }
   i64 answer = max(ones[0] - 1, n - ones[m - 1]);
   for (int j = 0; j + 1 < m; j++)
        answer = max(answer, (i64)delta[j]);
   
   fore(cnt, 1, m)
   {
        //printf("cnt = %d\n", cnt);
        //mypair cur = mp(0, 0);
        i64 cur = 0;
        forn(j, cnt)
        {
            i64 g = get(ones[j]);
            cur += g;
            //cur = mp(cur.fi + g.fi, (cur.se + g.se) % MOD); 
        }
        fore(start, 0, m - cnt)
        {
            //printf("start = %d\n", start);
            int finish = start + cnt - 1;
            int L = (start == 0 ? ones[0] - 1 : delta[start - 1]);
            int R = (finish == m - 1 ? n - ones[finish] : delta[finish]);
            
            i64 g = get(n - ones[start]);
            //hash.fi = hash.fi * g.fi;
            //hash.se = (hash.se * g.se) % MOD;
            i64 hash = cur * g;
            //printf("cnt = %d start = %d cur = %lld %lld hash = %lld %lld g = %lld %lld\n", cnt, start, cur.fi, cur.se, hash.fi, hash.se, g.fi, g.se);
            mymap[cnt][hash].pb(mp(L, R));
            g = get(ones[start]);
            cur -= g;
            //cur.fi -= g.fi;
            //cur.se = (cur.se - g.se + MOD) % MOD;
            g = get(ones[finish + 1]);
            cur += g;
            //cur.fi += g.fi;
            //cur.se = (cur.se + g.se) % MOD;
        }
   }
   int tttt = 0;
   fore(cnt, 1, m)
   {
          for (map_type :: iterator iter = mymap[cnt].begin(); iter != mymap[cnt].end(); iter++)
         {
             vector <pii> list = iter->second;
             //list.pb(mp(0, 0));
             if (list.empty())
                continue;
            sort(list.begin(), list.end());
            /*printf("size = %d\n", (int)list.size());
            forn(j, (int)list.size())
                printf("(%d %d)\n", list[j].fi, list[j].se);*/
            assert(tttt <= 2 * m * m + m);
            if (tttt > 2 * m * m + m)
                exit(-1);
            int maxx = 0;
            int j = list.size() - 1;
            while(j >= 0)
            {
                int x0 = list[j].fi;
                while(j >= 0 && list[j].fi == x0)
                {
                    maxx = max(maxx, list[j].se);
                    j--;
                    tttt++;
                }
                tttt++;
                i64 deltax = (j == -1 ? x0 + 1 : x0 - list[j].fi);
                i64 to_add = deltax * (i64)(maxx + 1);
                //printf("to_add = %lld\n", to_add);
                answer += to_add;
            }
        }
   }
   cout << answer;
}
