#include <bits/stdc++.h>
using namespace std;
const int N = 26;
int H, W, E[N];
char s[N][N];
size_t dp[N][(1 << 26) + 5];
int32_t main()
{
 ios_base::sync_with_stdio(false);
 cin.tie(nullptr);
 cout.tie(nullptr);
 cin >> H >> W;
 for (int i = 1; i <= H; ++i)
 {
  cin >> s[i];
  for (int j = 0; j < W; ++j)
   if (s[i][j] == '#') E[i] |= (1 << j);
 }
 for (int i = 1; i <= H; ++i)
 {
  
 }
 return 0;
}