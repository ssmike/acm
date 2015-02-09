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

const int maxn = 4e5 + 5;
const int inf = 1e9;


int p[maxn];
int closest[maxn];

bool KMP(string s, int L, bool flag)
{
    memset(p, 0, sizeof(p));
    int k = 0;
    //cout << "KMP" << s << endl;
    fore(j, 1, s.length() - 1)
    {
        while(k > 0 && s[k] != s[j])
            k = p[k - 1];
        if (s[k] == s[j])
            k++;
        p[j] = k;
        if (p[j] == L)
        {
            //cout << "j = " << j << endl;
            if (flag)
                return true;
            else
            {
                assert(closest[j - L - 1] == -1);
                closest[j - L - 1] = j - L - 1 - L + 1;
            }
        }
    }
    return false;
}


int dp[maxn];
int tree[4 * maxn];

int get(int i, int tl, int tr, int L, int R)
{
    if (tl >= R || L >= tr)
        return inf;
    if (tl == L && tr == R)
        return tree[i];
    int m = (tl + tr) / 2;
    int g1 = get(i * 2, tl, m, L, min(m, R));
    int g2 = get(i * 2 + 1, m, tr, max(m, L), R);
    return min(g1, g2);
}

void upd(int i, int tl, int tr, int pos, int val)
{
    if (tl + 1 == tr)
    {
        tree[i] = val;
        return;
    }
    int m = (tl + tr) / 2;
    if (pos < m)
        upd(i * 2, tl, m, pos, val);
    else upd(i * 2 + 1, m, tr, pos, val);
    tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}


int cost[26];
string s;

void build(int i, int tl, int tr)
{
    if (tl + 1 == tr)
    {
        tree[i] = cost[s[tl] - 'a'];
        return;
    }
    int m = (tl + tr) / 2;
    build(i * 2, tl, m);
    build(i * 2 + 1, m, tr);
    tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    //printf("tree[%d] = %d tl = %d tr = %d\n", i, tree[i], tl, tr);
}

string t[11];
bool bad[11];
string t1[11];

void solve(int test_number)
{
    int k;
    cin >> s;
    cin >> k;
    forn(j, s.length())
        closest[j] = -1;
    //cout << s << endl;
    forn(j, k)
        cin >> t[j];
    forn(first, k)
        forn(second, k) if (first != second)
        {
            bool f = KMP(t[first] + "#" + t[second], t[first].length(), true);
            if (f)
            {
                //printf("here!\n");
                if (t[first].length() != t[second].length())
                    bad[second] = true;
                else if (first < second)
                    bad[first] = true;
            }
        }
    forn(j, k)
        if (!bad[j])
        {
            KMP(t[j] + "#" + s, t[j].length(), false);
        }
    //forn(j, s.length())
      //  cout << "closest" << j << " " << closest[j] << endl;
    //exit(0);
    forn(j, 26)
    {
        cin >> cost[j];
        //printf("cost[%d] = %d\n", j, cost[j]);
    }
    int len = s.length();
    build(1, 0, len);
    forn(i, len)
    {
        if (closest[i] == -1)
        {
            dp[i] = (i == 0 ? 0 : dp[i - 1]); 
        }
        else
        {
            dp[i] = get(1, 0, len, closest[i], i + 1);
            //cout << "closest " << i <<  " " << closest[i] << endl;
            //cout << "dp " << i << " " <<  dp[i] << endl;
        }
        if (i + 1 < len)
        {
            int new_val = dp[i] + cost[s[i + 1] - 'a'];
            //cout << "new_val for " << i + 1 << " " << new_val << endl;
            upd(1, 0, len, i + 1, new_val);
        }
    }
    cout << dp[len - 1] << endl;
}
