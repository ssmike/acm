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

int n;
int a[1010][1010];
bool used[1010];
int l[1010], r[1010];
const int LEN = 1000000;
int p1, p2;
vector<int> all;

inline int intersect(int i, int j) {
    if (l[i] < l[j])
        return max(0, r[i] - l[j]);
    else
        return max(0, r[j] - l[i]);
}

inline bool check() {
    int last = all[all.size() - 1];
    for (int i = 0; i < (int)all.size() - 1; i++) {
        if (intersect(last, all[i]) != a[last][all[i]])
            return false;
    }
    return true;
}

inline void dfs(int v, int pred = -1) {
    used[v] = true;
    all.push_back(v);
    if (pred != -1) {
        l[v] = r[pred] - a[pred][v];
        r[v] = l[v] + LEN;
        if (!check()) {
            r[v] = l[pred] + a[pred][v];
            l[v] = r[v] - LEN;
            if (!check()) {
                cout << "No" << endl;
                exit(0);
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (a[v][i] != 0) {
            if (used[i])
                continue;
            dfs(i, v);
        }
}

inline void dfs2(int v) {
    used[v] = true;
    all.pb(v);
    for (int i = 0; i < n; i++)
        if (a[v][i] != 0 && !used[i])
            dfs2(i);
}

void solve(int test_number)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    for (int i = 0; i < n; i++)
        if (!used[i]) {
            l[i] = 0, r[i] = LEN;
            bool flag = false;
            p1 = i;
            for (int j = i + 1; j < n; j++) {
                if (a[i][j] != 0 && a[i][j] != LEN) {
                    flag = true;
                    p2 = j;
                    break;
                }
            }
            if (!flag) {
                all.clear();
                dfs2(i);
                for (int j = 0; j < (int)all.size(); j++)
                    for (int k = 0; k < (int)all.size(); k++)
                        if (a[j][k] != LEN) {
                            cout << "No" << endl;
                            exit(0);
                        }
                continue;
            }
            all.clear();
            dfs(p1);
        }
    cout << "Yes" << endl;
}
