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
    //ios_base::sync_with_stdio(false);
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
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

const int alpha = 26;
const int inf = 1e9;

struct Vertex
{
    int lastc;
    int link;
    int anc;
    int next[alpha];
    int shortest;
    int max_c;
    Vertex(){}
    Vertex(int _lastc, int _anc)
    {
        lastc = _lastc;
        anc = _anc;
        forn(j, alpha)
            next[j] = -1;
        link = max_c = -1;
        shortest = inf;
    }
};

const int maxn = 1e6 + 5;

int shortest[maxn];
int max_c[maxn];
int answer[maxn];
Vertex A[maxn];
int dp[maxn];

int get_link(int v);

int get_next(int v, int c)
{
    //printf("get_next %d %d\n", v, c);
    if (A[v].next[c] != -1)
        return A[v].next[c];
    if (v == 0)
        return 0;
    int tmp = get_link(v);
    //printf("%d %d %d\n", v, c, tmp);
    return get_next(tmp, c);
}

int get_link(int v)
{
    if (A[v].link != -1)
        return A[v].link;
    int anc = A[v].anc;
    if (anc == 0)
        return 0;
    return get_next(get_link(anc), A[v].lastc);
}


void solve(int test_number)
{
    int k;
    scanf("%d", &k);
    int sz = 0;
    A[0] = Vertex(0, 0);
    fore(j, 1, k - 1)
    {
        string s;
        cin >> s;
        //cout << "s = " << s << endl;
        int cur = 0;
        forn(p, s.length())
        {
            //printf("cur = %d sz = %d\n", cur, sz);
            if (A[cur].next[s[p] - 'a'] == -1)
            {
                A[sz] = Vertex(s[p] - 'a', cur);
                A[cur].next[s[p] - 'a'] = sz;
                sz++;
                cur = sz - 1;
            }
            else cur = A[cur].next[s[p] - 'a'];
        }
        A[cur].shortest = min(A[cur].shortest, (int)s.length());
        A[cur].max_c = max(A[cur].max_c, j);
    }
    //printf("sz = %d\n", sz);
    forn(j, sz)
        A[j].link = get_link(j);
    forn(j, sz)
    {
        A[j].shortest = min(A[j].shortest, A[A[j].link].shortest);
        A[j].max_c = max(A[j].max_c, A[A[j].link].max_c);
        //printf("j = %d %d %d\n", j, A[j].shortest, A[j].max_c);
    }
    string t;
    cin >> t;
    //cout << "t = " << t << endl;
    int cur = 0;
    forn(p, t.length())
    {
        /*while(cur != 0)
        {
            if (A[cur].next[t[p] - 'a'] == -1)
                cur = A[cur].link;
            else
            {
                cur = A[cur].next[t[p] - 'a'];
                break;
            }
        }*/
        cur = get_next(cur, t[p] - 'a');
        //printf("p = %d cur = %d %d %d\n", p, cur, A[cur].shortest, A[cur].max_c);
        shortest[p] = A[cur].shortest;
        max_c[p] = A[cur].max_c;
    }
    forn(p, t.length())
        printf("p = %d %d %d\n", p, shortest[p], max_c[p]);
    forn(j, t.length())
        dp[j] = 0;
    int dp_1 = 0;
    for (int p = t.length() - 1; p >= 0; p--)
    {
        dp[p] = max(dp[p + 1], dp[p]);
        //printf("dp[%d] = %d\n", p, dp[p]);
        if (shortest[p] != inf)
        {
            int new_val = dp[p] + 1;
            if (p - shortest[p] >= 0)
                dp[p - shortest[p]] = max(dp[p - shortest[p]], new_val);
            else dp_1 = max(dp_1, new_val); 
        }
    }
    forn(j, t.length())
        printf("dp[%d] = %d\n", j, dp[j]);
    forn(j, t.length())
    {
        int nnew = max_c[j];
        answer[dp[j]] = max(answer[dp[j]], nnew);
    }
    for (int j = dp_1 - 1; j >= 0; j--)
        printf("%d ", answer[j]);
    printf("\n");
}
