#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;

const int INF = 0X3F3F3F3F;
const int maxn = 500;
const int maxe = 500 * 500;
int head[maxn + 10], End[maxn + 10];//邻接表的头节点和尾节点 
int length[maxn + 10][maxn + 10];//最小生成树任意两点路径上的最长边
int n, m;//nodes and edges
int fa[maxn+10];
bool choose[maxe+10];//存储是否选取了该点的状态

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

int Find(int x){ return x == fa[x] ? x : fa[x] = Find(fa[x]); }

struct Edge
{
	int start, endding;
	int w;
	
}edge[maxe+10];

bool cmp(Edge a, Edge b)
{
	if (a.w != b.w)
		return a.w < b.w;
	else if (a.start != b.start)
		return a.start < b.start;
	return a.endding < b.endding;
}//比较


struct Node
{
	int to, next;
}link[maxn+10];

int Kruskal(int n, int m)
{
	int cnt = 0;

	for (int i = 0; i <n; i++)
	{
		link[i].to = i;
		link[i].next = head[i];
		End[i] = i;
		head[i] = i;
	}
	
	sort(edge, edge + m, cmp);//按照权值排序
	for (int i = 0; i < m; i++)
	{
		if (cnt == n - 1) break;
		int fx = Find(edge[i].start);
		int fy = Find(edge[i].endding);	
		if (fx != fy)
		{
			printf("test\n");
			for (int j = head[fx]; j != -1; j = link[j].next)
				for (int k = head[fy]; k != -1; k = link[k].next)
					length[link[j].to][link[k].to]= length[link[k].to][link[j].to]= edge[i].w;//当前加入的边的权值
			link[End[fy]].next = head[fx];//???
			End[fy] = End[fx];
			//merge
			int ffx = Find(fx), ffy = Find(fy);
			if (ffx != ffy)
				fa[ffx] = ffy;
			cnt++;
			choose[i] = true;
		printf("cnt is %d\n",cnt);
		}
	}
	if (cnt != n - 1) 
		return -1;	
	return 1;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		memset(choose,0,sizeof(choose));
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++)
			scanf("%d%d%d", &edge[i].start, &edge[i].endding, &edge[i].w);
		for(int i=0;i<=n;i++) 
			fa[i] = i;//初始化并查集 
		int f = Kruskal(n, m);
		if (f==-1) printf("Not Unique!\n");
		else
		{
			int mst = 0;
			for (int i = 0; i < m; i++)
				if (edge[i].choose)
					mst += edge[i].w;
			int secondmst = INF;
			for (int i = 0; i < m; i++)
				if (!edge[i].choose)
					secondmst = min(secondmst, mst + edge[i].w - length[edge[i].start][edge[i].endding]);
			printf("%d\n", secondmst);
		}
	}
	return 0;
}


/*2
3 3
1 2 1
2 3 2
3 1 3
4 4
1 2 2
2 3 2
3 4 2
4 1 2

*/
