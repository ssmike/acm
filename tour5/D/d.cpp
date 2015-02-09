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

const i64 MOD = 1e9 + 7;
const lint MODD = MOD * MOD;
const int sz = 100;

typedef i64 matrix[sz][sz];

inline lint md(lint x) {
    return (x > MODD) ? x - MODD: x;
}

inline void mult(matrix & a, matrix & b, matrix & c)
{
    forn(i, sz)
        forn(j, sz)
        {
            c[i][j] = 0;
            lint * ptr1 = a[i], * ptr2 = b[j];
            lint ac = 0;
            for(int k = 0; k < sz; k++, ptr1++, ptr2++)
                ac = md(ac + (*ptr1) * (*ptr2));
            c[i][j] = ac % MOD;
        }
}

inline void transpose(matrix & res) {
    forn (i, sz) {
        forn(j, i)
            swap(res[i][j], res[j][i]);
    }
}

inline void id(matrix & res) {
    forn (i, sz) {
        forn(j, sz)
            res[i][j] = j == i;
    }
}

void binpow(matrix & a, matrix & res, i64 p)
{
    id(res);
    matrix ra, tmp;
    memcpy(ra, a, sizeof(a));
    transpose(ra);
    while (p > 0) {
        if (p % 2 == 0) {
            mult(a, ra, tmp);
            memcpy(a, tmp, sizeof tmp);
            memcpy(ra, a, sizeof a);
            transpose(ra);
            p /= 2;
        } else {
            mult(res, ra, tmp);
            memcpy(res, tmp, sizeof(res));
            p--;
        }
    }
}



const int con[4] = {1, 5, 10, 25};

matrix a, res;

inline void print(matrix & a)
{
    printf("{");
    forn(i, sz)
    {
        printf("{");
        forn(j, sz)
            printf("%lld, ", a[i][j]);
        printf("},\n");
    }
    printf("},");
}

int get_pos(int i, int j)
{
    return i * 4 + j;
}

#define BLKSZ 100

void solve(int test_number)
{
    i64 n;
    cin >> n;
    lint init[100][4];
    memset(init, 0, sizeof init);
    init[0][0] = init[0][1] = init[0][2] = init[0][3] = 1;
    for (int i = 1; i < 100; i++) {
        for (int j = 0; j < 4; j++) {
            if (con[j] <= i)
                init[i][j] = (init[i - con[j]][j] + init[i][j]) % MOD;
            if (j > 0)
                init[i][j] = (init[i][j] + init[i][j - 1]) % MOD;
        }
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 4; j++) {
            int pos = get_pos(i, j);
            if (get_pos(i - con[j], j) < 0) {
                a[get_pos(i - con[j], j) + BLKSZ][pos]++;
                a[get_pos(i - con[j], j) + BLKSZ][pos] %= MOD;
            } else {
                for (int k = 0; k < BLKSZ; k++) {
                    a[k][pos] = (a[k][pos] + a[k][get_pos(i - con[j], j)]) % MOD;
                }
            }
            if (j > 0) {
                for (int k = 0; k < BLKSZ; k++)
                    a[k][pos] = (a[k][pos] + a[k][get_pos(i, j - 1)]) % MOD;
            }
        }
    }
    //print(a);
    binpow(a, res, n / 25);
    lint ans[25][4];
    memset(ans, 0, sizeof ans);
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 4; j++)
            for (int i1 = 0; i1 < 25; i1++)
                for (int j1 = 0; j1 < 4; j1++)
                    ans[i1][j1] = (ans[i1][j1] + init[i][j] * res[get_pos(i, j)][get_pos(i1, j1)]) % MOD;
    //print(res);
    printf("%lld", ans[n%25][3]);
    /*for (int i = 0; i < 60; i += 1) {
        cerr << i << endl;
        binpow(a, res, (1LL << i));        
        print(res);
    }*/
}
