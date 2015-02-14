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

const int MAXN = 200100;
const int LOG = 20;

int n;
vector<int> g[MAXN];
vector<li> ww[MAXN];
int p[MAXN][LOG];
int d[MAXN][LOG];
int order[MAXN];
int nord;
int from_pos[MAXN];
int to_pos[MAXN];
int level[MAXN];
li weight[MAXN];
int t[4 * MAXN];
int timer;
int tin[MAXN], tout[MAXN];

inline int get(int v, int vl, int vr, int l, int r) {
    if (l >= r)
        return 0;
    if (vl == l && vr == r)
        return t[v];
    int d = (vl + vr) / 2;
    return get(v * 2, vl, d, l, min(d, r)) + 
        get(v * 2 + 1, d, vr, max(l, d), r);
}

inline void put(int v, int vl, int vr, int pos, int val) {
    if (vl + 1 == vr) {
        t[v] = val;
        return;
    }
    int d = (vl + vr) / 2;
    if (pos < d)
        put(v * 2, vl, d, pos, val);
    else
        put(v * 2 + 1, d, vr, pos, val);
    t[v] = t[v * 2] + t[v * 2 + 1];
}

inline void dfs(int v, int cur_level = 0, li cur_weight = 0) {
    level[v] = cur_level;
    weight[v] = cur_weight;
    tin[v] = timer++;
    order[nord++] = v;
    from_pos[v] = nord - 1;
    for (int i = 1; i < LOG; i++) {
        if (p[v][i - 1] == -1) {
            p[v][i] = -1;
            continue;
        }
        p[v][i] = p[p[v][i - 1]][i - 1];
        d[v][i] = d[p[v][i - 1]][i - 1] + d[v][i - 1];
    }
    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i];
        int w = ww[v][i];
        dfs(to, cur_level + 1, cur_weight + w);
    }
    tout[v] = timer++;
    to_pos[v] = nord;
}

inline void precalc() {
    dfs(0);
}

inline bool is_ancestor(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

inline int get_lca(int v, int u) {
    if (is_ancestor(v, u))
        return v;
    if (is_ancestor(u, v))
        return u;
    for (int i = LOG - 1; i >= 0; i--) {
        int cur = p[v][i];
        if (cur == -1)
            continue;
        if (!is_ancestor(cur, u))
            v = cur;
    }
    return p[v][0];
}

inline int get_dist(int v, int u) {
    return level[u] - level[v];
}

inline li get_weight(int v, int u) {
    return weight[u] - weight[v];
}

inline li get_cnt(int v) {
    return get(1, 0, n, from_pos[v], to_pos[v]);
}

inline void add_cnt(int v) {
    put(1, 0, n, from_pos[v], 1);
}

inline int get_v_from(int v, int dist) {
    int cur = v;
    for (int i = 0; i < LOG; i++)
        if (dist & (1 << i))
            cur = p[cur][i];
    return cur;
}

inline bool check_down(int v) {
    li after_cnt = get_cnt(v);
    li before_cnt = get_cnt(0) - get_cnt(v);
    //cout << after_cnt << ' ' << before_cnt << endl;
    li diff = after_cnt - before_cnt;
    //cout << diff << endl;
    return diff > 0;
}

inline int bin_search_down(int cur, int last) {
    int dist = get_dist(cur, last);
    int l = 1, r = dist + 1;
    while (l + 1 != r) {
        int d = (l + r) / 2;
        int v = get_v_from(last, dist - d);
        //cout << "checking " << v << endl;
        if (check_down(v))
            l = d;
        else
            r = d;   
    }
    return l;
}

inline bool check_up(int v, int from) {
    li before_cnt = get_cnt(from);
    li after_cnt = get_cnt(0) - before_cnt;;
    //cout << after_cnt << ' ' << before_cnt << endl;
    li diff = after_cnt - before_cnt;
    //cout << diff << endl;
    return diff > 0;
}

inline int bin_search_up(int cur, int last) {
    int dist = get_dist(last, cur);
    int l = 1, r = dist + 1;
    while (l + 1 != r) {
        int d = (l + r) / 2;
        int v = get_v_from(cur, d);
        int from = get_v_from(cur, d - 1);
        //cout << "checking " << v << endl;
        if (check_up(v, from))
            l = d;
        else
            r = d;   
    }
    return l;
}

void solve(int test_number)
{
    memset(p, 255, sizeof(p));
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &p[i][0], &d[i][0]);
        p[i][0]--;
        g[p[i][0]].push_back(i);
        ww[p[i][0]].push_back(d[i][0]);
    }
    precalc();

    //cout << "answer: 1 - ";
    puts("0");
    li sum = 0;
    int cur = 0;
    add_cnt(0);
    for (int last = 1; last < n; last++) {
        //if (last == 9)
            //break;
        add_cnt(last);
        if (last == cur) {
            //cout << "answer: " << cur + 1 << " - ";
            printf("%lld\n", sum);
            continue;
        }
        if (is_ancestor(cur, last)) {
            sum += get_weight(cur, last);
            int dist = get_dist(cur, last);
            int l = bin_search_down(cur, last);
            int new_cur = get_v_from(last, dist - l);
            //cout << "new_cur = " << new_cur << endl;
            //cout << "sum = " << sum << endl;
            if (check_down(new_cur)) {
                li w = get_weight(cur, new_cur);
                sum += w * (get_cnt(0) - 2LL * get_cnt(new_cur)); // ?
                cur = new_cur;
            }
        } else if (is_ancestor(last, cur)) {
            sum += get_weight(last, cur);
            int l = bin_search_up(cur, last);
            int new_cur = get_v_from(cur, l);
            int from = get_v_from(cur, l - 1);
            if (check_up(new_cur, from)) {
                li w = get_weight(new_cur, cur);
                int from = get_v_from(cur, l - 1);
                sum += w * (2LL * get_cnt(from) - get_cnt(0));
                cur = new_cur;
            }
        } else {
            int lca = get_lca(cur, last);
            sum += get_weight(lca, cur) + get_weight(lca, last);
            // checking path (cur -> lca)
            int l = bin_search_up(cur, lca);
            int new_cur = get_v_from(cur, l);
            int from = get_v_from(cur, l - 1);
            if (check_up(new_cur, from)) {
                li w = get_weight(new_cur, cur);
                int from = get_v_from(cur, l - 1);
                sum += w * (2LL * get_cnt(from) - get_cnt(0));
                cur = new_cur;
                if (cur == lca) {
                    int dist = get_dist(cur, last);
                    int l = bin_search_down(cur, last);
                    int new_cur = get_v_from(last, dist - l);
                    //cout << "new_cur = " << new_cur << endl;
                    //cout << "sum = " << sum << endl;
                    if (check_down(new_cur)) {
                        li w = get_weight(cur, new_cur);
                        sum += w * (get_cnt(0) - 2LL * get_cnt(new_cur)); // ?
                        cur = new_cur;
                    }
                }
            }
        }
        //cout << "answer: " << cur + 1 << " - ";
        printf("%lld\n", sum);
    }
    
    /*
    cout << endl;
    cout << "Debug info" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << tin[i] << ' ';
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << tout[i] << ' ';
    cout << endl << endl;;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << get_lca(i, j) << ' ';
        cout << endl;
    }
    */
}
