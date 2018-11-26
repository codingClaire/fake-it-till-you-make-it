#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
 
const int maxn = 1000000 + 10;
int dir[4][2] = { 0,1,0,-1,-1,0,1,0 };
int year[maxn], ans[maxn], z, n, m, t,sum;
int vis[maxn], father[maxn];
struct node
{
	int x, y, val;
};
vector<node> nodes;//vector数组 存下每一个结点
bool cmp(node a, node b)
{
	return a.val < b.val;
}
int find(int x)
{
	if (father[x] != x)
		father[x] = find(father[x]);
	return father[x];
}
inline int transform(int x, int y) { return x*m + y; }//二维化一维
void judge(node u)
{
	sum++;
	vis[transform(u.x, u.y)] = 1;
	for (int i = 0; i < 4; i++)
	{
		int xx = u.x + dir[i][0];
		int yy = u.y + dir[i][1];
		if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&vis[transform(xx, yy)] != 0)
		{
			int a = find(transform(u.x, u.y));
			int b = find(transform(xx, yy));
			if (a != b)
			{
				father[a] = b;
				sum--;
			}
		}
	}
}

int main()
{
	int z;
	scanf("%d", &z);
	while (z--)
	{
		memset(vis, 0, sizeof(vis));
		nodes.clear();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				int v;
				scanf("%d", &v);
				nodes.push_back(node{ i,j,v});
			}
		}
		scanf("%d", &t);
		for (int i = 0; i < t; i++)
		{
			scanf("%d", &year[i]);
		}
		sort(nodes.begin(), nodes.end(), cmp); 
		for (int i = 0; i < n*m; i++)
		{
			father[i] = i;
		}

		int pos = nodes.size() - 1;
		sum = 0;
		for (int i = t - 1; i >= 0; i--)
		{
			while (nodes[pos].val> year[i])
				judge(nodes[pos--]);
			ans[i] = sum;
		}
		for (int i = 0; i < t; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}
