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

const int BLOCK = 2;

int h, w, n;
pair<int, int> a[200100];
vector<pair<int, int> > sw[500];
int res[200100];
int new_res[200100];

inline int get_block(int x) {
    return x / BLOCK;
}

inline int mov(int from, int cnt) {
    //cout << from << ' ' << cnt << endl;
    if (from % 2 == 0) {
        cnt--;
        int rem = w - from;
        if (cnt <= rem)
            return from + cnt;
        cnt -= rem;
        int step = 2 * (w + 1);
        cnt %= step;
        
        int half_step = w + 1;
        if (cnt <= half_step)
            return mov(w, cnt);
        else
            return mov(0, cnt - half_step);
    } else {
        return w - mov(w - from, cnt);
    }
}

void solve(int test_number)
{
    cin >> h >> w >> n;
    h--, w--;
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].se;
        a[i].fi--, a[i].se--;
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        int block = get_block(a[i].first);
        int g = a[i].second, h = a[i].second + 1;
        for (int j = a[i].fi - 1; j >= block * BLOCK; j--) {
            if (j % 2 == 0) {
                if (g % 2 == 0) {
                    g++;
                } else {
                    g--;
                }
                if (h % 2 == 0) {
                    h++;
                } else {
                    h--;
                }
            } else {
                if (g % 2 == 0) {
                    g--;
                } else {
                    g++;
                }
                if (h % 2 == 0) {
                    h--;
                } else {
                    h++;
                }
                if (g < 0)
                    g = 0;
                if (h < 0)
                    h = 0;
                if (g == w + 1)
                    g = w;
                if (h == w + 1)
                    h = w;
            }
            //cout << " " << g << " " << h << endl;
        }
        sw[block].push_back(mp(g, h));
    }

    for (int i = 0; i < w + 1; i++)
        res[i] = i;
    for (int i = 0; i < h; i += BLOCK) {
        int block = get_block(i);
        for (int j = 0; j < (int)sw[block].size(); j++)
            swap(res[sw[block][j].fi], res[sw[block][j].se]);
        int len = min(BLOCK, h - i + 2);
        for (int i = 0; i < w + 1; i++) {
            int to = mov(i, len);   
            new_res[to] = res[i];
            //cout << "_____________" << endl;
        }
        for (int i = 0; i < w + 1; i++)
            res[i] = new_res[i];
    }
    for (int i = 0; i < w + 1; i++)
        res[new_res[i]] = i;
    for (int i = 0; i < w + 1; i++)
        cout << res[i] + 1 << '\n';
}
