#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 1e6 + 5;
const int M = 1e3 + 5;
int field[M][M];
int n, m, tol, ans;
int fa[maxn];
struct Edge 
{
	int start, endding, w;
}edge[maxn * 2];
bool cmp(Edge a, Edge b) 
{
	return a.w < b.w;
}
int find(int n) 
{
	return n == fa[n] ? n : fa[n] = find(fa[n]);
}
int main() {
	int t, cas = 1;
	scanf("%d", &t);
	while (t--) 
	{
		scanf("%d%d", &n, &m);
		ans = tol = 0;
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++)
				scanf("%d", &field[i][j]);


		for (int i = 1; i <= n; i++) 
		{
			for (int j = 1; j <= m; j++) 
			{
				int c = (i - 1)*m + j;
				fa[c] = c;//在这里初始化 机智步骤
				if (j > 1) 
				{
					edge[tol].start = (i - 1)*m + j - 1;
					edge[tol].endding = c;
					edge[tol++].w = abs(field[i][j - 1] - field[i][j]);
				}
				if (i > 1) 
				{
					edge[tol].start = (i - 2)*m + j;
					edge[tol].endding = c;
					edge[tol++].w = abs(field[i][j] - field[i - 1][j]);
				}
			}
		}
		sort(edge, edge + tol, cmp);
		
		for (int i = 0; i < tol; i++) 
		{
			int fx = find(edge[i].start), fy = find(edge[i].endding);
			if (fx != fy) 
			{
				ans += edge[i].w;
				fa[fx] = fy;
			}
		}

		printf("Case #%d:\n", cas++);
		printf("%d\n", ans);
	}
	return 0;
}
