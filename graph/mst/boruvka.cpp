#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define rep(i, x, p) for (int i = x; i <= p; ++i)
#define sep(i, x, p) for (int i = x; i >= p; --i)
#define gc getchar()
#define pc putchar
#define ll long long
#define mk make_pair
#define fi first
#define se second
using std::max;
using std::min;
using std::swap;
const int inf = 0x3f3f3f3f;
const int maxN = 5000 + 7;
const int maxM = 200000 + 7;

inline int gi()
{
 int x = 0, f = 1;
 char c = gc;
 while (c < '0' || c > '9')
 {
  if (c == '-') f = -1;
  c = gc;
 }
 while (c >= '0' && c <= '9')
 {
  x = x * 10 + c - '0';
  c = gc;
 }
 return x * f;
}

struct Node
{
 int u, v, w;
} Map[maxM];
int n, m;
int f[maxN];
bool vis[maxM];       // 该边是否用过
int d[maxN], a[maxN]; // 各子树的最小连外边的权值
int id[maxN];         // 记录各子树的最小连外边的编号

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int unqie(int x, int y) { f[find(x)] = find(y); }

int Boruvka()
{
 for (int i = 1; i <= n; ++i) f[i] = i;
 int sum = 0;
 while (true)
 {
  bool flag = false;
  for (int i = 1; i <= n; ++i) d[i] = inf;
  for (int i = 1; i <= m; ++i)
  {
   int u = find(Map[i].u), v = find(Map[i].v), c = a[u] & a[v];
   if (u == v) continue;
   flag = true;
   if (c < d[u] || (d[u] == c && id[u] > i)) id[u] = i, d[u] = c;
   if (c < d[v] || (d[v] == c && id[v] > i)) id[v] = i, d[v] = c;
  }
  if (!flag) break;
  for (int i = 1; i <= n; ++i)
  {
   if (d[i] != inf && !vis[id[i]])
   {
    unqie(Map[id[i]].u, Map[id[i]].v);
    sum += Map[id[i]].w;
    vis[id[i]] = true;
   }
  }
 }
 int tot = 0;
 for (int i = 1; i <= n; ++i)
  if (f[i] == i) tot++;
 tot > 1 ? printf("orz") : printf("%d", sum);
}