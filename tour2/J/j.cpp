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
#include <iterator>

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
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
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

#define MOD ((lint)(1000000007))

lint power(lint x, int p) {
    lint r = 1;
    for (int i = 0; i < p; i++)
        r = (r * x) % MOD;
    return r;
}

lint buf[2][300 * 400];

lint * dn[2];

void solve(int test_number)
{   
    int d, s;
    vi l; 
    cin >> d;
    for (int i = 0; i < d; i++) {
        int t; cin >> t;
        l.push_back(t);
    }
    cin >> s;
    memset(dn, 0, sizeof dn);
    dn[0] = buf[0];
    dn[1] = buf[1];
    for (int si = 0; si <= s; si++) {
        dn[0][si] = power(si, d);
    }
    for (int li = 1; li <= d; li++) {
        for (int si = 0; si <= s; si++) {
            dn[1][si] = (dn[0][si] - dn[0][max(si - l[li - 1], 0)] + MOD) % MOD;
        }
        swap(dn[0], dn[1]);
    }
    cout << dn[0][s];
}
