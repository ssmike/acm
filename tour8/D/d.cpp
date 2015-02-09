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

#define TASKNAME "decomposable"

void solve(int test_number);

string s;

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
    while (cin >> s)
        solve(1);
}

const int ALPHA = 26;

bool used[30];
int res[100][100];

inline void clear(int sz) {
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < ALPHA; j++)
            res[i][j] = sz - 1;
}

inline void print(int sz) {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < ALPHA; j++)
            cout << res[i][j] + 1 << ' ';
        cout << endl;
    }
}

void solve(int test_number)
{
    memset(used, 0, sizeof(used));
    for (int i = 0; i < (int)s.length(); i++)
        used[s[i] - 'a'] = true;
    int cnt = 0;
    for (int i = 0; i < 26; i++)
        if (used[i])
            cnt++;
    if (cnt == 1) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    
    if (s.length() == 2) {
        int a = s[0] - 'a';
        int b = s[1] - 'a';
        cout << 3 << endl;
        cout << 1 << endl;
        cout << 2 << endl;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < ALPHA; j++)
                res[i][j] = 2;
        res[0][a] = 0;
        res[0][b] = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < ALPHA; j++)
                cout << res[i][j] + 1 << ' ';
            cout << endl;
        }

        cout << 3 << endl;
        cout << 1 << endl;
        cout << 2 << endl;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < ALPHA; j++)
                res[i][j] = 2;
        res[0][a] = 1;
        res[1][b] = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < ALPHA; j++)
                cout << res[i][j] + 1 << ' ';
            cout << endl;
        }
        return;
    }

    int len = 1;
    for (int i = 1; i < (int)s.length(); i++)
        if (s[i] == s[0]) {
            len++;
        } else
            break;
    if (len == (int)s.length() - 1) {
        int a = s[0] - 'a';
        int sz = len + 2;
        cout << sz << endl;
        cout << 1 << endl;
        cout << len + 1 << endl;
        clear(sz);
        for (int i = 0; i < len; i++)
            res[i][a] = i + 1;
        for (int i = 0; i < ALPHA; i++)
            if (i != a) {
                res[len][i] = len;
            }
        print(sz);

        int b = s[s.length() - 1] - 'a';
        sz = 3;
        clear(sz);
        cout << 3 << endl;
        cout << 1 << endl;
        cout << 2 << endl;
        res[0][a] = 0;
        res[0][b] = 1;
        print(sz);
        return;
    } else {
        int a = s[0] - 'a';
        int sz = len + 3;
        cout << sz << endl;
        cout << 1 << endl;
        cout << len + 2 << endl;
        clear(sz);
        for (int i = 0; i < len; i++)
            res[i][a] = i + 1;
        for (int i = 0; i < ALPHA; i++)
            if (i != a) {
                res[len][i] = len + 1;
            }
        for (int i = 0; i < ALPHA; i++)
            res[len + 1][i] = len + 1;
        print(sz);

        int rem = s.length() - len;
        sz = rem + 2;
        cout << sz << endl;
        cout << 1 << endl;
        cout << sz - 1 << endl;
        clear(sz);
        res[0][a] = 0;
        for (int i = len; i < (int)s.length(); i++) {
            int b = s[i] - 'a';
            res[i - len][b] = i - len + 1;
        }
        print(sz);
    }
}
