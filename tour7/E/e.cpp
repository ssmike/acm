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

#define TASKNAME "permutation"

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
    //freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

#define MAXN 100000

int ans[MAXN];
int anss;
int p[MAXN], pp[MAXN];
bool mark[MAXN];

void solve(int test_number)
{
    int n;
    scanf("%d", &n);      
    for (int i = 0; i < n; i++) {
        scanf("%d", p + i);
        p[i]--;
        pp[i] = p[i];
    }
    anss = 0;
    forn(i, n) {
        if (p[i] != i)
            anss = 1;
    }
    forn(i, n) {
        if (p[p[i]] != i) anss = 2;
    }
    if (anss == 0) {
        printf("0\n");
    } else if (anss == 1) {
        printf("1\n");
        forn(i, n) {
            printf("%d ", p[i] + 1);
        }
        printf("\n");
    } else {
        printf("2\n");
        fill(mark, mark + n, false);
        forn(i, n) {
            ans[i] = i;
        }
        forn(i, n) {
            if (!mark[i]) {
                vi tmp;
                for (int j = i; !mark[j]; j = p[j]) {
                    mark[j] = true;
                    tmp.pb(j);
                }
                for(int i = 1, j = tmp.size() - 1; i < j; i++, j--) {
                    swap(ans[tmp[i]], ans[tmp[j]]);
                }
            }
        }
        forn(i, n) {
            p[i] = ans[p[i]];
        }
        forn(i, n) {
            printf("%d ", ans[i] + 1);
        }
        printf("\n");
        forn(i, n) {
            printf("%d ", p[i] + 1);
        }
        printf("\n");
        forn(i, n) {
            assert(p[p[i]] == i);
            assert(ans[ans[i]] == i);
            assert(ans[p[i]] == pp[i]);
        }
    }
}
