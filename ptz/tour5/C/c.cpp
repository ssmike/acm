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
    freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

void solve(int test_number)
{
    int n, k;
    cin >> n >> k;
    if (k == 0) {
        cout << 0 << endl;
    } else if (n == 2) {
        cout << 1 << endl;
        cout << "0 1" << endl;
    } else if (k == 1) {
        cout << 2 << endl;
        cout << 0 << ' ' << n - 1 << endl;
        cout << 1 << ' ' << n - 1 << endl;
    } else if (k == n - 1) {
        cout << 2 << endl;
        cout << 0 << ' ' << n - 1 << endl;
        cout << 0 << ' ' << n - 2 << endl;
    } else {
        cout << 3 << endl;
        cout << 0 << ' ' << n - 1  << endl;
        cout << 0 << ' ' << k - 1 << endl;
        cout << k << ' ' << n - 1 << endl;
    }
}
