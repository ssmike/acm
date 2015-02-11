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

#define INF (li)(1e+18)
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
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

int n;
int a[10];
li res = INF;
int x[100];
li sum = 0;
li sum_all = 0;
int taken = 0;
bool good[100];
int cnt[100];

inline void rec(int pos) {

    /*if (sum == sum_all) {
    cout << pos << endl;
    for (int i = 0; i < taken; i++)
        cout << x[i] << ' ';
    cout << endl;
    }*/

    res = min(res, sum_all - sum);
    if (pos == (1 << n))
        return;
    
    // untaken
    rec(pos + 1);

    // taken
    for (int i = 0; i < taken; i++) {
        if (!good[x[i] & pos])
            return;
    }
    for (int i = 0; i < n; i++)
        if (pos & (1 << i) && a[i] == 0)
            return;
    x[taken] = pos;
    taken++;
    sum += (li)(cnt[pos] - 1);
    for (int i = 0; i < n; i++)
        if (pos & (1 << i))
            a[i]--;
    rec(pos + 1);
    taken--;
    sum -= (li)(cnt[pos] - 1);
    for (int i = 0; i < n; i++)
        if (pos & (1 << i))
            a[i]++;
}

void solve(int test_number)
{
    cin >> n;
    for (int i = 0; i <= n; i++)
        good[1 << i] = true;
    good[0] = true;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
                cnt[i]++;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum_all += (li)a[i];
    }
    rec(1);
    cout << res << endl;
}
