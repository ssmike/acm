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

#define TASKNAME "elegant"

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
     freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
    
    //for (int i = 3; i <= 30; i++)
    //    solve(i);
}

li a[33][33];
li b[33][33];
li c[33][33];
li c2[33][33];
li d[33][33];
li p[140];
int n;

bool prime(int p) {
    for (int i = 2; i * i <= p; i++)
        if (p % i == 0)
            return false;
    return true;
}

void build_odd(li c[33][33], int shift, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = (i + j) % n;
            b[i][j] = (i + 2 * j) % n + n;
            li p1, p2;
            if (a[i][j] == 0)
                p1 = 1;
            else
                p1 = p[a[i][j] - 1 + shift];
            if (b[i][j] == n)
                p2 = 1;
            else
                p2 = p[b[i][j] - 1 + shift];
            c[i][j] = p1 * p2;
        }
}

inline li gcd(li a, li b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

void shift(int x, int y) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int i2 = (i + x) % n;
            int j2 = (j + x) % n;
            d[i2][j2] = c[i][j] * c2[i2][j2];
        }
}

bool check() {
    set<li> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (q.count(d[i][j]) != 0)
                return false;
            else
                q.insert(d[i][j]);
    return true;
}

void solve(int test_number)
{
    cin >> n;
    //n = test_number;
    //cout << n << endl;
    int cnt = 0;
    int i = 1;
    while (true) {
        i++;
        if (prime(i)) {
            p[cnt] = i;
            cnt++;  
        }
        if (cnt == 139)
            break;
    }
    /*for (int i = 0; i < 10; i++)
        cout << p[i] << ' ';
    cout << endl;
    cout << p[60] << endl;*/
    if (n % 2 == 1) {
        build_odd(c, 0, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << c[i][j] << ' ';
            cout << endl;
        }
    } else {
        build_odd(c, 0, n + 1);
        build_odd(c2, 2 * (n + 1), n + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                int g = gcd(c[0][i], c[j][0]);
                c[j][i] *= g;
                g = gcd(c2[0][i], c2[j][0]);
                c2[j][i] *= g;
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c[i][j] = c[i + 1][j + 1], c2[i][j] = c2[i + 1][j + 1];
        for (int x = 0; x < n; x++)
            for (int y = 0; y < n; y++) {
                shift(x, y);
                //cerr << x << ' ' << y << endl;
                if (check()) {
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) 
                            cout << d[i][j] << ' ';
                        cout << endl;
                    }
                //cerr << x << ' ' << y << endl;
                    return;
                }
                //cerr << x << ' ' << y << endl;
            }
        exit(-1);
    }
}
