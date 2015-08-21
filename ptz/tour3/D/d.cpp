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

void fail() {
    cout << -1 << endl;
    exit(0);
}

void solve(int test_number)
{
    li l, s;
    cin >> l >> s;
    if (l % 2 == 1)
        fail();
    li half = l / 2;
    li n = half / 2, m = half - n;
    if (n + m - 1 > s || n * m < s)
        fail();
    if (s == n * m) {
        cout << 4 << endl;
        cout << 0 << ' ' << 0 << endl;
        cout << 0 << ' ' << n << endl;
        cout << m << ' ' << n << endl;
        cout << m << ' ' << 0 << endl;
    } else {
        li lines = (s - m) / (n - 1);
        if ((s - m) % (n - 1) == 0) {
            cout << 6 << endl;;
            cout << 0 << ' ' << 0 << endl;
            cout << 0 << ' ' << n << endl;
            cout << lines << ' ' << n << endl;
            cout << lines << ' ' << 1 << endl;
            cout << m << ' ' << 1 << endl;
            cout << m << ' ' << 0 << endl;
        } else if (lines + 1 == m) {
            li mod = (s - m) % (n - 1);
            cout << 6 << endl;
            cout << 0 << ' ' << 0 << endl;
            cout << 0 << ' ' << n << endl;
            cout << lines << ' ' << n << endl;
            cout << lines << ' ' << 1 + mod << endl;
            cout << lines + 1 << ' ' << 1 + mod << endl;
            cout << m << ' ' << 0 << endl;
        } else {
            li mod = (s - m) % (n - 1);
            cout << 8 << endl;
            cout << 0 << ' ' << 0 << endl;
            cout << 0 << ' ' << n << endl;
            cout << lines << ' ' << n << endl;
            cout << lines << ' ' << 1 + mod << endl;
            cout << lines + 1 << ' ' << 1 + mod << endl;
            cout << lines + 1 << ' ' << 1 << endl;
            cout << m << ' ' << 1 << endl;
            cout << m << ' ' << 0 << endl;
        }

    }

}
