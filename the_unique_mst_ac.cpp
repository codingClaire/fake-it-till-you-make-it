#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;

const int INF = 0X3F3F3F3F;
const int maxn = 500;
const int maxe = 500 * 500;
int n, m;//nodes and edges
int fa[maxn + 10];
bool choose[maxe + 10];//存储是否选取了该点的状态
int mst, secondmst;
int cnt;


int Find(int x)//路径压缩 
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

struct Edge
{
	int start, endding;
	int w;

}edge[maxe + 10];

bool cmp(Edge a, Edge b)
{
	if (a.w != b.w)
		return a.w < b.w;
	else if (a.start != b.start)
		return a.start < b.start;
	return a.endding < b.endding;
}//比较

void Union(int x, int y)
{
	x = Find(x);
	y = Find(y);
	if (x != y)
	{
		fa[x] = y;
	}
}




int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		mst = 0;
		cnt = 0;
		memset(choose, false, sizeof(choose));
		scanf("%d%d", &n, &m);
		for (int i = 0; i<m; i++)
		{
			scanf("%d%d%d", &edge[i].start, &edge[i].endding, &edge[i].w);
		}
		sort(edge, edge + m, cmp);
		
		for (int i = 0; i <= n; i++)
			fa[i] = i;//初始化并查集 


		int flag = 0;
		for (int i = 0; i<m; i++)
		{
			if (Find(edge[i].start) != Find(edge[i].endding))
			{
				cnt++;
				Union(edge[i].start, edge[i].endding);
				mst += edge[i].w;
				choose[i] = true;
			}
		}
		if (cnt != (n - 1))
		{
			printf("Not Unique!\n");
			continue;
		}
		for (int i = 0; i<m; i++)
		{
			if (choose[i] == false)
			{
				cnt = 1;
				secondmst = 0;
				flag = i;
				for (int i = 0; i <= n; i++)
					fa[i] = i;//初始化并查集 
				Union(edge[flag].start, edge[flag].endding);
				secondmst += edge[flag].w;
				for (int j = 0; j<m; j++)
				{
					if (Find(edge[j].start) != Find(edge[j].endding))
					{
						secondmst += edge[j].w;
						cnt++;
						Union(edge[j].start, edge[j].endding);
						if (cnt== (n - 1))
						{
							break;
						}
					}
				}
			}
			if (secondmst == mst)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			printf("Not Unique!\n");
		}
		else
			printf("%d\n", mst);
	}
	return 0;
}
