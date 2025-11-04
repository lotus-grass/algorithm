void solve(int l, int r)
{
 if (l == r) return;
 int mid = (l + r) >> 1;
 solve(l, mid), solve(mid + 1, r);
 // cross
}