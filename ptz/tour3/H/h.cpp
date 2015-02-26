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

#define INF ((int)((int)1e9 + 10000))

#define MAXP 300000

lint fact[MAXP];


lint q, n, k, p;

void precalc() {
    fact[0] = 1;
    for (int i = 1; i < MAXP; i++) {
        fact[i] = (i * fact[i - 1]) % p;
    }
}

lint pow(lint x, lint p) {
    lint r = 1;
    for (int i = 0; i < p; i++) {
        if (r > INF) return INF;
        r = (r * x);
    }
    return r;
}

lint modPow(lint x, lint p, lint mod) {
    lint r = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            p--;
            r = (r * x) % mod;
        } else {
            p /= 2;
            x = (x * x) % mod;
        }
    }
    return r;
}

lint cnk(int n, int k) {
    return (fact[n] * modPow((fact[n - k] * fact[k]) % p, p - 2, p)) % p;
}

lint countD(lint l, lint r, lint k) {
    return r / k - (l - 1) / k;
}

int order(lint q) {
    int t = 0;
    lint cur = 1;
    while (cur != 1 || t == 0) {
        t++;
        cur = (cur * q) % p;
    }
    return t;
}

lint qFact(lint q, lint n) {
    int t = order(q);
    lint ans = modPow(p - 1, n / t, p);
    for (int i = n; modPow(q, i, p) != 1; i--) {
        ans = (ans * (modPow(q, i, p) + p - 1)) % p;
    }
    return ans;
}

lint inv(lint x) {
    return modPow(x, p - 2, p);
}

lint Fact(lint x) {
    lint ans = modPow(-1, x / p, p);
    return (ans * fact[x % p]) % p;
}

lint calc(lint n, lint k, lint P) {
    if (P > n) return 1;
    if (countD(n - k + 1, n, P) > countD(1, k, P))
        return 0;
    lint ans = (Fact(n/P) * inv((Fact((n - k)/P) * Fact(k/P) % p))) % p;
    return (ans * calc(n, k, P * p)) % p;
}

void solve(int test_number)
{
    cin >> q >> n >> k >> p;
    lint ans = (qFact(q, n) * inv((qFact(q, n - k) * qFact(q, k)) % p)) % p;
    cout << (ans * calc(n, k, order(q))) % p;
}
