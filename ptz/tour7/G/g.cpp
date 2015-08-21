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

#define TASKNAME "shortest-accepted"

void solve(int test_number);

int main() {
    //ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
     freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n = 1;
    scanf("%d", &n);
    forn(i, n)
        solve(i);
}

const int maxlen = 305;

string s;
int bal[maxlen];

string get(int L, int R)
{
    //printf("L = %d R = %d\n", L, R);
    //cout << "s = " << s.substr(L, R - L + 1) << endl;
    if (L > R)
        return "";
    if (L == R)
    {
        //printf("s[%d] = %c\n", L, s[L]);
        string ret = "";
        if (s[L] != '$' && s[L] != '*')
            ret += s[L];
        //cout << "ret = " << ret << endl;
        return ret;
    }
    if (s[L] == '(' && s[R] == ')')
    {
        int bracket = L + 1;
        while(bracket <= R && (s[bracket] != ')' || bal[L] != bal[bracket + 1]))
            bracket++; 
        if (bracket == R)
            return get(L + 1, R - 1);
    }
    fore(j, L + 1, R - 1)
        if (s[j] == '|' && bal[j] == bal[L])
        {
            string g1 = get(L, j - 1);
            string g2 = get(j + 1, R);
            if (g1.length() != g2.length())
                return (g1.length() < g2.length() ? g1 : g2);
            else return (g1 < g2 ? g1 : g2);
        }
    if (s[L] == '(')
    {
        int bracket = L + 1;
        while(bracket < (int)s.length() && (s[bracket] != ')' || bal[L] != bal[bracket + 1]))
            bracket++;
        assert(bracket < (int)s.length());
        if (bracket + 1 <= R && s[bracket + 1] == '*')
            return get(bracket + 2, R);
        else return get(L + 1, bracket - 1) + get(bracket + 1, R);
    }

    if (s[L + 1] == '*')
        return get(L + 2, R);
    else if (s[L] == '$' || s[L] == '*')
        return get(L + 1, R);
    else return s[L] + get(L + 1, R);
}

void solve(int test_number)
{
    cin >> s;
    //cout << "s = " << s << endl;
    bal[0] = 0;
    fore(j, 1, s.length())
    {
        bal[j] = bal[j - 1];
        if (s[j - 1] == '(')
            bal[j]++;
        else if (s[j - 1] == ')')
            bal[j]--;
    }
    string answer = get(0, s.length() - 1);
    if (answer == "")
        answer = "$";
    cout << answer << endl;
 //   exit(0);
}
