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
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    forn(i, n)
        solve(i);
}

const int inf = 1e9;

string S, T;

void spec_sol()
{
        int start = -1;
        int maxx = 0;
        forn(pos, S.length())
        {
            if (S[pos] == 'b')
            {
                if (start != -1)
                    maxx = max(maxx, pos - start);
                start = -1;
            }
            else
            {
                if (start == -1)
                    start = pos;
            }
        }
        //printf("maxx = %d\n", maxx);
        int answer = 0;
            while(maxx < (int)T.length())
            {
                maxx = maxx * 2 + 1;
                answer++;
            }
        if (start != -1)
        {
            int tmp = (int)S.length() - start;
            int new_ans = 0;
            while(tmp < (int)T.length())
            {
                tmp = tmp * 2;
                new_ans++;
            }
            answer = min(answer, new_ans);
        }
        if (answer == inf)
            cout << -1 << endl;
        else cout << answer << endl;
        exit(0);   
}

const int maxn = 4e5 + 5;

int p[maxn];

bool KMP(string s, int L)
{
    //cout << "KMP" << s << endl;
    int k = 0;
    fore(j, 1, s.length() - 1)
    {
        while(k > 0 && s[k] != s[j])
            k = p[k - 1];
        if (s[k] == s[j])
            k++;
        p[j] = k;
        if (j > L && k == L)
            return true;
    }
    return false;
}

void trying(string t, int iter)
{
    bool result = KMP(t + "#" + S, t.length());
    if (result)
    {
        printf("%d\n", iter);
        exit(0);
    }
}

void solve(int test_number)
{
    cin >> S >> T;
    bool found = false;
    forn(pos, T.length())
        if (T[pos] == 'b')
        {
          found = true;
          break;
        }

    if (!found)
    {
        spec_sol();
    }

    forn(iter, 100)
    {
        //cout << iter << " " << T << endl;
        if (T[T.length() - 1] == '?')
        {
            trying(T.substr(0, T.length() - 1) + 'a', iter);
            trying(T.substr(0, T.length() - 1) + 'b', iter);
        }
        else trying(T, iter);
        //printf("after trying\n");
        int last = -1;
        string T1 = "";
        bool fail = false;
        forn(pos, T.length())
        {
            if (T[pos] == 'b')
            {
                int len = pos - last - 1;
                
                if (last != -1 && len % 2 == 0)
                {
                    fail = true;
                    break;
                }
                
                forn(j, len / 2)
                        T1 += 'a'; 
                T1 += 'b';
                last = pos;
            }
        }
        if (fail)
            break;
        bool flag = T[T.length() - 1] == '?';
        int a_cnt = (flag ? T.length() - last - 2 : T.length() - last - 1);
        //printf("a_cnt = %d last = %d\n", a_cnt, last);
        if (flag)
        {
            forn(j, a_cnt / 2)
                T1 += 'a';
            T1 += '?';
        }
        else
        {
            forn(j, a_cnt / 2)
                T1 += 'a';
            if (a_cnt % 2 == 1)
                T1 += '?';
        }
        T = T1;
    }
    cout << -1 << endl;
}
