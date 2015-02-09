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

#define TASKNAME "galois"

void solve(int test_number);

int main() {
    ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
    freopen(TASKNAME ".in", "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

#define MAXN 500000
#define MOD 1000000007
bool vis[MAXN];
int p[MAXN];
int q[MAXN];


int cyc(int x) {
   int c = 0;
   while (!vis[x]) {
       c++;
       vis[x] = true;
       x = p[x];
   }
   return c;
}

void solve(int test_number)
{
    int n;
    /*n = 4;
    for (int i = 0; i < n; i++)
        p[i] = i;
    for (int i = 1; i < n; i++)
        swap(p[i], p[rand()%(i+1)]);*/
    cin >> n;
    for (int i = 0; i< n; i++) {
        cin >> p[i];
        p[i]--;
    }
    vector<lint> cc;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) cc.push_back(cyc(i));
    }
    sort(cc.begin(), cc.end());
    lint ans = 1;
    for (int i = 0; i < (int)cc.size(); i++) {
        ans = (ans * cc[i]) % MOD;
    }
    bool div2 = false;
    for (int i = 0; i < (int)cc.size(); i++) {
        if (i == 0 || cc[i - 1] != cc[i]) {
            for (int j = i; j < (int)cc.size() && cc[j] == cc[i]; j++) {
                ans = (ans * (j - i + 1)) % MOD;
                if (cc[j] % 2 == 1 && j > i)
                    div2 = true;
            }
        }
    }
    for (int i = 0; i < (int)cc.size(); i++) {
        if (cc[i] % 2 == 0) {
            div2 = true;
        }
    }
    if (div2)
        ans = (ans * ((MOD+1)/2)) % MOD;
    /*for (int i = 0; i < n; i++)
        q[i] = i;
    int aans = 0;
    do {
        bool ac = true;
        for (int i = 0; i < n; i++) {
            if (p[q[i]] != q[p[i]])
                ac = false;
        }
        int inv = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (q[i] > q[j]) 
                    inv++;
            }
        }
        if (inv % 2 != 0)
            ac = false;
        aans += ac;
    } while (next_permutation(q, q + n));
    if (ans != aans) {
        for (int i = 0; i < n; i++)
            cerr << p[i] << " ";
    }
    assert(ans == aans);*/
    cout << ans;
}
