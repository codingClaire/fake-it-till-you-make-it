#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

const int maxn = 1000;
int fa[maxn*maxn+10];
int T;
int n, m;
int field[maxn][maxn];
int tol;//边数 加边前赋值为0
int cnt;//记录加入的边
int ans;//记录最小生成树的长度


struct Edge
{
	int start, endding, w;
}edge[maxn*maxn+10];

bool cmp(Edge a, Edge b)
{
	return a.w < b.w; //排序函数 按照权值排序	
}

int find(int x)//路径压缩 
{
	int r=x;
	while(r!=fa[r])
		r=fa[r];
	int i=x,j;
	while(i!=r)
	{
		j=fa[i];
		fa[i]=r;
		i=j;
	}
	return r;
}

int Kruskal(int n)
{
	int cnt = 0;//记录加入的边
	int ans = 0;//记录最小生成树的长度
	sort(edge,edge+tol,cmp);
	for (int i = 0; i < tol; i++)
	{
		int t1 = find(edge[i].start);
		int t2 = find(edge[i].endding);
		if (t1 != t2)//起始点和终点不属于同一棵树
		{
			ans +=edge[i].w;
			fa[t1] = t2;//合并
			cnt++;
		}
		if (cnt == n - 1)
			break;//加入的边等于顶点数减1 说明找到生成树了
	//if (cnt < n - 1) return -1;//不是生成树
	}
	 return ans;
}
int main()
{
	scanf("%d", &T);
	int cas = 1;
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &field[i][j]);
		tol=0;
		for(int i=0; i<n; i++)
			for(int k=0; k<m; k++)
			{
				// 横向 
				if (k + 1 < m)
				{
					edge[tol].start = i* m + k;
					edge[tol].endding= i * m + k + 1;
					edge[tol++].w = abs(field[i][k] - field[i][k+1]); 
				}
				
				// 纵向
				if (i+ 1 < n)
				{
					edge[tol].start = i * m + k;
					edge[tol].endding = (i + 1) * m + k;
					edge[tol++].w = abs(field[i+1][k] - field[i][k]);	
				}  
			}	
	for(int j=0; j<=n*m; j++)
			fa[j] = j;
		printf("Case #%d:\n", cas++);
		printf("%d\n",Kruskal(n*m));
	}
return 0;
}

	
		
/*
2
4  3
9 12 4
7 8 56
32 32 43
21 12 12
2  3
34 56 56
12 23 4
*/


	/*	int sum=0;
		for (int j = 0; j <= n*m; j++)
			fa[j] = j;//初始化并查集
		sort(edge, edge + tol, cmp);//将处理好的边按照权值排序
		for(int j=0; j<tol; j++)
		{
			int t1 = find(edge[j].start);
			int t2= find(edge[j].endding);
			if (t1 != t2)
			{
				fa[t1] = t2;
				sum += edge[j].w;
			}	
		}
		printf("Case #%d:\n", cas++);
		printf("%d\n",sum); */

