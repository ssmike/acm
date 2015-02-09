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
    //freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

int n, m;
int p[100100];
int cnt;
map<pair<int, int> , bool> q;

inline void ask(int p) {
    if (p < n)
        cout << "s " << p + 1 << ' ';
    else
        cout << "t " << p - n << ' ';
}

inline void ask(int p1, int p2) {
    ask(p1);
    ask(p2);
    cout << endl;
}

inline bool cmp(int p1, int p2) {
    if (q.find(mp(p1, p2)) != q.end())
        return q[mp(p1, p2)];
    if (p1 == n || p2 == n)
        return false;
    else {
        cnt--;
        ask(p1, p2);
        string s;
        cin >> s;
        return q[mp(p1, p2)] = s == "Yes";
    }
}

void solve(int test_number)
{
    cin >> n >> m;
    int cur = 1;
    int j = 0;
    int res = 0;
    memset(p, 255, sizeof(p));
    p[0] = 0;
    for (int i = 0; i < m; i++) {
        cnt = 5;
        while (cnt > 0) {
            if (cur > n + 1 + i)
                break;
            if (j > 0 && !cmp(cur, j)) 
                j = p[j - 1];
            else {
                if (cmp(cur, j))
                    j++;
                p[cur] = j;
                /*for (int k = 0; k <= cur; k++)
                    cout << p[k] << ' ';
                cout << endl;*/
                cur++;
                j = p[cur - 1];
            }
        }
        if (p[n + i + 1] == n)
            res++;
        cout << "$ " << res << endl;
    }
}
