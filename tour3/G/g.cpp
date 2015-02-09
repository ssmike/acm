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

void solve(int test_number)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(1, 0, n);
    for (int i = 0; i < n; i++) {
        int l = 0, r = i + 1;
        while (l + 1 != r) {
            int d = (l + r) / 2;
            if (get(1, 0, n, i - d, i + 1) == a[i]) 
                l = d;
            else
                r = d;
        }
        lmax[i] = i - l;
    }
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - i;
        while (l + 1 != r) {
            int d = (l + r) / 2;
            if (get(1, 0, n, i, i + d + 1) == a[i])
                l = d;
            else
                r = d;
        }
        rmax[i] = i + l;
    }

    for (int i = 0; i < 16; i++)
        if (a[0] & (1 << i))
            lbit[0][i] = 0;
        else
            lbit[0][i] = -1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 16; j++) {
            if (a[i] & (1 << j))
                lbit[i][j] = i;
            else
                lbit[i][j] = lbit[i - 1][j];
        }
    }

    for (int i = 0; i < 16; i++)
        if (a[n - 1] & (1 << i))
            rbit[n - 1][i] = n - 1;
        else
            rbit[n - 1][i] = INF;
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < 16; j++) 
            if (a[i] & (1 << j))
                rbit[i][j] = i;
            else
                rbit[i][j] = rbit[i + 1][j];
    }

    for (int i = 0; i < n; i++) {
        pair<int, int> b[20];
        for (int j = 0; j < 16; j++)
            b[j] = mp(lbit[i][j], j);
        sort(b, b + 16, greater<pair<int, int> >());
        int cur = 0;
        for (int j = 0; j < 16; j++)
            if (b[j].first == -1)
                lor[i][j] = mp(-1, -1);
            else {
                cur |= (1 << b[j].second);
                lor[i][j] = mp(cur, b[j].first);
            }
    }

    for (int i = 0; i < n; i++) {
        pair<int, int> b[20];
        for (int j = 0; j < 16; j++)
            b[j] = mp(rbit[i][j], j);
        sort(b, b + 16);
        int cur = 0;
        for (int j = 0; j < 16; j++)
            if (b[j].first == INF)
                ror[i][j] = mp(INF, INF);
            else {
                cur |= (1 << b[j].second);
                ror[i][j] = mp(cur, b[j].first);
            }
    }

    for (int i = 0; i < n; i++) {
        //cout << "____________________" << endl;
        int lm = lmax[i], rm = rmax[i];
        if (lor[i][0].second != i) {
            int val = a[i];
            g[1].push_back(mp(val, 1));
            g[min(ror[i][0].second - lor[i][0].second + 2, n + 2)].push_back(mp(val, -1));
        }
        for (int l = 0; l < 16; l++)
            for (int r = 0; r < 16; r++) {
                if (lor[i][l].fi == -1 || ror[i][r].fi == INF)
                    continue;
                int from = lor[i][l].se;
                int to = ror[i][r].se;
                int next_from = (lor[i][l + 1].fi == -1 ? -INF : lor[i][l + 1].se);
                int next_to = (ror[i][r + 1].fi == INF ? +INF : ror[i][r + 1].se);
                if (from == next_from || to == next_to)
                    continue;
                if (lm > from || rm < to)
                    continue;

                next_from = max(next_from, lm), next_to = min(next_to, rm);
                
                int val = (lor[i][l].fi | ror[i][r].fi) + a[i];
                //cout << "~~~~~" << endl;
                //cout << next_from << ' ' << from << " - " << to << " " << next_to << endl;
                //cout << val << endl;
                g[min(to - from + 1, n + 2)].push_back(mp(val, 1));
                g[min(next_to - next_from + 2, n + 2)].push_back(mp(val, -1));
            }
    }

    //cout << "Answer: "<< endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)g[i].size(); j++) {
            int val = g[i][j].fi;
            if (g[i][j].se > 0) {
                cnt[val]++;
                sz_block[val / BLOCK]++;
            } else {
                cnt[val]--;
                sz_block[val / BLOCK]++;
            }
        }
        bool flag = false;
        for (int j = n / BLOCK + 5; j >= 0; j--) {
            if (sz_block[j] != 0) {
                int l = j * BLOCK;
                int r = l + BLOCK;
                for (int k = r - 1; k >= l; k--)
                    if (cnt[k] != 0) {
                        cout << k << '\n';
                        flag = true;
                        break;
                    }
                if (flag)
                    break;
            }
        }
        //if (!flag)
          //  cout << 0 << endl;
    }

    /*cout << "lmax" << endl;
    for (int i = 0; i < n; i++)
        cout << lmax[i] << ' ';
    cout << endl;
    cout << "rmax" << endl;
    for (int i = 0; i < n; i++)
        cout << rmax[i] << ' ';
    cout << endl;
    cout << "lbit" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            cout << lbit[i][j] << ' ';
        cout << endl;
    }
    cout << "rbit" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            cout << rbit[i][j] << ' ';
        cout << endl;
    }
    cout << "lor" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            cout << "(" << lor[i][j].first << ", " << lor[i][j].second << ") ";
        cout << endl;
    }
    cout << "ror" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            cout << "(" << ror[i][j].first << ", " << ror[i][j].second << ") ";
        cout << endl;
    }*/
}
