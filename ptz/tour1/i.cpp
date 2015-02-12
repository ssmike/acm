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
#include <unordered_map>
#include <unordered_set>

using namespace std;


#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
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
#ifdef LOCAL
    freopen("inp", "r", stdin);
    freopen("outp", "w", stdout);
#else
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

const li MOD = 1000000007;
const li P1 = 29;
const li P2 = 31;

int n, q;
string s[200100];
string x[200100];
int l[200100], r[200100];
int ord[200100];
li p1[200100];
li p2[200100];

void precalc() {
    p1[0] = p2[0] = 1;
    for (int i = 1; i < 200100; i++) {
        p1[i] = (p1[i - 1] * P1) % MOD; 
        p2[i] = (p2[i - 1] * P2) % MOD;
    }
}

bool cmp(int a, int b) {
    return x[a].length() < x[b].length();   
}

struct hash_pair {
    inline li operator() (const pair<li, li> a) const {
        return (a.first << 32) + a.second;
    }
};

pair<li, li> get_hash(const string& s) {
    li h1 = 0, h2 = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        int c = s[i] - 'a' + 1;
        h1 = (h1 + c * p1[i]) % MOD;
        h2 = (h2 + c * p2[i]) % MOD;
    }
    return mp(h1, h2);
}

void solve(int test_number)
{
    precalc();
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i] >> x[i];
        ord[i] = i;
    }
    sort(ord, ord + q, cmp);
    int cur_len = x[ord[0]].length();
    for (int i = 0; i < q; i++) {
        int start = i;
        int finish = i + 1;
        while ((int)x[ord[finish]].length() == cur_len)
            finish++;
        
        unordered_map<pair<li, li>, unordered_set<int>, hash_pair, equal_to<pair<li, li> >, allocator<pair<pair<li, li>, unordered_set<int> > > > my_map;
        my_map.reserve(finish - start);
        for (int j = start; j < finish; j++) {
            auto cur_h = get_hash(x[j]);
            my_map[cur_h].insert(ord[j]);
        }

        i = finish - 1;
    }
}
