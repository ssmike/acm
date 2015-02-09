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

#define WIN 3
#define LOSE 2
#define DRAW 1

void solve(int test_number);

typedef char matrix[3][3];

const int sz = 60000;
const int dx[4] = {0, 1, 1, 1};
const int dy[4] = {1, 0, 1, -1};

int game[sz];
int pows[15];
vi lose_moves[sz];
vi win_moves[sz];
vi draw_moves[sz];
bool reachable[sz];

inline void decode(int mask, matrix & result)
{
    forn(i, 3)
        forn(j, 3)
        {
            if (mask % 3 != 0)
            {
                result[i][j] = (mask % 3 == 1 ? 'O' : 'X');
            }
            else result[i][j] = '.';
            mask /= 3;
        }
}

inline bool check_victory(matrix & a)
{
    forn(i, 3)
        forn(j, 3) if (a[i][j] != '.')
            forn(move, 4)
            {
                bool fail = false;
                int curx = i;
                int cury = j;
                forn(step, 3)
                {
                    if (curx < 0 || curx >= 3 || cury < 0 || cury >= 3 || (a[curx][cury] != a[i][j]))
                    {
                        fail = true;
                        break;
                    }
                    curx += dx[move];
                    cury += dy[move];
                }
                if (!fail)  
                    return true;
            }
    return false;
}

inline bool check_can_move(matrix & a)
{
    forn(i, 3)
        forn(j, 3)
            if (a[i][j] == '.')
                return true;
    return false;
}

inline int get_player(matrix & a)
{
    int cntO = 0;
    int cntX = 0;
    forn(i, 3)
        forn(j, 3)
            if (a[i][j] == 'O')
                cntO++;
            else if (a[i][j] == 'X')
                cntX++;
    return (cntO > cntX ? 2 : 1);
}

void print(matrix & a)
{
    forn(i, 3)
    {
        forn(j, 3)
            printf("%c", a[i][j]);
        printf("\n");
    }
}

int go(int cur)
{
    if (game[cur] != 0)
        return game[cur];
    //printf("go %d\n", cur);

    matrix a;
    decode(cur, a);
    if (check_victory(a))
        return game[cur] = LOSE;
    if (!check_can_move(a))
        return game[cur] = DRAW;
    int player = get_player(a);
    //print(a);
    //printf("player = %d\n", player);
    forn(i, 3)
        forn(j, 3)
            if (a[i][j] == '.')
            {
                //printf("i = %d j = %d %c\n", i, j, a[i][j]);
                //print(a);
                int new_mask = cur + player * pows[i * 3 + j];
                int new_move = go(new_mask);
                //printf("cur = %d i = %d j = %d new_mask = %d new_move = %d\n", cur, i, j, new_mask, new_move);
                if (new_move == LOSE)
                {
                    lose_moves[cur].pb(new_mask);
                }
                else if (new_move == DRAW)
                {
                    draw_moves[cur].pb(new_mask);
                }
                else win_moves[cur].pb(new_mask);
            }
    if (!lose_moves[cur].empty())
        return game[cur] = WIN;
    if (!draw_moves[cur].empty())
        return game[cur] = DRAW;
    return game[cur] = LOSE;
}

void reach(int cur);

void reach_all(vi & v)
{
    forn(j, v.size())
        reach(v[j]);
}

void reach(int cur)
{
    //printf("cur = %d\n", cur);
    //matrix a;
    //decode(cur, a);
    //print(a);
    reachable[cur] = true;
    if (game[cur] == WIN)
        reach_all(lose_moves[cur]);
    else if (game[cur] == DRAW)
        reach_all(draw_moves[cur]);
    else reach_all(win_moves[cur]);
}

void precalc()
{
    pows[0] = 1;
    fore(j, 1, 9)
        pows[j] = pows[j - 1] * 3;
}

int main() {
    /*ios_base::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);*/
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    precalc();
    go(0);
    //printf("after go\n");
    reach(0);
    //printf("WIN = %d LOSE = %d DRAW = %d\n", WIN, LOSE, DRAW);
    //int tmp = pows[4] + 2 * pows[5];
    //printf("%d %d (tmp = %d)\n", game[pows[4]], game[tmp], tmp);
    //printf("after reach\n");
    int tests;
    scanf("%d", &tests);
    forn(i, tests)
        solve(i);
}



void solve(int test_number)
{
    int mask = 0;
    forn(i, 3)
    {
        string s;
        cin >> s;
        forn(j, 3)
            if (s[j] == 'O')
                mask += pows[i * 3 + j];
            else if (s[j] == 'X')
                mask += 2 * pows[i * 3 + j];
    }
    //printf("mask = %d\n", mask);
    if (game[mask] == 0)
        printf("INVALID\n");
    else if (reachable[mask])
        printf("REACHABLE\n");
    else printf("UNREACHABLE\n");

}
