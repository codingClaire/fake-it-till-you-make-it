#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

const int maxn = 1000;
const int maxp = 1000000;
int n, m;
int fa[maxn]; 
int tol;

struct Edge
{
	int start, endding;
	double w;
}edge[maxp + 10];

struct Farm
{
	double x, y;
}farm[maxn+10];

int find(int x)//路径压缩 
{
	int r = x;
	while (r != fa[r])
		r = fa[r];
	int i = x, j;
	while (i != r)
	{
		j = fa[i];
		fa[i] = r;
		i = j;
	}
	return r;
}

bool cmp(Edge a, Edge b)
{
		return a.w < b.w;
}//比较

double Kruskal(int n)
{
	int cnt = 0;//记录加入的边
	double ans = 0;//记录最小生成树的长度
	sort(edge, edge + tol, cmp);
	for (int i = 0; i < tol; i++)
	{
		int t1 = find(edge[i].start);
		int t2 = find(edge[i].endding);
		if (t1 != t2)//起始点和终点不属于同一棵树
		{
			ans += edge[i].w;
			fa[t1] = t2;//合并
			cnt++;
		}
	
	if (cnt == n - 1-m)
			break;//加入的边等于顶点数减1 说明找到生成树了
		//if (cnt < n - 1) return -1;//不是生成树
	}
	return ans;
}

int main()
{
	
	scanf("%d%d", &n, &m);// != EOF)//n个点 m条路
	
		tol = 0;
		for (int i = 1; i <= n; i++)
			//scanf("%d%d", &farm[i].x, &farm[i].y);
	      cin>>farm[i].x>>farm[i].y;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)//注意这个二重循环 把每个点之间的距离记录下来
			{
				edge[tol].start = i;
				edge[tol].endding = j;
				edge[tol++].w =sqrt((farm[i].x - farm[j].x)*(farm[i].x - farm[j].x) + (farm[i].y - farm[j].y)*(farm[i].y - farm[j].y));
			}
		for (int i = 0; i <= n; i++) fa[i] = i;//初始化
		for (int i = 0; i < m; i++)
		{
			int p1, p2;
			scanf("%d %d", &p1, &p2);
			if(find(p1)!=find(p2))
			{
				int fx = find(p1);
				int fy = find(p2);
				if (fx != fy)
					fa[fx] = fy;
			}
		
		}
		printf("%.2lf\n", Kruskal(n));
	
	return 0;
}
