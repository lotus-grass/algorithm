#include <bits/stdc++.h>
#define pp putchar(' ')
#define pn putchar('\n')
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define Fo(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e5 + 5;
int n, m;
struct treenode
{
 int lc, rc, siz, val, tag;
 mt19937::result_type pri;
} tr[N];
#define ls tr[p].lc
#define rs tr[p].rc
int rt, nodecnt;
inline void up(int p) { tr[p].siz = tr[tr[p].lc].siz + tr[tr[p].rc].siz + 1; }
inline void spread(int p)
{
 if (tr[p].tag) swap(tr[p].lc, tr[p].rc), tr[ls].tag ^= 1, tr[rs].tag ^= 1, tr[p].tag = 0;
}
void split(int p, int rk, int &x, int &y)
{
 if (!p) return x = y = 0, void();
 spread(p);
 if (tr[ls].siz + 1 <= rk) x = p, split(tr[p].rc, rk - tr[ls].siz - 1, tr[p].rc, y);
 else y = p, split(tr[p].lc, rk, x, tr[p].lc);
 up(p);
}
int merge(int x, int y)
{
 if (!x || !y) return x | y;
 if (tr[x].pri <= tr[y].pri) return spread(x), tr[x].rc = merge(tr[x].rc, y), up(x), x;
 else return spread(y), tr[y].lc = merge(x, tr[y].lc), up(y), y;
}
int newnode(int val)
{
 int p = ++nodecnt;
 tr[p].pri = rng(), tr[p].val = val, tr[p].lc = tr[p].rc = tr[p].tag = 0, tr[p].siz = 1;
 return p;
}
signed main() { return 0; }